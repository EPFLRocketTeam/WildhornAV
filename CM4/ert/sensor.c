/*  Title		: Sensor Acquisition
 *  Filename	: sensor.c
 *	Author		: iacopo sprenger
 *	Date		: 13.07.2021
 *	Version		: 0.1
 *	Description	: Thread grouping all the sensors on the same I2C bus.
 */

/**********************
 *	INCLUDES
 **********************/

#include <sensor.h>

#include <main.h>
#include <cmsis_os.h>

#include <device/i2c_sensor.h>
#include <sensor/accelerometer.h>
#include <sensor/gyroscope.h>
#include <sensor/barometer.h>
/**********************
 *	CONSTANTS
 **********************/

//TODO: check if this is short/long enough
#define I2C_ACQ_HEART_BEAT	100


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/


static device_t * accelerometer;
static device_t * gyroscope;
static device_t * barometer;



/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

void sensor_i2c_thread(__attribute__((unused)) void * arg) {
	static TickType_t last_wake_time;
	static const TickType_t period = pdMS_TO_TICKS(I2C_ACQ_HEART_BEAT);
	last_wake_time = xTaskGetTickCount();

	//get devices
	accelerometer = i2c_sensor_get_accelerometer();
	gyroscope = i2c_sensor_get_gyroscope();
	barometer = i2c_sensor_get_barometer();

	//init
	accelerometer_init(accelerometer);
	gyroscope_init(gyroscope);
	barometer_init(barometer);

	//mainloop
	for(;;) {


		vTaskDelayUntil( &last_wake_time, period );
	}

}

/* END */
