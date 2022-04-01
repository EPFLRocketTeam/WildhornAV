/*  Title		: Deamon
 *  Filename	: deamon.c
 *	Author		: iacopo sprenger
 *	Date		: 01.04.2021
 *	Version		: 0.1
 *	Description	: deamon for serial driver
 */

/**********************
 *	INCLUDES
 **********************/

#include "deamon.h"
#include <threads.h>

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

error_t deamon_create(deamon_context_t * deamon, const char * name, uint32_t prio, interface_context_t head) {
	static uint32_t counter = 0;
	deamon->id = counter++;
	deamon->head = head;
	deamon->handle = xTaskCreateStatic(deamon_thread, name, DEAMON_STACK_SIZE, deamon, prio, deamon->stack, deamon->buffer);
	return ER_SUCCESS;
}


void deamon_thread(void * arg) {

}

/* END */
