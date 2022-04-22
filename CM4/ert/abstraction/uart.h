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
#include "dma.h"

/**********************
 *  CONSTANTS
 **********************/

#define UART_SAMPLES_PER_BIT	16
#define UART_DATA_BUFFER		64


/**********************
 *  MACROS
 **********************/

#define UART_PRESCALER_TO_DIV(prescaler) \
  (((prescaler) == UART_PSCALER_DIV1)   ? 1U :       \
   ((prescaler) == UART_PSCALER_DIV2)   ? 2U :       \
   ((prescaler) == UART_PSCALER_DIV4)   ? 4U :       \
   ((prescaler) == UART_PSCALER_DIV6)   ? 6U :       \
   ((prescaler) == UART_PSCALER_DIV8)   ? 8U :       \
   ((prescaler) == UART_PSCALER_DIV10)  ? 10U :      \
   ((prescaler) == UART_PSCALER_DIV12)  ? 12U :      \
   ((prescaler) == UART_PSCALER_DIV16)  ? 16U :      \
   ((prescaler) == UART_PSCALER_DIV32)  ? 32U :      \
   ((prescaler) == UART_PSCALER_DIV64)  ? 64U :      \
   ((prescaler) == UART_PSCALER_DIV128) ? 128U :     \
   ((prescaler) == UART_PSCALER_DIV256) ? 256U : 1U)


/**********************
 *  TYPEDEFS
 **********************/

typedef enum uart_prescaler {
	UART_PSCALER_DIV1 	= 0x00000000U,
	UART_PSCALER_DIV2 	= 0x00000001U,
	UART_PSCALER_DIV4 	= 0x00000002U,
	UART_PSCALER_DIV6 	= 0x00000003U,
	UART_PSCALER_DIV8 	= 0x00000004U,
	UART_PSCALER_DIV10	= 0x00000005U,
	UART_PSCALER_DIV12	= 0x00000006U,
	UART_PSCALER_DIV16  = 0x00000007U,
	UART_PSCALER_DIV32  = 0x00000008U,
	UART_PSCALER_DIV64  = 0x00000009U,
	UART_PSCALER_DIV128 = 0x0000000AU,
	UART_PSCALER_DIV256 = 0x0000000BU
}uart_prescaler_t;

typedef struct uart_config {
	uint32_t baudrate;
	uint32_t uart_clock_freq;
	uart_prescaler_t prescaler;

}uart_config_t;

typedef struct uart_dev {
	USART_TypeDef * uart;
	util_buffer_u8_t rx_buffer;
	util_buffer_u8_t tx_buffer;
	uint8_t rx_data[UART_DATA_BUFFER];
	uint8_t tx_data[UART_DATA_BUFFER];
	dma_stream_dev_t * tx_stream;
	dma_stream_dev_t * rx_stream;
	uint16_t dmamux_tx_request;
	uint16_t dmamux_rx_request;
}uart_dev_t;


/**********************
 *  VARIABLES
 **********************/




/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

error_t uart_init(uart_dev_t * dev, uart_config_t config);
error_t uart_receive_DMA(uart_dev_t * dev, uint8_t * buffer, uint16_t length);
error_t uart_receive_IT(uart_dev_t * dev);

uart_dev_t * uart_get_usart2(void);
uart_dev_t * uart_get_usart3(void);
uart_dev_t * uart_get_usart6(void);



#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* DMA_H */

/* END */
