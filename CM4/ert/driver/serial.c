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
#include "device.h"


/**********************
 *	CONSTANTS
 **********************/

#define S1_UART 			huart2
#define S2_UART 			huart3;
#define S3_UART 			huart6;

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

}serial_deamon_context_t;

typedef struct serial_interface_context {
	UART_HandleTypeDef * uart;
	util_buffer_u8_t rx_buffer;
	uint8_t rx_data[SERIAL_BUFFER_LEN];
	uint32_t rx_data_len;
	uint8_t rx_fragment;
	uint8_t tx_data[SERIAL_BUFFER_LEN];


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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	for(uint8_t i = 0; i < serial_deamon.interfaces_count; i++) {
		serial_interface_context_t * serial_context = (serial_interface_context_t *) serial_deamon.interfaces[i]->inst;
		if(serial_context->uart == huart) {
			util_buffer_u8_add(&serial_context->rx_buffer, serial_context->rx_fragment);
			//release semaphore
			break;
		}
	}
}




device_deamon_t * serial_get_deamon(void)
{
	return &serial_deamon;
}

device_interface_t * serial_get_feedback_interface(void)
{
	return &feedback_interface;
}


error_t serial_init(void)
{
	error_t error = ER_SUCCESS;

	//initialize deamon semaphore
	serial_deamon_context.rx_sem = xSemaphoreCreateBinaryStatic(&serial_deamon_context.rx_sem_buffer);


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

		return ER_RESSOURCE_ERROR;
		//TODO: setup reception using DMA


	} else if ( mode == SERIAL_TRANSFER_IT) {
		//setup Interrupt reception byte per byte
		util_buffer_u8_init(&interface_context->rx_buffer, interface_context->rx_data, SERIAL_BUFFER_LEN);

		HAL_UART_Receive_IT(interface_context->uart, &interface_context->rx_fragment, 1);

	}
	return ER_FAILURE;
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

	return ER_SUCCESS;
}


error_t serial_handle_data(void * if_context, void * dem_context)
{
	serial_interface_context_t * interface_context = (serial_interface_context_t *) if_context;
	serial_deamon_context_t * deamon_context = (serial_deamon_context_t *) dem_context;

	return ER_SUCCESS;
}



/* END */
