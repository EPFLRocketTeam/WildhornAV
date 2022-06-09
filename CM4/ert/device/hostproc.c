/*  Title		: Messenger
 *  Filename	: messenger.c
 *	Author		: iacopo sprenger
 *	Date		: 30.01.2021
 *	Version		: 0.1
 *	Description	: messenger to communicate with linux kernel on CA7
 *				  in this file we define the messenger which communicates between
 *				  rpmsg and openAMP
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



/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

typedef struct hostproc_interface_context {
	VIRT_UART_HandleTypeDef * uart;
	uint8_t rx_once;
}hostproc_interface_context_t;


/**********************
 *	VARIABLES
 **********************/

static VIRT_UART_HandleTypeDef host_UART0;


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
}

util_error_t host_send(void* context, uint8_t* data, uint32_t len) {
	hostproc_interface_context_t * interface_context = (hostproc_interface_context_t *) context;
	if(interface_context->rx_once) {
		VIRT_UART_Transmit(interface_context->uart, data, len);
	}


	return ER_SUCCESS;
}

util_error_t host_recv(void* context, uint8_t* data, uint32_t* len) {

}


util_error_t hostproc_init(void) {
	if(VIRT_UART_Init(&host_UART0) != VIRT_UART_OK) {
		return ER_FAILURE;
	}

	if (VIRT_UART_RegisterCallback(&host_UART0, VIRT_UART_RXCPLT_CB_ID, host_UART0_RX) != VIRT_UART_OK) {
		return ER_FAILURE;
	}
	//we need to receive once before sending...
//	if (VIRT_UART_Transmit(&host_UART0, "Welcome", sizeof("welcome")) != VIRT_UART_OK) {
//		return ER_FAILURE;
//	}



	hostproc_interface_context.uart = &host_UART0;
	hostproc_interface_context.rx_once = 0;

	device_interface_create(&hostproc_interface, (void*) &hostproc_interface_context, NULL, host_send, host_recv, NULL);

	return ER_SUCCESS;

}




/* END */
