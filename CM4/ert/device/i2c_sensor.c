/*  Title		: i2c_sensor
 *  Filename	: i2c_sensor.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: device driver for i2c sensors
 */

/**********************
 *	INCLUDES
 **********************/
#include <main.h>
#include <device/device.h>
#include <device/i2c_sensor.h>
#include <driver/i2c.h>
#include <util.h>
#include <string.h>
/**********************
 *	CONSTANTS
 **********************/

#define TEMP_DATA_LEN	32


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

util_error_t i2c_sensor_read_reg(void* context, device_interface_t * interface, uint32_t addr, uint8_t * data, uint32_t len);
util_error_t i2c_sensor_write_reg(void* context, device_interface_t * interface, uint32_t addr, uint8_t * data, uint32_t len);


/**********************
 *	DECLARATIONS
 **********************/

device_t * i2c_sensor_get_accelerometer(void) {
	return &i2c_accelerometer_device;
}

device_t * i2c_sensor_get_gyroscope(void) {
	return &i2c_gyroscope_device;
}

device_t * i2c_sensor_get_barometer(void) {
	return &i2c_barometer_device;
}

util_error_t i2c_sensor_init(void) {

	device_interface_t * i2c_sensor_interface = i2c_get_sensor_interface();

	device_create((void*) &i2c_accelerometer_device, &i2c_accelerometer_device_context, i2c_sensor_interface, i2c_sensor_read_reg, i2c_sensor_write_reg);

	return ER_SUCCESS;

}

/**
 * @brief Function used to send data to a sensor
 */
util_error_t i2c_sensor_read_reg(void* context, device_interface_t * interface, uint32_t addr, uint8_t * data, uint32_t len) {
	i2c_sensor_context_t * ctx = (i2c_sensor_context_t *) context;
	util_error_t error = ER_SUCCESS;
	uint8_t i2c_addr = ctx->device_address;
	uint8_t temp_data[TEMP_DATA_LEN] = {0};
	temp_data[0] = i2c_addr;
	len += 1;
	temp_data[1] = addr & 0xff; //register address
	error |= interface->send(interface->context, temp_data, len);
	error |= interface->recv(interface->context, temp_data, &len);
	memcpy(data, temp_data+1, len-1); //copy only the received data (w/o dev addr)
	return error;
}

util_error_t i2c_sensor_write_reg(void* context, device_interface_t * interface, uint32_t addr, uint8_t * data, uint32_t len) {
	i2c_sensor_context_t * ctx = (i2c_sensor_context_t *) context;
	util_error_t error = ER_SUCCESS;
	uint8_t i2c_addr = ctx->device_address;
	uint8_t temp_data[TEMP_DATA_LEN] = {0};
	temp_data[0] = i2c_addr;
	len += 1;
	temp_data[1] = addr & 0xff; //register address
	error |= interface->send(interface->context, temp_data, len);
	memcpy(temp_data+1, data, len-1); //copy data to temp array
	error |= interface->send(interface->context, temp_data, len);
	return error;
}



/* END */
