/*  Title		: Messenger
 *  Filename	: messenger.c
 *	Author		: iacopo sprenger
 *	Date		: 30.01.2021
 *	Version		: 0.1
 *	Description	: messenger to communicate with linux kernel on CA7
 */

#ifndef MESSENGER_H
#define MESSENGER_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <virt_uart.h>
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

device_interface_t * hostproc_get_interface(void);
device_t * hostproc_get_device(void);

util_error_t hostproc_init(void);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* MESSENGER_H */

/* END */
