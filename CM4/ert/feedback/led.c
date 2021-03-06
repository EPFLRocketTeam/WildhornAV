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
#include <cmsis_os.h>

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

/**
 * @brief 	Initialize the feedback module
 * @details This will initialize a board to accept a feedback board on
 * 			the S3 socket.
 *
 */
void led_feedback_init(void) {
	//GPIO init leds
	//feedback leds located on socket 3

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);

}

/**
 * @brief 	Initialize the RGB LED.
 * @details Starts the PWM channels connected to the RGB led for user feedback.
 */
void led_rgb_init(void) {

	//make sure GPIO are initialized correctly

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	LED_TIM.Instance->ARR = LED_MAX;
	LED_TIM.Instance->CCR1 = 0;
	LED_TIM.Instance->CCR2 = 0;
	LED_TIM.Instance->CCR3 = 0;
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&LED_TIM, TIM_CHANNEL_3);
}

/**
 * @brief	Set RBG LED color using r, g, b values.
 *
 * @param	r	Red channel value.
 * @param 	g	Green channel value.
 * @param	b	Blue channel value.
 */
void led_rgb_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	LED_TIM.Instance->CCR1 = r;
	LED_TIM.Instance->CCR2 = g;
	LED_TIM.Instance->CCR3 = b;
}

/**
 * @brief	Set RBG LED color using color structure.
 *
 * @param	color	Color structure, defines the color to be set.
 */
void led_rgb_set_color(led_color_t color) {
	LED_TIM.Instance->CCR1 = color.r;
	LED_TIM.Instance->CCR2 = color.g;
	LED_TIM.Instance->CCR3 = color.b;
}


void led_rgb_thread(__attribute__((unused)) void * arg) {
	static TickType_t last_wake_time;
	static TickType_t period = pdMS_TO_TICKS(500);

	led_rgb_init();

	led_rgb_set_color(led_blue);

	last_wake_time = xTaskGetTickCount();

	for(;;) {

		led_rgb_set_color(led_blue);

		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */


