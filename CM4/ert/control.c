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
	static const TickType_t period = pdMS_TO_TICKS(2000);
	last_wake_time = xTaskGetTickCount();



	device_interface_t * serial_interface = serial_get_feedback_interface();

	i2c_sensor_init();

	device_t * i2c_accelerometer = i2c_get_accelerometer();

	static uint8_t char_buffer[64];
	static uint16_t val = 0;

	for(;;) {

		uint16_t len = sprintf(char_buffer, "salut: %d\n\r", val++);
		device_interface_send(serial_interface, char_buffer, len);

		static uint8_t data;
		device_read_u8(i2c_accelerometer, 0x0F, &data);

		data;




		vTaskDelayUntil( &last_wake_time, period );
	}
}


/* END */
