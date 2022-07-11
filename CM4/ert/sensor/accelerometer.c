/*  Title		: Accelerometer
 *  Filename	: accelerometer.c
 *	Author		: iacopo sprenger
 *	Date		: 10.06.2022
 *	Version		: 0.1
 *	Description	: accelerometer setup and acquisition
 */

/**********************
 *	INCLUDES
 **********************/

#include <sensor/accelerometer.h>
#include <device/i2c_sensor.h>

/**********************
 *	CONSTANTS
 **********************/


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/

device_t * accelerometer;


/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

/**
 * @brief Initialize accelerometers
 */
util_error_t accelerometer_init(void) {

	accelerometer = i2c_sensor_get_accelerometer();

	//TODO: put correct magic numbers
	int8_t data; //read sensor magic number
	device_read_i8(accelerometer, 0x68, &data);
	if(data != 0x66) {
		return ER_RESSOURCE_ERROR;
	}

	//initialize sensor

	return ER_SUCCESS;
}

/* END */
