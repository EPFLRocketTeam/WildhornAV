/*  Title       : Generic device driver
 *  Filename    : device.h
 *  Author      : iacopo sprenger
 *  Date        : 20.03.2022
 *  Version     : 0.1
 *  Description : 
 */

#ifndef DEVICE_H
#define DEVICE_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <util.h>

#include "interface.h"

/**********************
 *  CONSTANTS
 **********************/

#define DEVICE_NAME_LEN 16


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct device_context {
    util_list_attribute;
    uint32_t id;
    interface_context_t * interface;
    /*arguments: context, addr, data, data_len*/
    error_t (*read_reg)(interface_context_t*, uint32_t, uint8_t *, uint32_t);
    /*arguments: context, addr, data, data_len*/
    error_t (*write_reg)(interface_context_t*, uint32_t, uint8_t *, uint32_t);
}device_context_t;


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

error_t device_write_i32(device_context_t * dev, uint32_t addr, int32_t data);
error_t device_write_u32(device_context_t * dev, uint32_t addr, uint32_t data);

error_t device_write_i16(device_context_t * dev, uint32_t addr, int16_t data);
error_t device_write_u16(device_context_t * dev, uint32_t addr, uint16_t data);

error_t device_write_i8(device_context_t * dev, uint32_t addr, int8_t data);
error_t device_write_u8(device_context_t * dev, uint32_t addr, uint8_t data);

error_t device_read_i32(device_context_t * dev, uint32_t addr, int32_t data);
error_t device_read_u32(device_context_t * dev, uint32_t addr, uint32_t data);

error_t device_read_i16(device_context_t * dev, uint32_t addr, int16_t data);
error_t device_read_u16(device_context_t * dev, uint32_t addr, uint16_t data);

error_t device_read_i8(device_context_t * dev, uint32_t addr, int8_t data);
error_t device_read_u8(device_context_t * dev, uint32_t addr, uint8_t data);




#endif /* DEVICE_H */

/* END */
