/*  Title		: Gyroscope
 *  Filename	: gyroscope.h
 *	Author		: iacopo sprenger
 *	Date		: 10.06.2022
 *	Version		: 0.1
 *	Description	: gyroscope setup and acquisition
 */

#ifndef GYROSCOPE_H
#define GYROSCOPE_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <util.h>

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

util_error_t gyroscope_init(void);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* GYROSCOPE_H */

/* END */
