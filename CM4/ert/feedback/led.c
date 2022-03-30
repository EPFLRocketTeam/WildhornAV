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

#define LED_MAX			(0xfff)



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

void led_rgb_init(void) {
	LED_TIM.Instance->ARR = LED_MAX;
	LED_TIM.Instance->CCR1 = 0;
	LED_TIM.Instance->CCR2 = 0;
	LED_TIM.Instance->CCR3 = 0;
	HAL_TIMEx_PWMN_Start(&LED_TIM, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&LED_TIM, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&LED_TIM, TIM_CHANNEL_3);
}

void led_rgb_set_color(uint8_t r, uint8_t g, uint8_t b) {
	LED_TIM.Instance->CCR1 = r;
	LED_TIM.Instance->CCR2 = g;
	LED_TIM.Instance->CCR3 = b;
}


/* END */


