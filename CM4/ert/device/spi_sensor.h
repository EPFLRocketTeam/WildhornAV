/*  Title		: spi_sensor
 *  Filename	: spi_sensor.h
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: device driver for spi sensors
 */

#ifndef SPI_SENSOR_H
#define SPI_SENSOR_H



/**********************
 *  INCLUDES
 **********************/

#include <device/device.h>
#include <stdint.h>

#include <sensor/accelerometer.h>
#include <sensor/barometer.h>
#include <sensor/gyroscope.h>

/**********************
 *  CONSTANTS
 **********************/


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

// pas sur pour les données de capteur ici...
typedef struct spi_sensor_context {
	union data {
		accelerometer_data_t acc_data;
		barometer_data_t baro_data;
		gyroscope_data_t gyro_data;
	} data;
}spi_sensor_context_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

device_t * spi_sensor_get_accelerometer(void);
device_t * spi_sensor_get_gyroscope(void);
device_t * spi_sensor_get_barometer(void);

util_error_t spi_sensor_init(void);


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SPI_SENSOR_H */

/* END */
