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
#include "dma.h"
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

uart_dev_t usart2 = {
		.uart = USART2,
		.dmamux_tx_request = STM32_DMAMUX1_USART2_TX,
		.dmamux_rx_request = STM32_DMAMUX1_USART2_RX
};

uart_dev_t usart3 = {
		.uart = USART3
};

uart_dev_t usart6 = {
		.uart = USART6
};


/**********************
 *	PROTOTYPES
 **********************/

void uart_handle_interrupt(uart_dev_t * dev);

void uart_data_ready(uart_dev_t * dev);

/**********************
 *	DECLARATIONS
 **********************/


/*
 * Interrupt handlers
 */

void USART2_IRQHandler(void) {
	uart_handle_interrupt(&usart2);
}

void USART3_IRQHandler(void) {
	uart_handle_interrupt(&usart3);
}

void USART6_IRQHandler(void) {
	uart_handle_interrupt(&usart6);
}


void uart_handle_interrupt(uart_dev_t * dev) {
	//get status
	uint32_t status_flags = dev->uart->ISR;

	if(status_flags & USART_ISR_RXNE_RXFNE) { //data received
		uint8_t data = dev->uart->RDR;
		util_buffer_u8_add(&dev->rx_buffer, data);
		uart_data_ready(dev);
	} else if(status_flags & USART_ISR_IDLE) {
		//do nothing but idle detected
	} else {
		//unexpected state, do nothing
	}

}


/*
 * peripheral specific functions
 */

uart_dev_t * uart_get_usart2(void)
{
	return &usart2;
}

uart_dev_t * uart_get_usart3(void)
{
	return &usart3;
}

uart_dev_t * uart_get_usart6(void)
{
	return &usart6;
}


/*
 * Generic functions
 */

error_t uart_init(uart_dev_t * dev, uart_config_t config)
{
	/* setup uart for:
	 * 8 bits word M = 00
	 * 1 stop bit no parity
	 */

	//setup circular buffer for rx
	util_buffer_u8_init(&dev->rx_buffer, dev->rx_data, UART_DATA_BUFFER);

	//enable uart clock
	dev->uart->CR1 = 0;
	dev->uart->PRESC = config.prescaler;
	uint32_t res_clock_freq = config.uart_clock_freq/UART_PRESCALER_TO_DIV(config.prescaler);
	uint32_t uart_div = (res_clock_freq + (config.baudrate/2))/config.baudrate;
	dev->uart->BRR = uart_div;
	dev->uart->CR2 = 0;
	//enable peripheral
	dev->uart->CR1 |= USART_CR1_UE;

	return ER_SUCCESS;



}

error_t uart_receive_DMA(uart_dev_t * dev, uint8_t * buffer, uint16_t length)
{
	return ER_RESSOURCE_ERROR;
	//setup the dma stream for reception


	//use peripheral flow controller to allow variable size packets


	//enable serial rx dma trigger (last thing)
	dev->uart->CR3 = USART_CR3_DMAR; //enable DMA rx

}

error_t uart_receive_IT(uart_dev_t * dev) {

	//enable RX interrupt
	dev->uart->CR1 |= USART_CR1_RXNEIE;

	dev->uart->CR1 |= USART_CR1_RE;

	return ER_SUCCESS;
}

__weak void uart_data_ready(uart_dev_t * dev) {
	UNUSED(dev);
}

error_t uart_transmit_DMA(uart_dev_t * dev, uint8_t * buffer, uint16_t length) {
	if(!IS_DMA_STREAM_ALL_INSTANCE(dev->tx_stream->dma_stream)) {
		return ER_RESSOURCE_ERROR;
	}
	dma_stream_config_t dma_config;
	dma_config.direction = DMA_STREAM_M2P;
	dma_config.dmamux_request_number = dev->dmamux_rx_request;
	dma_config.m0_addr = (uint32_t) buffer;
	dma_config.transfer_size = length;
	dma_config.peripheral_flow_control = 1;
	dma_config.p_addr = (uint32_t) &(dev->uart->TDR);
	dma_config.priority = 0;

	dma_start_stream(dev->tx_stream, dma_config);

	dev->uart->CR3 = USART_CR3_DMAT;
	dev->uart->CR1 |= USART_CR1_TE;

	return ER_SUCCESS;
}

error_t uart_transmit_IT(uart_dev_t * dev, uint8_t * buffer, uint16_t length) {
	return ER_RESSOURCE_ERROR;
}



/* END */
