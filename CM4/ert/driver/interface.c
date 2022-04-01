/*  Title		: Generic interface wrapper
 *  Filename	: interface.c
 *	Author		: iacopo sprenger
 *	Date		: 20.03.2021
 *	Version		: 0.1
 *	Description	: 
 */

/**********************
 *	INCLUDES
 **********************/

#include "interface.h"
#include <util.h>

/**********************
 *	CONSTANTS
 **********************/


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/



/**********************
 *	VARIABLES
 **********************/



/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

error_t interface_create(   interface_context_t * interface,
                            void * inst,
							error_t (*send)(void*, uint8_t*, uint32_t),
							error_t (*recv)(void*, uint8_t*, uint32_t),
							error_t (*data_rdy)(void*))
{
    static int32_t count = 0;
    interface->inst = inst;
    interface->send = send;
    interface->recv = recv;
    interface->data_rdy = data_rdy;
    interface->id = count++;

    return ER_SUCCESS;
}



/* END */


