/*  Title		: H3LS331DL
 *  Filename	: H3LS331DL.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: device driver for H3LS331DL
 */

#ifndef H3LS331DL_H
#define H3LS331DL_H



/**********************
 *  INCLUDES
 **********************/

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

device_t * i2c_get_accelerometer(void);

util_error_t i2c_sensor_init(void);


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* H3LS331DL_H */

/* END */
