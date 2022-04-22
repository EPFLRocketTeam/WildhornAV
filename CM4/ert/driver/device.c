/*  Title		: Generic device driver
 *  Filename	: device.c
 *	Author		: iacopo sprenger
 *	Date		: 20.03.2022
 *	Version		: 0.1
 *	Description	: 
 */

/**********************
 *	INCLUDES
 **********************/

#include <cmsis_os.h>
#include <util.h>

#include "device.h"


/**********************
 *	CONSTANTS
 **********************/

#define LEN_32 4
#define LEN_16 2
#define LEN_8  1 

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

void device_deamon_thread(void * arg);


/**********************
 *	DECLARATIONS
 **********************/


error_t device_create(	device_t * dev,
						device_interface_t * interface,
						error_t (*read_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t),
						error_t (*write_reg)(device_interface_t*, uint32_t, uint8_t *, uint32_t))
{
	static int32_t count = 0;
	dev->interface = interface;
	dev->read_reg = read_reg;
	dev->write_reg = write_reg;
	dev->id = count++;

	return ER_SUCCESS;
}


error_t device_interface_create(   	device_interface_t * interface,
                            		void * inst,
									device_deamon_t * deamon,
									error_t (*send)(void*, uint8_t*, uint32_t),
									error_t (*recv)(void*, uint8_t*, uint32_t*),
									error_t (*handle_data)(void*, void*))
{
    static int32_t count = 0;
    interface->inst = inst;
    interface->send = send;
    interface->recv = recv;
    interface->handle_data = handle_data;
    interface->id = count++;
    deamon->interfaces[deamon->interfaces_count] = interface;
    deamon->interfaces_count++;
    return ER_SUCCESS;
}

error_t device_deamon_create(	device_deamon_t * deamon,
								const char * name,
								uint32_t prio,
								void * inst,
								error_t (*data_rdy)(void*))
{
	static uint32_t counter = 0;
	deamon->id = counter++;
	deamon->inst = inst;
	deamon->data_rdy = data_rdy;
	deamon->interfaces_count = 0;
	deamon->handle = xTaskCreateStatic(device_deamon_thread, name, DEAMON_STACK_SIZE, deamon, prio, deamon->stack, &deamon->buffer);
	return ER_SUCCESS;
}

void device_deamon_thread(void * arg)
{
	device_deamon_t * deamon = (device_deamon_t * ) arg;

	for(;;) {
		if(deamon->data_rdy(deamon->inst) == ER_SUCCESS) {
			//iterate over all interfaces in deamon
			for(uint16_t i = 0; i < deamon->interfaces_count; i++) {
				device_interface_t * interface = deamon->interfaces[i];
				interface->handle_data(interface->inst, deamon->inst);
			}
		}
	}
}



//interface send/recv functions

error_t device_interface_send(device_interface_t * interface, uint8_t * data, uint32_t len)
{

	return interface->send(interface->inst, data, len);
}

error_t device_interface_recv(device_interface_t * interface, uint8_t * data, uint32_t * len)
{
	return interface->recv(interface->inst, data, len);
}

// device write functions


error_t device_write_i32(device_t * dev, uint32_t addr, int32_t data)
{
    uint8_t tmp[LEN_32];
    util_encode_i32(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_32);
    return ER_SUCCESS;
}

error_t device_write_u32(device_t * dev, uint32_t addr, uint32_t data)
{
    uint8_t tmp[LEN_32];
    util_encode_u32(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_32);
    return ER_SUCCESS;
}

error_t device_write_i16(device_t * dev, uint32_t addr, int16_t data)
{
    uint8_t tmp[LEN_16];
    util_encode_i16(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_16);
    return ER_SUCCESS;
}

error_t device_write_u16(device_t * dev, uint32_t addr, uint16_t data)
{
    uint8_t tmp[LEN_16];
    util_encode_u16(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_16);
    return ER_SUCCESS;
}

error_t device_write_i8(device_t * dev, uint32_t addr, int8_t data)
{
    uint8_t tmp[LEN_8];
    util_encode_i8(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_8);
    return ER_SUCCESS;
}
error_t device_write_u8(device_t * dev, uint32_t addr, uint8_t data)
{
    uint8_t tmp[LEN_8];
    util_encode_u8(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_8);
    return ER_SUCCESS;
}

error_t device_read_i32(device_t * dev, uint32_t addr, int32_t* data)
{
    uint8_t tmp[LEN_32];
    dev->read_reg(dev->interface, addr, tmp, LEN_32);
    *data = util_decode_i32(tmp);
    return ER_SUCCESS;
}
error_t device_read_u32(device_t * dev, uint32_t addr, uint32_t* data)
{
    uint8_t tmp[LEN_32];
    dev->read_reg(dev->interface, addr, tmp, LEN_32);
    *data = util_decode_u32(tmp);
    return ER_SUCCESS;
}

error_t device_read_i16(device_t * dev, uint32_t addr, int16_t* data)
{
    uint8_t tmp[LEN_16];
    dev->read_reg(dev->interface, addr, tmp, LEN_16);
    *data = util_decode_i16(tmp);
    return ER_SUCCESS;
}

error_t device_read_u16(device_t * dev, uint32_t addr, uint16_t* data)
{
    uint8_t tmp[LEN_16];
    dev->read_reg(dev->interface, addr, tmp, LEN_16);
    *data = util_decode_u16(tmp);
    return ER_SUCCESS;
}

error_t device_read_i8(device_t * dev, uint32_t addr, int8_t* data)
{
    uint8_t tmp[LEN_8];
    dev->read_reg(dev->interface, addr, tmp, LEN_8);
    *data = util_decode_i8(tmp);
    return ER_SUCCESS;
}

error_t device_read_u8(device_t * dev, uint32_t addr, uint8_t* data)
{
    uint8_t tmp[LEN_8];
    dev->read_reg(dev->interface, addr, tmp, LEN_8);
    *data = util_decode_u8(tmp);
    return ER_SUCCESS;
}


/* END */
