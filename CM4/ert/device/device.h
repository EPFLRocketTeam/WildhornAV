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

#define DEVICE_MAX_INTERFACES_PER_DEAMON	16

#define DEAMON_STACK_SIZE	1024


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct device_interface {
    uint32_t id;
    void * context;
    /* arguments: if context, data, len) */
    util_error_t (*send)(void*, uint8_t*, uint32_t);
    /* arguments: if context, data, len) */
    util_error_t (*recv)(void*, uint8_t*, uint32_t*);
    /* arguments: if context, dem context */
    util_error_t (*handle_data)(void*, void*);

}device_interface_t;

typedef struct device_deamon {
	uint32_t id;
	StaticTask_t buffer;
	StackType_t stack[ DEAMON_STACK_SIZE ];
	TaskHandle_t handle;
	uint32_t interfaces_count;
	device_interface_t * interfaces[DEVICE_MAX_INTERFACES_PER_DEAMON];
	void * context;
	util_error_t (*data_rdy)(void*);
}device_deamon_t;

typedef struct device {
    uint32_t id;
    device_interface_t * interface;
    void * context;
    /*arguments: context, interface, addr, data, data_len*/
    util_error_t (*read_reg)(void*, device_interface_t*, uint32_t, uint8_t *, uint32_t);
    /*arguments: context, interface, addr, data, data_len*/
    util_error_t (*write_reg)(void*, device_interface_t*, uint32_t, uint8_t *, uint32_t);
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

util_error_t device_create(	device_t * dev,
						void * context,
						device_interface_t * interface,
						util_error_t (*read_reg)(void*, device_interface_t*, uint32_t, uint8_t *, uint32_t),
						util_error_t (*write_reg)(void*, device_interface_t*, uint32_t, uint8_t *, uint32_t));

util_error_t device_deamon_create(	device_deamon_t * deamon,
								const char * name,
								uint32_t prio,
								void * inst,
								util_error_t (*data_rdy)(void*));

util_error_t device_interface_create(   device_interface_t * interface,
                            		void * inst,
									device_deamon_t * deamon,
									util_error_t (*send)(void*, uint8_t*, uint32_t),
									util_error_t (*recv)(void*, uint8_t*, uint32_t*),
									util_error_t (*handle_data)(void*, void*));


util_error_t device_interface_send(device_interface_t * interface, uint8_t * data, uint32_t len);
util_error_t device_interface_recv(device_interface_t * interface, uint8_t * data, uint32_t * len);


util_error_t device_write_i32(device_t * dev, uint32_t addr, int32_t data);
util_error_t device_write_u32(device_t * dev, uint32_t addr, uint32_t data);

util_error_t device_write_i16(device_t * dev, uint32_t addr, int16_t data);
util_error_t device_write_u16(device_t * dev, uint32_t addr, uint16_t data);

util_error_t device_write_i8(device_t * dev, uint32_t addr, int8_t data);
util_error_t device_write_u8(device_t * dev, uint32_t addr, uint8_t data);

util_error_t device_read_i32(device_t * dev, uint32_t addr, int32_t* data);
util_error_t device_read_u32(device_t * dev, uint32_t addr, uint32_t* data);

util_error_t device_read_i16(device_t * dev, uint32_t addr, int16_t* data);
util_error_t device_read_u16(device_t * dev, uint32_t addr, uint16_t* data);

util_error_t device_read_i8(device_t * dev, uint32_t addr, int8_t* data);
util_error_t device_read_u8(device_t * dev, uint32_t addr, uint8_t* data);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */


#endif /* DEVICE_H */

/* END */
