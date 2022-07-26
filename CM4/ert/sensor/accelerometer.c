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

void accelerometer_process_data(accelerometer_data_t * data, uint16_t range) {
	for (uint8_t i = 0; i < ACC_AXIS_COUNT; i++) {
		data->processed[i] = ((int32_t)data->raw[i] * range) >> 15;
	}
}

util_error_t accelerometer_read_data(device_t * acc, accelerometer_data_t * data) {
	//i2c_sensor_context_t * context = (i2c_sensor_context_t *) acc->context;
	util_error_t error = ER_SUCCESS;
	uint8_t tmp[6];
	error |= device_read(acc, OUT_X_L, tmp, 6);
	data->raw[ACC_X] = tmp[0] | (tmp[1]<<8);
	data->raw[ACC_Y] = tmp[2] | (tmp[3]<<8);
	data->raw[ACC_Z] = tmp[4] | (tmp[5]<<8);

	return error;
}

/**
 * @brief Initialize accelerometers
 */
util_error_t accelerometer_init(device_t * acc) {
	util_error_t error = ER_SUCCESS;
	uint8_t data; //read sensor magic number
	error |= device_read_u8(acc, WHO_AM_I, &data);

	if(data != WHO_AM_I_MAGIC) {
		return error | ER_RESSOURCE_ERROR;
	}

	//initialize sensor
	//enable all axis of the accelerometer at 50Hz
	error |= device_write_u8(acc, CTRL_REG1, 0b00100111);
	//enable internal high pass filter with cutoff=8
	error |= device_write_u8(acc, CTRL_REG2, 0b00010000);
	//enable DBU and change endianess, +/- 100g
	error |= device_write_u8(acc, CTRL_REG4, 0b11000000);


	return error;
}

/* END */
