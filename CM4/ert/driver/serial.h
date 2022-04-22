/*  Title       : Serial
 *  Filename    : serial.h
 *  Author      : iacopo sprenger
 *  Date        : 02.04.2022
 *  Version     : 0.1
 *  Description : serial interface for device driver
 */

#ifndef SERIAL_H
#define SERIAL_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <device/device.h>
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

error_t serial_init(void);

error_t serial_feedback_init(void);

device_deamon_t * serial_get_deamon(void);

device_interface_t * serial_get_feedback_interface(void);




#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SERIAL_H */

/* END */
