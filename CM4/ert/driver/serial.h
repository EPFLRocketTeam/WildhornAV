/*  Title       : Serial
 *  Filename    : serial.h
 *  Author      : iacopo sprenger
 *  Date        : 02.04.2022
 *  Version     : 0.1
 *  Description : serial interface for device driver
 */

#ifndef SERIAL_H
#define SERIAL_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <device/device.h>
#include <util.h>
#include <semphr.h>

/**********************
 *  CONSTANTS
 **********************/

#define SERIAL_BUFFER_LEN 256


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct serial_deamon_context {
	SemaphoreHandle_t rx_sem;
	StaticSemaphore_t rx_sem_buffer;

}serial_deamon_context_t;

typedef struct serial_interface_context {
	UART_HandleTypeDef * uart;
	util_buffer_u8_t rx_buffer;
	uint8_t rx_data[SERIAL_BUFFER_LEN];
	uint32_t rx_data_len;
	uint8_t rx_fragment;
	uint8_t tx_data[SERIAL_BUFFER_LEN];
	void * protocol;
}serial_interface_context_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

util_error_t serial_init(void);

util_error_t serial_feedback_init(void);

device_daemon_t * serial_get_deamon(void);

device_interface_t * serial_get_feedback_interface(void);

util_error_t serial_setup_reception(serial_interface_context_t * interface_context);

util_error_t serial_send(void * context, uint8_t* data, uint32_t len);

util_error_t serial_recv(void * context, uint8_t * data, uint32_t * len);





#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SERIAL_H */

/* END */
