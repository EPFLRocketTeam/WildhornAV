/*  Title		: i2c_sensor
 *  Filename	: i2c_sensor.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: device driver for i2c sensors
 */

#ifndef I2C_SENSOR_H
#define I2C_SENSOR_H



/**********************
 *  INCLUDES
 **********************/

#include <device/device.h>
#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

device_t * i2c_sensor_get_accelerometer(void);
device_t * i2c_sensor_get_gyroscope(void);
device_t * i2c_sensor_get_barometer(void);

util_error_t i2c_sensor_init(void);


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* I2C_SENSOR_H */

/* END */
