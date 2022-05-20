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
#include <device/device.h>
#include <device/i2c_sensor.h>

#include <control.h>
#include <feedback/led.h>
#include <feedback/buzzer.h>

#include <abstraction/gpio.h>

/**********************
 *	CONSTANTS
 **********************/

#define CONTROL_HEART_BEAT	200


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
	static const TickType_t period = pdMS_TO_TICKS(500);
	last_wake_time = xTaskGetTickCount();

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);



	device_interface_t * serial_interface = serial_get_feedback_interface();

	i2c_sensor_init();

	device_t * i2c_accelerometer = i2c_get_accelerometer();

	static uint8_t char_buffer[64];
	static uint16_t val = 0;
	static uint8_t proxenete = 0;

	for(;;) {

		//uint16_t len = sprintf(char_buffer, "salut: %d\n\r", val++);
		//device_interface_send(serial_interface, char_buffer, len);

		static uint8_t data;
		device_read_u8(i2c_accelerometer, 0x0F, &data);

		if(val == 0) {
			gpio_set(GPIOA, GPIO_PIN_1);
			gpio_clr(GPIOA, GPIO_PIN_2);
			gpio_clr(GPIOA, GPIO_PIN_3);
			gpio_set(GPIOC, GPIO_PIN_4);
			gpio_clr(GPIOC, GPIO_PIN_5);
		} else if (val == 1) {
			gpio_clr(GPIOA, GPIO_PIN_1);
			gpio_set(GPIOA, GPIO_PIN_2);
			gpio_clr(GPIOA, GPIO_PIN_3);
			gpio_clr(GPIOC, GPIO_PIN_4);
			gpio_set(GPIOC, GPIO_PIN_5);
		} else {
			gpio_clr(GPIOA, GPIO_PIN_1);
			gpio_clr(GPIOA, GPIO_PIN_2);
			gpio_set(GPIOA, GPIO_PIN_3);
			gpio_set(GPIOC, GPIO_PIN_4);
			gpio_set(GPIOC, GPIO_PIN_5);
		}
		val++;
		if(val==3) {
			val=0;
		}

		if(!gpio_get(GPIOF, GPIO_PIN_11)) {
			if(!proxenete) {
				buzzer_enable();
				proxenete = 1;
			} else {
				buzzer_disable();
				proxenete = 0;
			}

		}



		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */
