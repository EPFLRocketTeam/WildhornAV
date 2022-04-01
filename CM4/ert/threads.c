/*  Title		: Threads
 *  Filename	: threads.c
 *	Author		: iacopo sprenger
 *	Date		: 20.01.2022
 *	Version		: 0.1
 *	Description	: template for code files
 */

/**********************
 *	INCLUDES
 **********************/


#include <cmsis_os.h>
#include <threads.h>


#include <control.h>


/**********************
 *	CONSTANTS
 **********************/

#define DEFAULT_SZ	(1024)

#define CONTROL_SZ	DEFAULT_SZ
#define CONTROL_PRIO	(6)


/**********************
 *	MACROS
 **********************/

#define CREATE_THREAD(handle, name, func, cont, sz, prio) \
	static StaticTask_t name##_buffer; \
	static StackType_t name##_stack[ sz ]; \
	handle = xTaskCreateStatic( \
			func, \
	        #name, \
			sz, \
			( void * ) cont, \
			prio, \
			name##_stack, \
			&name##_buffer)

/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/

static TaskHandle_t control_handle = NULL;

/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/


void threads_init(void) {

	CREATE_THREAD(control_handle, control, control_thread, 0, CONTROL_SZ, CONTROL_PRIO);

}


/* END */
