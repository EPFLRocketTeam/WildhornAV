/*  Title		: barometer
 *  Filename	: barometer.c
 *	Author		: iacopo sprenger
 *	Date		: 10.06.2022
 *	Version		: 0.1
 *	Description	: barometer setup and acquisition
 */

/**********************
 *	INCLUDES
 **********************/

#include <sensor/barometer.h>
#include <device/i2c_sensor.h>
#include <feedback/led.h>
#include <util.h>

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

static device_t * barometer;


/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

/**
 * @brief Initialize barometers
 */
util_error_t barometer_init(void) {

	barometer = i2c_sensor_get_barometer();

	//Barometer does not have an ID

	//initialize sensor

	return ER_SUCCESS;
}

/* END */
