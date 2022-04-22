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

#include <driver/serial.h>
#include <driver/device.h>

#include <control.h>
#include <feedback/led.h>
#include <abstraction/gpio.h>
#include <abstraction/dma.h>

/**********************
 *	CONSTANTS
 **********************/

#define CONTROL_HEART_BEAT	2000


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

	led_rgb_set_color(LED_TEAL);

	last_wake_time = xTaskGetTickCount();

	static uint8_t dummy = 0;

	serial_init();

	device_interface_t * serial_interface = serial_get_interface();

	//GPIO init leds




	dma2_init_scheduler();

	dma_scheduler_dev_t * sched = dma2_get_scheduler();

	for(;;) {

		if(dummy % 4 == 0) {
			led_rgb_set_color(LED_RED);
			gpio_set(GPIOB, GPIO_PIN_6);
			gpio_clr(GPIOD, GPIO_PIN_13);
			gpio_clr(GPIOD, GPIO_PIN_14);
			gpio_clr(GPIOD, GPIO_PIN_15);
		} else if(dummy % 4 == 1) {
			led_rgb_set_color(LED_GREEN);
			gpio_clr(GPIOB, GPIO_PIN_6);
			gpio_set(GPIOD, GPIO_PIN_13);
			gpio_clr(GPIOD, GPIO_PIN_14);
			gpio_clr(GPIOD, GPIO_PIN_15);
		} else if(dummy % 4 == 2) {
			led_rgb_set_color(LED_BLUE);
			gpio_clr(GPIOB, GPIO_PIN_6);
			gpio_clr(GPIOD, GPIO_PIN_13);
			gpio_set(GPIOD, GPIO_PIN_14);
			gpio_clr(GPIOD, GPIO_PIN_15);
		} else {
			led_rgb_set_color(LED_BLACK);
			gpio_clr(GPIOB, GPIO_PIN_6);
			gpio_clr(GPIOD, GPIO_PIN_13);
			gpio_clr(GPIOD, GPIO_PIN_14);
			gpio_set(GPIOD, GPIO_PIN_15);
		}
		dummy++;

		device_interface_send(serial_interface, "hello\r\n", 7);




		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */
