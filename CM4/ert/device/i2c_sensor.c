/*  Title		: H3LS331DL
 *  Filename	: H3LS331DL.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: device driver for H3LS331DL
 */

/**********************
 *	INCLUDES
 **********************/
#include <main.h>
#include <device/device.h>
#include <device/i2c_sensor.h>
#include <driver/i2c.h>
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

typedef struct i2c_sensor_context {
	uint8_t device_address;
}i2c_sensor_context_t;


/**********************
 *	VARIABLES
 **********************/




static device_t i2c_accelerometer_device;
static device_t i2c_gyroscope_device;
static device_t i2c_barometer_device;

static i2c_sensor_context_t i2c_accelerometer_device_context = {
		.device_address = 0x68
};

static i2c_sensor_context_t i2c_gyroscope_device_context = {
		.device_address = 0x68
};

static i2c_sensor_context_t i2c_barometer_device_context = {
		.device_address = 0x18
};

/**********************
 *	PROTOTYPES
 **********************/

util_error_t read_reg(void * context, device_interface_t* dev, uint32_t address, uint8_t * data, uint32_t data_len);

util_error_t write_reg(void * context, device_interface_t* dev, uint32_t address, uint8_t * data, uint32_t data_len);


/**********************
 *	DECLARATIONS
 **********************/

device_t * i2c_get_accelerometer(void) {
	return &i2c_accelerometer_device;
}

util_error_t i2c_sensor_init(void) {

	device_interface_t * i2c_sensor_interface = i2c_get_sensor_interface();

	device_create((void*) &i2c_accelerometer_device, &i2c_accelerometer_device_context, i2c_sensor_interface, read_reg, write_reg);

	return ER_SUCCESS;

}


util_error_t read_reg(void* context, device_interface_t* dev, uint32_t address, uint8_t * data, uint32_t data_len) {
	i2c_interface_context_t * i2c_context = (i2c_interface_context_t *) dev->context;
	i2c_sensor_context_t * dev_context = (i2c_sensor_context_t *) context;
	HAL_I2C_Mem_Read_IT(i2c_context->i2c, dev_context->device_address, (uint8_t) address, sizeof(uint8_t), data, sizeof(uint8_t));

	return ER_SUCCESS;
}

util_error_t write_reg(void* context, device_interface_t* dev, uint32_t address, uint8_t * data, uint32_t data_len) {
	i2c_interface_context_t * i2c_context = (i2c_interface_context_t *) dev->context;
	i2c_sensor_context_t * dev_context = (i2c_sensor_context_t *) context;
	HAL_I2C_Mem_Write_IT(i2c_context->i2c, dev_context->device_address, (uint8_t) address, sizeof(uint8_t), data, sizeof(uint8_t));

	return ER_SUCCESS;
}

/* END */
