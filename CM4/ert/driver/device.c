/*  Title		: Generic device driver
 *  Filename	: device.c
 *	Author		: iacopo sprenger
 *	Date		: 20.03.2021
 *	Version		: 0.1
 *	Description	: 
 */

/**********************
 *	INCLUDES
 **********************/

#include <util.h>

#include "device.h"


/**********************
 *	CONSTANTS
 **********************/
#define DEVICE_NAME_LEN 16

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


/**********************
 *	DECLARATIONS
 **********************/


error_t device_write_i32(device_context_t * dev, uint32_t addr, int32_t data)
{
    uint8_t tmp[LEN_32];
    util_encode_i32(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_32);
    return ER_SUCCESS;
}

error_t device_write_u32(device_context_t * dev, uint32_t addr, uint32_t data)
{
    uint8_t tmp[LEN_32];
    util_encode_u32(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_32);
    return ER_SUCCESS;
}

error_t device_write_i16(device_context_t * dev, uint32_t addr, int16_t data)
{
    uint8_t tmp[LEN_16];
    util_encode_i16(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_16);
    return ER_SUCCESS;
}

error_t device_write_u16(device_context_t * dev, uint32_t addr, uint16_t data)
{
    uint8_t tmp[LEN_16];
    util_encode_u16(tmp, data);
    dev->write_reg(dev->interface, addr, tmp, LEN_16);
    return ER_SUCCESS;
}

error_t device_write_i8(device_context_t * dev, uint32_t addr, int8_t data);
error_t device_write_u8(device_context_t * dev, uint32_t addr, uint8_t data);

error_t device_read_i32(device_context_t * dev, uint32_t addr, int32_t data);
error_t device_read_u32(device_context_t * dev, uint32_t addr, uint32_t data);

error_t device_read_i16(device_context_t * dev, uint32_t addr, int16_t data);
error_t device_read_u16(device_context_t * dev, uint32_t addr, uint16_t data);

error_t device_read_i8(device_context_t * dev, uint32_t addr, int8_t data);
error_t device_read_u8(device_context_t * dev, uint32_t addr, uint8_t data);



/* END */


