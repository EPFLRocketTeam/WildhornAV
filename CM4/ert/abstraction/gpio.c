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
#include <util.h>

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



uint8_t gpio_get(GPIO_TypeDef* gpio, uint16_t pin) {
	return gpio->IDR & pin ? 1 : 0;
}

void gpio_set(GPIO_TypeDef * gpio, uint16_t pin) {
	gpio->BSRR = pin;
}

void gpio_clr(GPIO_TypeDef * gpio, uint16_t pin) {
	gpio->BSRR = pin<<16;
}

void gpio_cfg(GPIO_TypeDef * gpio, uint16_t pins, gpio_config_t cfg) {
	for (uint16_t position = 0; position < 16; position++) {
		uint16_t pin = 0b1<<position;
		if(pins & pin) {
			WRITE_IN_REG(gpio->ODR, pin, 0); //clear output
			WRITE_IN_REG(gpio->OTYPER, pin, cfg.drive<<position); //write drive mode
			WRITE_IN_REG(gpio->OSPEEDR, 0b11<<(position*2), cfg.speed<<(position*2));
			WRITE_IN_REG(gpio->MODER, 0b11<<(position*2), cfg.mode<<(position*2));
			if(position < 8) {
				WRITE_IN_REG(gpio->AFR[0], 0b1111<<(position*4), cfg.alternate<<(position*4));
			} else {
				WRITE_IN_REG(gpio->AFR[1], 0b1111<<((position-8)*4), cfg.alternate<<((position-8)*4));
			}

		}
	}
}

/* END */
