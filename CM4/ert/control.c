/*  Title		: Control
 *  Filename	: control.c
 *	Author		: iacopo sprenger
 *	Date		: 20.01.2022
 *	Version		: 0.1
 *	Description	: control
 */

/**********************
 *	INCLUDES
 **********************/

#include <main.h>
#include <gpio.h>
#include <usart.h>


#include <cmsis_os.h>



#include <control.h>
#include <feedback/led.h>
#include <abstraction/gpio.h>

/**********************
 *	CONSTANTS
 **********************/

#define CONTROL_HEART_BEAT	100


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

void control_thread(void * arg) {
	static TickType_t last_wake_time;
	static const TickType_t period = pdMS_TO_TICKS(CONTROL_HEART_BEAT);

	led_rgb_init();

	led_rgb_set_color(LED_BLUE);

	last_wake_time = xTaskGetTickCount();

	static uint8_t dummy = 0;

	//GPIO init leds

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStructure);



	for(;;) {

		if(dummy) {
			led_rgb_set_color(LED_RED);
			gpio_set(GPIOB, GPIO_PIN_6);
			gpio_clr(GPIOD, GPIO_PIN_13);
			gpio_set(GPIOD, GPIO_PIN_14);
			gpio_clr(GPIOD, GPIO_PIN_15);
		} else {
			led_rgb_set_color(LED_GREEN);
			gpio_clr(GPIOB, GPIO_PIN_6);
			gpio_set(GPIOD, GPIO_PIN_13);
			gpio_clr(GPIOD, GPIO_PIN_14);
			gpio_set(GPIOD, GPIO_PIN_15);
		}



		uint8_t string[] = "I am alive\n\r        ";

		HAL_UART_Transmit(&huart2, string, 15, 200);


		dummy = !dummy;





		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */
