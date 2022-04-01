/*  Title       : Deamon
 *  Filename    : deamon.h
 *  Author      : iacopo sprenger
 *  Date        : 01.04.2021
 *  Version     : 0.1
 *  Description : template for code files
 */

#ifndef DEAMON_H
#define DEAMON_H



/**********************
 *  INCLUDES
 **********************/
#include <cmsis_os.h>
#include <stdint.h>
#include <util.h>

/**********************
 *  CONSTANTS
 **********************/

#define DEAMON_STACK_SIZE	1024


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct deamon_context {
	util_list_attribute;
	uint32_t id;
	StaticTask_t buffer;
	StackType_t stack[ DEAMON_STACK_SIZE ];
	TaskHandle_t handle;
	interface_context_t * head;

}deamon_context_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif


error_t deamon_create(deamon_context_t * deamon, interface_context_t head);


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* DEAMON_H */

/* END */
