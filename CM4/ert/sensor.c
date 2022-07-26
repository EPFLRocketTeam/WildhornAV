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
#include <od/od.h>
/**********************
 *	CONSTANTS
 **********************/

//TODO: check if this is short/long enough
#define I2C_SENSOR_HEART_BEAT	500


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

static device_interface_t * hostproc_feedback;


static uint8_t calibration;

//data

static accelerometer_data_t acc_data;



/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

void sensor_i2c_thread(__attribute__((unused)) void * arg) {
	static TickType_t last_wake_time;
	static const TickType_t period = pdMS_TO_TICKS(I2C_SENSOR_HEART_BEAT);
	last_wake_time = xTaskGetTickCount();

	//get devices
	accelerometer = i2c_sensor_get_accelerometer();
	gyroscope = i2c_sensor_get_gyroscope();
	barometer = i2c_sensor_get_barometer();

	hostproc_feedback = hostproc_get_feedback_interface();

	//init
	accelerometer_init(accelerometer);
	gyroscope_init(gyroscope);
	barometer_init(barometer);

	//manual calibration only:
	calibration = 0;

	//mainloop
	for(;;) {

		if(!calibration) {
			accelerometer_read_data(accelerometer, &acc_data);
			accelerometer_process_data(&acc_data, 10000);
		} else {
			//calibration steps
		}

		//send data to hostproc for verif

		static char message[1024];

		uint32_t msg_len = sprintf(message, "Accelerometer: %d | %d | %d\n", acc_data.processed[ACC_X], acc_data.processed[ACC_Y], acc_data.processed[ACC_Z]);

		device_interface_send(hostproc_feedback, (uint8_t *)message, msg_len);
		led_rgb_set_rgb(0xff, 0x00, 0x00);

		vTaskDelayUntil( &last_wake_time, period );
	}

}

/* END */
