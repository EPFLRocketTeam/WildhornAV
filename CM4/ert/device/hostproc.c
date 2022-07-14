/*  Title		: Messenger
 *  Filename	: messenger.c
 *	Author		: iacopo sprenger
 *	Date		: 30.01.2021
 *	Version		: 0.1
 *	Description	: messenger to communicate with linux kernel on CA7
 *				  in this file we define the messenger which communicates between
 *				  rpmsg and openAMP
 *
 */

/**********************
 *	INCLUDES
 **********************/

#include <main.h>

#include <cmsis_os.h>
#include <device/hostproc.h>
#include <feedback/led.h>
#include <openamp.h>
#include <util.h>



/**********************
 *	CONSTANTS
 **********************/

#define MAX_RX_DATA	1024


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

typedef struct hostproc_interface_context {
	VIRT_UART_HandleTypeDef * uart;
	uint8_t rx_once;
	util_buffer_u8_t rx_buffer;
	uint8_t rx_data[MAX_RX_DATA];
}hostproc_interface_context_t;


/**********************
 *	VARIABLES
 **********************/

/**
 * @brief 	Virtual UART channel for feedback messages.
 * @details	This channel is used to send debug and logging messages
 * 			to linux, these messages will be saved into log files.
 *
 * @note 	These messages will be fed to the feedback board for debug as
 * 			engineering data (in plain text or connected to a UI)
 *
 */
static VIRT_UART_HandleTypeDef host_UART0;
static device_interface_t hostproc_feedback_interface;
static hostproc_interface_context_t hostproc_feedback_interface_context = {
		.uart = &host_UART0
};

/**
 * @brief	Virtual UART channel for OD synchronization.
 * @details	This channel is used to synchronize the OD with the linux system.
 *
 */
static VIRT_UART_HandleTypeDef host_UART1;
static device_interface_t hostproc_sync_interface;
static hostproc_interface_context_t hostproc_sync_interface_context = {
		.uart = &host_UART1
};

/**
 * @brief	Virtual UART channel for critical data synchronization.
 * @details	This channel is used to synchronize some critical data with the
 * 			linux system. This will be typically used to send sensor data to be
 * 			processed by the kalman filter and the state estimation.
 */
static VIRT_UART_HandleTypeDef host_UART2;
static device_interface_t hostproc_data_interface;
static hostproc_interface_context_t hostproc_data_interface_context = {
		.uart = &host_UART2
};

/**
 * @brief	Virtual UART channel for commands
 * @details	This channel is used to send commands to and from the hostproc
 * 			for example to enable some specific operation modes
 *
 * @note 	This might be included in the OD as a command word or something.
 */
static VIRT_UART_HandleTypeDef host_UART3;
static device_interface_t hostproc_cmd_interface;
static hostproc_interface_context_t hostproc_cmd_interface_context = {
		.uart = &host_UART3
};


static device_interface_t * hostproc_interfaces[] = {
		&hostproc_feedback_interface,
		&hostproc_sync_interface,
		&hostproc_data_interface,
		&hostproc_cmd_interface
};

static uint32_t hostproc_interfaces_count =
		sizeof(hostproc_interfaces) / sizeof(device_interface_t *);



/**********************
 *	PROTOTYPES
 **********************/

void host_UART_RX(VIRT_UART_HandleTypeDef *huart);

util_error_t host_send(void* context, uint8_t* data, uint32_t len);
util_error_t host_recv(void* context, uint8_t* data, uint32_t* len);

/**********************
 *	DECLARATIONS
 **********************/

device_interface_t * hostproc_get_feedback_interface(void) {
	return &hostproc_feedback_interface;
}

device_interface_t * hostproc_get_sync_interface(void) {
	return &hostproc_sync_interface;
}

device_interface_t * hostproc_get_data_interface(void) {
	return &hostproc_data_interface;
}

device_interface_t * hostproc_get_cmd_interface(void) {
	return &hostproc_cmd_interface;
}



/**
 * @brief Virtual uart reception callback, called from the rpmsg polling function.
 */
void host_UART_RX(VIRT_UART_HandleTypeDef *huart) {
	for(uint32_t i = 0; i < hostproc_interfaces_count; i++) {
		hostproc_interface_context_t * if_ctx = (hostproc_interface_context_t *) hostproc_interfaces[i]->context;
		if(if_ctx->uart == huart) {
			if_ctx->rx_once = 1;
			uint32_t i = 0;
			while(i < huart->RxXferSize) {
				util_buffer_u8_add(&if_ctx->rx_buffer, huart->pRxBuffPtr[i]);
				i++;
			}
			break; //no need to check others after match
		}
	}
}

util_error_t host_send(void* context, uint8_t* data, uint32_t len) {
	hostproc_interface_context_t * interface_context = (hostproc_interface_context_t *) context;
	if(interface_context->rx_once) {
		VIRT_UART_Transmit(interface_context->uart, data, len);
	}
	return ER_SUCCESS;
}

util_error_t host_recv(void* context, uint8_t* data, uint32_t* len) {
	hostproc_interface_context_t * if_ctx = (hostproc_interface_context_t *) context;
	//check if messages where received.
	OPENAMP_check_for_message();
	uint32_t i = 0;
	while((!util_buffer_u8_isempty(&if_ctx->rx_buffer)) && (i < *len)) {
		//led_rgb_set_rgb(0xff, 0xff, 0xff);
		data[i] = util_buffer_u8_get(&if_ctx->rx_buffer);
		i++;
	}
	*len = i;
	return ER_SUCCESS;
}

util_error_t hostproc_uart_init(device_interface_t * hostproc, hostproc_interface_context_t * context) {
	if(VIRT_UART_Init(context->uart) != VIRT_UART_OK) {
		return ER_FAILURE;
	}

	if (VIRT_UART_RegisterCallback(context->uart, VIRT_UART_RXCPLT_CB_ID, host_UART_RX) != VIRT_UART_OK) {
		return ER_FAILURE;
	}



	context->rx_once = 0;
	util_buffer_u8_init(&context->rx_buffer, context->rx_data, MAX_RX_DATA);

	device_interface_create(hostproc, (void*) context, NULL, host_send, host_recv, NULL);

	return ER_SUCCESS;
}


util_error_t hostproc_init(void) {

	hostproc_uart_init(&hostproc_feedback_interface, &hostproc_feedback_interface_context);
	hostproc_uart_init(&hostproc_sync_interface, &hostproc_sync_interface_context);
	hostproc_uart_init(&hostproc_data_interface, &hostproc_data_interface_context);
	hostproc_uart_init(&hostproc_cmd_interface, &hostproc_cmd_interface_context);


	return ER_SUCCESS;

}




/* END */
