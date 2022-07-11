/*  Title		: Serial
 *  Filename	: serial.c
 *	Author		: iacopo sprenger
 *	Date		: 02.04.2022
 *	Version		: 0.1
 *	Description	: serial interface for device driver
 */

/**********************
 *	INCLUDES
 **********************/

#include <util.h>
#include <usart.h>
#include <main.h>

#include "serial.h"
#include <device/device.h>


/**********************
 *	CONSTANTS
 **********************/

#define S1_UART 			huart2
#define S2_UART 			huart3
#define S3_UART 			huart6

#define SERIAL_DMA_LEN 32


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/




/**********************
 *	VARIABLES
 **********************/

static device_daemon_t serial_deamon;

static device_interface_t feedback_interface;

static serial_deamon_context_t serial_deamon_context;

static serial_interface_context_t feedback_interface_context = {
		.uart = &S3_UART
};


/**********************
 *	PROTOTYPES
 **********************/

util_error_t serial_data_ready(void * context);

util_error_t serial_send(void * context, uint8_t* data, uint32_t len);

util_error_t serial_recv(void * context, uint8_t* data, uint32_t * len);

util_error_t serial_handle_data(void * if_context, void * dem_context);

util_error_t serial_setup_reception(serial_interface_context_t * interface_context, serial_transfer_mode_t mode);


/**********************
 *	DECLARATIONS
 **********************/

//Interrupt receive handler for serial

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	for(uint8_t i = 0; i < serial_deamon.interfaces_count; i++) {
		serial_interface_context_t * serial_context = (serial_interface_context_t *) serial_deamon.interfaces[i]->context;
		if(serial_context->uart == huart) {
			util_buffer_u8_add(&serial_context->rx_buffer, serial_context->rx_fragment);

			serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) serial_deamon.context;
			xSemaphoreGiveFromISR( deamon_context->rx_sem, &xHigherPriorityTaskWoken );

			break;
		}
	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}




device_daemon_t * serial_get_deamon(void)
{
	return &serial_deamon;
}

device_interface_t * serial_get_feedback_interface(void)
{
	return &feedback_interface;
}


util_error_t serial_init(void)
{
	util_error_t error = ER_SUCCESS;

	//initialize deamon semaphore
	serial_deamon_context.rx_sem = xSemaphoreCreateBinaryStatic(&serial_deamon_context.rx_sem_buffer);

	error |= device_deamon_create(&serial_deamon, "serial deamon", 6, (void *) &serial_deamon_context, serial_data_ready);


	return error;
}

util_error_t serial_feedback_init(void) {
	util_error_t error = ER_SUCCESS;

	error |= device_interface_create(&feedback_interface, (void*) &feedback_interface_context, &serial_deamon, serial_send, serial_recv, serial_handle_data);

	serial_setup_reception(&feedback_interface_context, SERIAL_TRANSFER_IT);

	return error;
}

util_error_t serial_data_ready(void * context)
{
	serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) context;
	if( xSemaphoreTake(deamon_context->rx_sem, 0xffff) == pdTRUE ) {
		return ER_SUCCESS;
	} else {
		return ER_TIMEOUT;
	}

}

util_error_t serial_setup_reception(serial_interface_context_t * interface_context, serial_transfer_mode_t mode)
{
	if( mode == SERIAL_TRANSFER_DMA) {
		//setup dma reception

		return ER_RESSOURCE_ERROR;
		//TODO: setup reception using DMA


	} else if ( mode == SERIAL_TRANSFER_IT) {
		//setup Interrupt reception byte per byte
		util_buffer_u8_init(&interface_context->rx_buffer, interface_context->rx_data, SERIAL_BUFFER_LEN);

		HAL_UART_Receive_IT(interface_context->uart, &interface_context->rx_fragment, 1);

	}
	return ER_FAILURE;
}

util_error_t serial_send(void * context, uint8_t* data, uint32_t len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	HAL_UART_Transmit_IT(interface_context->uart, data, len);

	return ER_SUCCESS;
}

util_error_t serial_recv(void * context, uint8_t * data, uint32_t * len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;
	uint16_t i = 0;
	while(!util_buffer_u8_isempty(&interface_context->rx_buffer) && i < len) {
		data[i++] = util_buffer_u8_get(&interface_context->rx_buffer);
	}
	*len = i;
	return ER_SUCCESS;
}


util_error_t serial_handle_data(void * if_context, void * dem_context)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) if_context;
	serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) dem_context;

	//no data handling for now

	return ER_SUCCESS;
}



/* END */
