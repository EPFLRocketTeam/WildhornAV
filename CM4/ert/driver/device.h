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
#include <cmsis_os.h>
#include <stdint.h>
#include <util.h>


/**********************
 *  CONSTANTS
 **********************/

#define DEVICE_NAME_LEN 16

#define DEAMON_STACK_SIZE	1024


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct device_context {
    util_list_attribute;
    uint32_t id;
    void * inst;
    /* arguments: device_ptr, data, len) */
    error_t (*send)(void*, uint8_t*, uint32_t);
    /* arguments: device_ptr, data, len) */
    error_t (*recv)(void*, uint8_t*, uint32_t);
    /* arguments: device_ptr*/
    error_t (*data_rdy)(void*);

}device_interface_t;

typedef struct device_context {
	util_list_attribute;
	uint32_t id;
	StaticTask_t buffer;
	StackType_t stack[ DEAMON_STACK_SIZE ];
	TaskHandle_t handle;
	util_list_t * head;
}device_deamon_t;

typedef struct device_context {
    util_list_attribute;
    uint32_t id;
    device_interface_t * interface;
    /*arguments: context, addr, data, data_len*/
    error_t (*read_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t);
    /*arguments: context, addr, data, data_len*/
    error_t (*write_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t);
}device_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

error_t device_create(	device_t * dev,
						device_interface_t * interface,
						error_t (*read_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t),
						error_t (*write_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t));

error_t device_deamon_create(	device_deamon_t * deamon,
								const char * name,
								uint32_t prio);

error_t device_interface_create(   device_interface_t * interface,
                            		void * inst,
									device_deamon_t * deamon,
									error_t (*send)(void*, uint8_t*, uint32_t),
									error_t (*recv)(void*, uint8_t*, uint32_t),
									error_t (*data_rdy)(void*));

error_t device_write_i32(device_t * dev, uint32_t addr, int32_t data);
error_t device_write_u32(device_t * dev, uint32_t addr, uint32_t data);

error_t device_write_i16(device_t * dev, uint32_t addr, int16_t data);
error_t device_write_u16(device_t * dev, uint32_t addr, uint16_t data);

error_t device_write_i8(device_t * dev, uint32_t addr, int8_t data);
error_t device_write_u8(device_t * dev, uint32_t addr, uint8_t data);

error_t device_read_i32(device_t * dev, uint32_t addr, int32_t* data);
error_t device_read_u32(device_t * dev, uint32_t addr, uint32_t* data);

error_t device_read_i16(device_t * dev, uint32_t addr, int16_t* data);
error_t device_read_u16(device_t * dev, uint32_t addr, uint16_t* data);

error_t device_read_i8(device_t * dev, uint32_t addr, int8_t* data);
error_t device_read_u8(device_t * dev, uint32_t addr, uint8_t* data);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */


#endif /* DEVICE_H */

/* END */
