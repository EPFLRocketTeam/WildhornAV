/*  Title		: UART
 *  Filename	: uart.c
 *	Author		: iacopo sprenger
 *	Date		: 02.04.2022
 *	Version		: 0.1
 *	Description	: uart hardware abstraction
 */

/**********************
 *	INCLUDES
 **********************/

#include "uart.h"
#include <usart.h>

/**********************
 *	CONSTANTS
 **********************/


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/


/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

error_t uart_init(UART_HandleTypeDef * uart) {
	__HAL_UART_ENABLE_IT(uart, UART_IT_IDLE);

}


void uart_interrupt_handler(UART_HandleTypeDef * uart) {
	if(RESET != __HAL_UART_GET_FLAG(uart, UART_FLAG_IDLE)) {
		__HAL_UART_CLEAR_IDLEFLAG(uart);
		uart_idle_handler(uart);
	}
}

__weak void uart_idle_handler(UART_HandleTypeDef * uart) {
	UNUSED(uart);
}

/* END */
