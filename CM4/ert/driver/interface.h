/*  Title       : Generic interface wrapper
 *  Filename    : interface.h
 *  Author      : iacopo sprenger
 *  Date        : 20.03.2022
 *  Version     : 0.1
 *  Description : 
 */

#ifndef INTERFACE_H
#define INTERFACE_H



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

typedef struct interface_context {
    util_list_attribute;
    uint32_t id;
    void * inst;
    /* arguments: device_ptr, data, len) */
    error_t (*send)(void*, uint8_t*, uint32_t);
    /* arguments: device_ptr, data, len) */
    error_t (*recv)(void*, uint8_t*, uint32_t);
    /* arguments: device_ptr*/
    error_t (*data_rdy)(void*);

}interface_context_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

error_t interface_create(   interface_context_t * interface,
                            void * inst,
                            error_t (*send)(void*, uint8_t*, uint32_t),
							error_t (*recv)(void*, uint8_t*, uint32_t),
							error_t (*data_rdy)(void*));


#endif /* INTERFACE_H */

/* END */
