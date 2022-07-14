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

/**********************
 *	CONSTANTS
 **********************/

#define WHO_AM_I		0x0F
#define WHO_AM_I_MAGIC	0x32
#define CTRL_REG1		0x20
#define CTRL_REG2		0x21
#define CTRL_REG3		0x22
#define CTRL_REG4		0x23
#define CTRL_REG5		0x24
#define HP_FILTER_RESET	0x25
#define REFERENCE		0x26
#define STATUS_REG		0x27
#define OUT_X_L			0x28
#define OUT_X_H			0x29
#define OUT_Y_L			0x2A
#define OUT_Y_H			0x2B
#define OUT_Z_L			0x2C
#define OUT_Z_H			0x2D
#define INT1_CFG		0x30
#define INT1_SRC		0x31
#define INT1_THS		0x32
#define INT1_DURATION	0x33
#define INT2_CFG		0x34
#define INT2_SRC		0x35
#define INT2_THS		0x36
#define INT2_DURATION	0x37


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

util_error_t accelerometer_calibrate(device_t * acc, accelerometer_data_t * data) {

}

util_error_t accelerometer_read_data(device_t * acc, accelerometer_data_t * data) {

}

/**
 * @brief Initialize accelerometers
 */
util_error_t accelerometer_init(device_t * acc) {

	uint8_t data; //read sensor magic number
	device_read_u8(acc, WHO_AM_I, &data);

	if(data != WHO_AM_I_MAGIC) {
		return ER_RESSOURCE_ERROR;
	}

	//initialize sensor
	//write to ctrl1
	//write to ctrl3

	return ER_SUCCESS;
}

/* END */
