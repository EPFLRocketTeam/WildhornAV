/*  Title		: Barometer
 *  Filename	: barometer.h
 *	Author		: iacopo sprenger
 *	Date		: 10.06.2022
 *	Version		: 0.1
 *	Description	: barometer setup and acquisition
 */

#ifndef BAROMETER_H
#define BAROMETER_H



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

util_error_t barometer_init(device_t * baro);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* BAROMETER_H */

/* END */
