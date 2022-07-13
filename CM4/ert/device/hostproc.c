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

/**
 * @brief	Virtual UART channel for OD synchronization.
 * @details	This channel is used to synchronize the OD with the linux system.
 *
 */
static VIRT_UART_HandleTypeDef host_UART1;

/**
 * @brief	Virtual UART channel for critical data synchronization.
 * @details	This channel is used to synchronize some critical data with the
 * 			linux system. This will be typically used to send sensor data to be
 * 			processed by the kalman filter and the state estimation.
 */
static VIRT_UART_HandleTypeDef host_UART2;

/**
 * @brief	Virtual UART channel for commands
 * @details	This channel is used to send commands to and from the hostproc
 * 			for example to enable some specific operation modes
 *
 * @note 	This might be included in the OD as a command word or something.
 */
static VIRT_UART_HandleTypeDef host_UART3;

/*
 * This will need to be
 *
 * hostproc_feedback_interface
 *
 * hostproc_od_interface
 *
 * hostproc_data_interface
 *
 * (optional) hostproc_cmd_interface
 */

static device_t hostproc_device;
static device_interface_t hostproc_interface;
static hostproc_interface_context_t hostproc_interface_context;


/**********************
 *	PROTOTYPES
 **********************/

void host_UART0_RX(VIRT_UART_HandleTypeDef *huart);

util_error_t host_send(void* context, uint8_t* data, uint32_t len);
util_error_t host_recv(void* context, uint8_t* data, uint32_t* len);

/**********************
 *	DECLARATIONS
 **********************/


device_interface_t * hostproc_get_interface(void) {
	return &hostproc_interface;
}

device_t * hostproc_get_device(void) {
	return &hostproc_device;
}


void host_UART0_RX(VIRT_UART_HandleTypeDef *huart) {
	led_rgb_set_rgb(0xff, 0xff, 0xff);
	hostproc_interface_context.rx_once = 1;
	uint32_t i = 0;
	while(i < huart->RxXferSize) {
		util_buffer_u8_add(&hostproc_interface_context.rx_buffer, huart->pRxBuffPtr[i]);
		i++;
	}
}

util_error_t host_send(void* context, uint8_t* data, uint32_t len) {
	hostproc_interface_context_t * interface_context = (hostproc_interface_context_t *) context;
	if(interface_context->rx_once) {

		if(VIRT_UART_Transmit(interface_context->uart, data, len) != VIRT_UART_OK) {
			led_rgb_set_rgb(0xff, 0, 0);
		} else {
			led_rgb_set_rgb(0, 0xff, 0);
		}
	}
	return ER_SUCCESS;
}

util_error_t host_recv(void* context, uint8_t* data, uint32_t* len) {
	hostproc_interface_context_t * if_ctx = (hostproc_interface_context_t *) context;
	//check if messages where received.
	OPENAMP_check_for_message();
	uint32_t i = 0;
	while(!util_buffer_u8_isempty(&if_ctx->rx_buffer) && i < *len) {
		data[i] = util_buffer_u8_get(&if_ctx->rx_buffer);
		i++;
	}
	*len = i;
	return ER_SUCCESS;
}


util_error_t hostproc_init(void) {
	if(VIRT_UART_Init(&host_UART0) != VIRT_UART_OK) {
		return ER_FAILURE;
	}

	if (VIRT_UART_RegisterCallback(&host_UART0, VIRT_UART_RXCPLT_CB_ID, host_UART0_RX) != VIRT_UART_OK) {
		return ER_FAILURE;
	}



	hostproc_interface_context.uart = &host_UART0;
	hostproc_interface_context.rx_once = 0;
	util_buffer_u8_init(&hostproc_interface_context.rx_buffer, hostproc_interface_context.rx_data, MAX_RX_DATA);

	device_interface_create(&hostproc_interface, (void*) &hostproc_interface_context, NULL, host_send, host_recv, NULL);

	return ER_SUCCESS;

}




/* END */
