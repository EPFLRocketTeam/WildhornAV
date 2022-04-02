/*  Title       : UART
 *  Filename    : uart.h
 *  Author      : iacopo sprenger
 *  Date        : 02.04.2022
 *  Version     : 0.1
 *  Description : uart hardware abstraction
 */

#ifndef UART_H
#define UART_H



/**********************
 *  INCLUDES
 **********************/
#include <main.h>
#include <stdint.h>
#include <util.h>

/**********************
 *  CONSTANTS
 **********************/


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

void uart_interrupt_handler(UART_HandleTypeDef * uart);

__weak void uart_idle_handler(UART_HandleTypeDef * uart);


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* DMA_H */

/* END */
