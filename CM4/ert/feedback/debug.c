/*  Title		: Debug
 *  Filename	: debug.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: debug interface for computer connection
 *				  will be running inside the serial reception deamon
 *				  The computer can send and or receive information to and from the device
 */

/**********************
 *	INCLUDES
 **********************/

#include <protocol/msv2.h>
#include <feedback/debug.h>
#include <driver/serial.h>

/**********************
 *	CONSTANTS
 **********************/


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/


typedef struct debug_interface_context {
	MSV2_INST_t msv2;


}debug_interface_context_t;


//debug object dictionnary
typedef struct debug_context {

}debug_context_t;

/**********************
 *	VARIABLES
 **********************/

debug_context_t debug_context;
serial_interface_context_t feedback_interface_context;
debug_interface_context_t debug_interface_context;

/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/




/*
 * Setup serial debug protocol
 */
util_error_t debug_init(void){

	util_error_t error = 0;


	msv2_init(&debug_interface_context.msv2);

	serial_feedback_init();

	device_interface_t * feedback_interface = serial_get_feedback_interface();

	device_daemon_t * serial_deamon = serial_get_deamon();


}

/* END */
