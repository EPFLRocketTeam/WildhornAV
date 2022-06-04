/*  Title       : Object dictionary
 *  Filename    : od.h
 *  Author      : Oliver Facklam
 *  Date        : 28.05.2022
 *  Version     : 0.1
 *  Description : Object dictionary implementation
 */

#ifndef OD_H
#define OD_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/

#define OD_FRAME_MAX_SIZE   (64)    // 64 bytes for CAN frame size
#define OD_MAX_DATAID       (256U)   // 8-bit identifiers

/**********************
 *  MACROS
 **********************/

#define DECLARE_OD_ENTRY(NAME, TYPE) \
    void od_read_ ## NAME  (TYPE *dst); \
    void od_write_ ## NAME (TYPE *src);

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

void od_init();
void od_update_task(void *argument);

DECLARE_OD_ENTRY(TEMPERATURE, float)

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* OD_H */

/* END */
