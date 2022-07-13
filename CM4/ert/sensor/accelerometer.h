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


util_error_t accelerometer_init(device_t * acc);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* ACCELEROMETER_H */

/* END */
