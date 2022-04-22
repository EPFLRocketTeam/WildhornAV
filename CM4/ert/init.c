/*  Title		: Initialization
 *  Filename	: init.c
 *	Author		: iacopo sprenger
 *	Date		: 17.04.2022
 *	Version		: 0.1
 *	Description	: hostboard hardware initialization
 */

/**********************
 *	INCLUDES
 **********************/

#include "init.h"
#include <abstraction/gpio.h>
#include <abstraction/uart.h>
#include <abstraction/dma.h>
#include <driver/serial.h>
#include <main.h>

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

void init_hostboard(void)
{

	//init GPIO
	gpio_config_t gpio_config;

	//start GPIO clocks A, B, C, D, E, F

	RCC->MC_AHB4ENSETR = 	RCC_MC_AHB4ENSETR_GPIOAEN | RCC_MC_AHB4ENSETR_GPIOBEN | RCC_MC_AHB4ENSETR_GPIOCEN |
							RCC_MC_AHB4ENSETR_GPIODEN | RCC_MC_AHB4ENSETR_GPIOEEN | RCC_MC_AHB4ENSETR_GPIOFEN;

	//setup GPIO for feedback leds
	gpio_config.mode = GPIO_MODE_OUT;
	gpio_config.drive = GPIO_DRIVE_PP;
	gpio_config.bias = GPIO_BIAS_NONE;
	gpio_config.speed = 3;
	gpio_config.alternate = 0;

	gpio_cfg(GPIOB, GPIO_PIN_6, gpio_config);
	gpio_cfg(GPIOD, GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, gpio_config);

	//setup GPIO for uart

	//uart8 is setup by linux

	//uart2 init

	//uart2 clock enable
	RCC->MC_APB1ENSETR = RCC_MC_APB1ENSETR_USART2EN;



	/*
	 * UART2  GPIO init:
	 * TX on PD5
	 * RX on PD6
	 */
	gpio_config.mode = GPIO_MODE_ALT;
	gpio_config.drive = GPIO_DRIVE_PP;
	gpio_config.bias = GPIO_BIAS_NONE;
	gpio_config.speed = 3;
	gpio_config.alternate = GPIO_AF7_USART2;

	gpio_cfg(GPIOD, GPIO_PIN_5 | GPIO_PIN_6, gpio_config);





	//init DMA

	//dma2 and dmamux clock enable
	RCC->MC_AHB2ENSETR = RCC_MC_AHB2ENSETR_DMA2EN | RCC_MC_AHB2ENSETR_DMAMUXEN;

	dma2_init_scheduler();



	//init serial drivers
	serial_init();

	//init I2C

	//init SPI

	//init ADC



	//init



}

/* END */
