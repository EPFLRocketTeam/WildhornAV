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

#define SERIAL_BUFFER_LEN 256

#define SERIAL_DMA_LEN 32


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

typedef enum serial_interrupt_source{
	SERIAL_SOURCE_DMA_FIRST_HALF,
	SERIAL_SOURCE_DMA_SECOND_HALF,
	SERIAL_SOURCE_IDLE
}serial_interrupt_source_t;

typedef enum serial_transfer_mode{
	SERIAL_TRANSFER_DMA,
	SERIAL_TRANSFER_IT
}serial_transfer_mode_t;

typedef struct serial_deamon_context {
	SemaphoreHandle_t rx_sem;
	StaticSemaphore_t rx_sem_buffer;
	serial_interrupt_source_t source;

}serial_deamon_context_t;

typedef struct serial_interface_context {
	uart_dev_t * uart;
	dma_scheduler_dev_t * dma;
	dma_stream_dev_t * rx_dma;
	dma_stream_dev_t * tx_dma;
	uint8_t rx_dma_buffer[SERIAL_DMA_LEN];
	uint8_t rx_data[SERIAL_BUFFER_LEN];
	uint32_t rx_data_len;
	uint8_t first_half;

}serial_interface_context_t;


/**********************
 *	VARIABLES
 **********************/

static device_deamon_t serial_deamon;

static device_interface_t feedback_interface;

static serial_deamon_context_t serial_deamon_context;

static serial_interface_context_t feedback_interface_context;


/**********************
 *	PROTOTYPES
 **********************/

error_t serial_data_ready(void * context);

error_t serial_send(void * context, uint8_t* data, uint32_t len);

error_t serial_recv(void * context, uint8_t* data, uint32_t * len);

error_t serial_handle_data(void * if_context, void * dem_context);

error_t serial_setup_reception(serial_interface_context_t * interface_context, serial_transfer_mode_t mode);


/**********************
 *	DECLARATIONS
 **********************/

//Interrupt receive handler for serial

device_deamon_t * serial_get_deamon(void)
{
	return &serial_deamon;
}

device_interface_t * serial_get_interface(void)
{
	return &feedback_interface;
}


error_t serial_init(void)
{
	error_t error = ER_SUCCESS;

	//initialize deamon semaphore
	serial_deamon_context.rx_sem = xSemaphoreCreateBinaryStatic(&serial_deamon_context.rx_sem_buffer);

	//initialize feedback serial
	uart_config_t uart_config;
	uart_config.baudrate = 115200;
	uart_config.prescaler = UART_PSCALER_DIV8;
	uart_config.uart_clock_freq =100e6;

	//initialize uart hardware
	feedback_interface_context.uart = uart_get_usart2();
	uart_init(feedback_interface_context.uart, uart_config);

	//start reception using DMA
	//TODO: handle error cases!
	serial_setup_reception(&feedback_interface_context, SERIAL_TRANSFER_IT);




	error |= device_deamon_create(&serial_deamon, "serial deamon", 6, (void *) &serial_deamon_context, serial_data_ready);

	error |= device_interface_create(&feedback_interface, (void*) &feedback_interface_context, &serial_deamon, serial_send, serial_recv, serial_handle_data);




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

error_t serial_setup_reception(serial_interface_context_t * interface_context, serial_transfer_mode_t mode)
{
	if( mode == SERIAL_TRANSFER_DMA) {
		//setup dma reception
		interface_context->uart->rx_stream = dma_scheduler_request_stream(interface_context->dma);
		//check if a stream was available
		if(interface_context->tx_dma == NULL) {
			return ER_RESSOURCE_ERROR;
		}
		return ER_RESSOURCE_ERROR;
		//TODO: setup reception using DMA


	} else if ( mode == SERIAL_TRANSFER_IT) {
		//setup Interrupt reception
		uart_receive_IT(interface_context->uart);
	}
	return ER_FAILURE;
}

error_t serial_send(void * context, uint8_t* data, uint32_t len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	dma_stream_dev_t * stream = dma_scheduler_request_stream(interface_context->dma);

	if(stream != NULL) {
		//send using DMA
		interface_context->uart->tx_stream = dma_scheduler_request_stream(interface_context->dma);
		uart_transmit_DMA(interface_context->uart, len, data);
	} else {
		//send using interrupts
	}

	//UART: interface_context->uart

	return ER_SUCCESS;
}

error_t serial_recv(void * context, uint8_t * data, uint32_t * len)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) context;

	//copy data using DMA
	if(*len > interface_context->rx_data_len) {
		*len = interface_context->rx_data_len;
	}

	//dma_copy(data, interface_context->rx_data, *len);

	interface_context->rx_data_len -= *len;

	return ER_SUCCESS;
}

error_t serial_handle_data(void * if_context, void * dem_context)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) if_context;
	serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) dem_context;

	return ER_SUCCESS;
}



/* END */
