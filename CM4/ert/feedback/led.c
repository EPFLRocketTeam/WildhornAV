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

typedef enum led_blick_state {
	LED_ON,
	LED_FAINT,
	LED_OFF
}led_blink_state_t;




/**********************
 *	VARIABLES
 **********************/

static led_blink_state_t blink_sequence[] = {
		LED_ON,
		LED_FAINT,
		LED_ON,
		LED_FAINT,
		LED_ON,
		LED_OFF
};

static const int blink_sequence_len = sizeof(blink_sequence)/sizeof(led_blink_state_t);

static led_color_t color_sequence[] =  {
		led_green,
		led_red,
		led_blue,
		led_red,
		led_green
};

static const int color_sequence_len = sizeof(color_sequence)/sizeof(led_color_t);

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
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_SET);

}

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

void led_rgb_set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	LED_TIM.Instance->CCR1 = r;
	LED_TIM.Instance->CCR2 = g;
	LED_TIM.Instance->CCR3 = b;
}

void led_rgb_set_color(led_color_t color) {
	LED_TIM.Instance->CCR1 = color.r;
	LED_TIM.Instance->CCR2 = color.g;
	LED_TIM.Instance->CCR3 = color.b;
}

void led_rgb_thread(void * arg) {
	static TickType_t last_wake_time;
	static TickType_t period = pdMS_TO_TICKS(500);

	led_rgb_init();

	led_rgb_set_color(led_blue);

	last_wake_time = xTaskGetTickCount();

	static uint16_t seq = 0;
	static uint16_t col = 0;

	for(;;) {

		switch(blink_sequence[seq]) {
		case LED_ON:
			period = pdMS_TO_TICKS(500);
			led_rgb_set_color(color_sequence[col]);
			break;
		case LED_FAINT:
			period = pdMS_TO_TICKS(100);
			led_rgb_set_rgb(LED_BLACK);
			break;
		case LED_OFF:
			period = pdMS_TO_TICKS(500);
			led_rgb_set_rgb(LED_BLACK);
			break;
		}

		seq++;
		if(!(seq < blink_sequence_len)) {
			seq = 0;
		}

		col++;
		if(!(col < color_sequence_len)) {
			col = 0;
		}

		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */


