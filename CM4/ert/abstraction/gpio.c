/*  Title		: GPIO
 *  Filename	: gpio.c
 *	Author		: iacopo sprenger
 *	Date		: 30.03.2021
 *	Version		: 0.1
 *	Description	: GPIO hardware abstraction
 */

/**********************
 *	INCLUDES
 **********************/

#include "gpio.h"

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

void gpio_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR = GPIO_Pin;
}

void gpio_clr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
	GPIOx->BSRR = GPIO_Pin<<16;
}

/* END */
