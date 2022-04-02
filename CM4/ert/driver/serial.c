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

#include <abstraction/dma.h>
#include <abstraction/uart.h>

#include "serial.h"
#include "device.h"


/**********************
 *	CONSTANTS
 **********************/

#define FEEDBACK_SERIAL_DEV	huart2

#define SERIAL_BUFFER_LEN 256


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

typedef struct serial_deamon_context {
	SemaphoreHandle_t rx_sem;
	StaticSemaphore_t rx_sem_buffer;

}serial_deamon_context_t;

typedef struct serial_interface_context {
	UART_HandleTypeDef * uart;
	uint8_t rx_dma_buffer[SERIAL_BUFFER_LEN];
	uint8_t rx_data[SERIAL_BUFFER_LEN];
	uint32_t rx_data_len;

}serial_interface_context_t;


/**********************
 *	VARIABLES
 **********************/

static device_deamon_t serial_deamon;

static device_interface_t feedback_interface;

static serial_deamon_context_t serial_deamon_context;

static serial_interface_context_t serial_feedback_context;


/**********************
 *	PROTOTYPES
 **********************/

error_t serial_data_ready(void * context);

error_t serial_send(void * context, uint8_t* data, uint32_t len);

error_t serial_recv(void * context, uint8_t* data, uint32_t * len);

error_t serial_handle_data(void * context);


/**********************
 *	DECLARATIONS
 **********************/

//Interrupt receive handler for serial

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(serial_deamon_context.rx_sem , &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(serial_deamon_context.rx_sem , &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void uart_idle_handler(UART_HandleTypeDef * uart) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xSemaphoreGiveFromISR(serial_deamon_context.rx_sem , &xHigherPriorityTaskWoken );
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}



error_t serial_initialize(void)
{
	error_t error = ER_SUCCESS;

	error |= device_deamon_create(&serial_deamon, "serial deamon", 6, (void *) &serial_deamon_context, serial_data_ready);

	error |= device_interface_create(&feedback_interface, (void*) &serial_feedback_context, &serial_deamon, serial_send, serial_recv, serial_handle_data);



	return error;
}

error_t serial_data_ready(void * context)
{
	serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) context;
	if( xSemaphoreTake(deamon_context->rx_sem, 0xffff) == pdTRUE ) {
		return ER_SUCCESS;
	} else {
		return ER_TIMEOUT;
	}

}

error_t serial_send(void * context, uint8_t* data, uint32_t len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	HAL_UART_Transmit_DMA(interface_context->uart, data, len);

	return ER_SUCCESS;
}

error_t serial_recv(void * context, uint8_t * data, uint32_t * len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	//copy data using DMA
	if(*len > interface_context->rx_data_len) {
		*len = interface_context->rx_data_len;
	}

	dma_copy(data, interface_context->rx_data, *len);

	return ER_SUCCESS;
}

error_t serial_handle_data(void * context)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	for(uint32_t i = 0; i < SERIAL_BUFFER_LEN; i++) {
		interface_context->rx_data[interface_context->rx_data_len++] = interface_context->rx_dma_buffer[i];
	}


}



/* END */