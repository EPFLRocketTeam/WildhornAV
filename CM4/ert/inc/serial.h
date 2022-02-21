/*  Title       : Serial
 *  Filename    : serial.h
 *  Author      : iacopo sprenger
 *  Date        : 31.01.2021
 *  Version     : 0.1
 *  Description : serial communication driver
 */

#ifndef SERIAL_H
#define SERIAL_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <usart.h>
#include <util.h>

/**********************
 *  CONSTANTS
 **********************/

#define SERIAL_MAX_INST	(16)
#define SERIAL_FIFO_LEN	(1024)


#define SERIAL_USE_GENERIC 1


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef enum SERIAL_RET {
	SERIAL_DONE,
	SERIAL_PROGRESS,
	SERIAL_ERROR
}SERIAL_RET_t;

typedef struct SERIAL_INST {
	uint32_t id;
	UART_HandleTypeDef * uart;
	void * inst;
	SERIAL_RET_t (*decode_fcn)(void *, uint8_t);
	UTIL_BUFFER_U8_t bfr;
	uint8_t buffer[SERIAL_FIFO_LEN];
	uint8_t dma_buffer;
}SERIAL_INST_t;

/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif


void serial_global_init();

void serial_init(SERIAL_INST_t * ser, UART_HandleTypeDef * uart, void * inst, SERIAL_RET_t (*decode_fcn)(void *, uint8_t));

void serial_send(SERIAL_INST_t * ser, uint8_t * data, uint16_t length);

void serial_garbage_clean(SERIAL_INST_t * ser);

void serial_thread(void * arg);

void serial_epos4_thread(void * arg);

void serial_debug_thread(void * arg);

void serial_epos4_init(SERIAL_INST_t * ser, UART_HandleTypeDef * uart, void * inst, SERIAL_RET_t (*decode_fcn)(void *, uint8_t));

void serial_debug_init(SERIAL_INST_t * ser, UART_HandleTypeDef * uart, void * inst, SERIAL_RET_t (*decode_fcn)(void *, uint8_t));


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SERIAL_H */

/* END */
