/*  Title		: I2C Acquisition
 *  Filename	: i2c_acq.h
 *	Author		: iacopo sprenger
 *	Date		: 13.07.2021
 *	Version		: 0.1
 *	Description	: Thread grouping all the sensors on the same I2C bus.
 */

#ifndef I2C_ACQ_H
#define I2C_ACQ_H



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

void i2c_acq_thread(__attribute__((unused)) void * arg);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* I2C_ACQ_H */

/* END */
