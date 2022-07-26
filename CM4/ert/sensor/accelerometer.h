/*  Title		: Accelerometer
 *  Filename	: accelerometer.h
 *	Author		: iacopo sprenger
 *	Date		: 10.06.2022
 *	Version		: 0.1
 *	Description	: accelerometer setup and acquisition
 */

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <util.h>
#include <device/device.h>

/**********************
 *  CONSTANTS
 **********************/

#define ACC_AXIS_COUNT	3



/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef enum accelerometer_axis {
	ACC_X,
	ACC_Y,
	ACC_Z
}accelerometer_axis_t;


typedef struct accelerometer_data {
	int16_t raw[ACC_AXIS_COUNT];
	int16_t	processed[ACC_AXIS_COUNT];
}accelerometer_data_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

void accelerometer_process_data(accelerometer_data_t * data, uint16_t range);
util_error_t accelerometer_calibrate(device_t * acc, accelerometer_data_t * data);
util_error_t accelerometer_read_data(device_t * acc, accelerometer_data_t * data);
util_error_t accelerometer_init(device_t * acc);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* ACCELEROMETER_H */

/* END */
