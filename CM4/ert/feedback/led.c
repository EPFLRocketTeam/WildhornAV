/*  Title		: Led
 *  Filename	: led.c
 *	Author		: iacopo sprenger
 *	Date		: 20.01.2021
 *	Version		: 0.1
 *	Description	: rgb led control
 */

/**********************
 *	INCLUDES
 **********************/

#include "led.h"
#include <main.h>
#include <tim.h>

/**********************
 *	CONFIGURATION
 **********************/

#define LED_TIM			htim3



/**********************
 *	CONSTANTS
 **********************/

#define LED_MAX			(0xff)



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


void led_feedback_init(void) {
	//GPIO init leds
	//feedback leds located on socket 3

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

}

void led_rgb_init(void) {
	LED_TIM.Instance->ARR = LED_MAX;
	LED_TIM.Instance->CCR1 = 0;
	LED_TIM.Instance->CCR2 = 0;
	LED_TIM.Instance->CCR3 = 0;
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_3);
}

void led_rgb_set_color(uint8_t r, uint8_t g, uint8_t b) {
	LED_TIM.Instance->CCR1 = r;
	LED_TIM.Instance->CCR2 = g;
	LED_TIM.Instance->CCR3 = b;
}


/* END */


