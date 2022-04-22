/*  Title       : GPIO
 *  Filename    : gpio.h
 *  Author      : iacopo sprenger
 *  Date        : 30.03.2021
 *  Version     : 0.1
 *  Description : gpio hardware abstraction
 */

#ifndef GPIO_H
#define GPIO_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <main.h>

/**********************
 *  CONSTANTS
 **********************/



/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef enum gpio_drive {
	GPIO_DRIVE_PP	= 0b0,
	GPIO_DRIVE_OD	= 0b1
}gpio_drive_t;

typedef enum gpio_mode {
	GPIO_MODE_IN  	= 0b00,
	GPIO_MODE_OUT 	= 0b01,
	GPIO_MODE_ALT  	= 0b10,
	GPIO_MODE_ANA	= 0b11
}gpio_mode_t;

typedef enum gpio_bias {
	GPIO_BIAS_NONE 	= 0b00,
	GPIO_BIAS_HIGH 	= 0b01,
	GPIO_BIAS_LOW	= 0b10
}gpio_bias_t;



typedef struct gpio_config {
	gpio_drive_t drive;
	gpio_mode_t mode;
	gpio_bias_t bias;
	uint8_t speed;
	uint8_t alternate;
}gpio_config_t;



/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif


void gpio_set(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void gpio_clr(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t gpio_get(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void gpio_cfg(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, gpio_config_t cfg);



#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* GPIO_H */

/* END */
