/*  Title       : Maxon Serial v2
 *  Filename    : msv2.h
 *  Author      : iacopo sprenger
 *  Date        : 20.01.2021
 *  Version     : 0.1
 *  Description : Maxon serial v2 data transport layer
 */

#ifndef MSV2_H
#define MSV2_H

/**********************
 *  INCLUDES
 **********************/

#include <util.h>
#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/

#define MSV2_MAX_FRAME_LEN	(1024)

#define MSV2_MAX_DATA_LEN	(512)


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

/**
 * @brief Msv2 packet creator return codes.
 */
typedef enum MSV2_ERROR {
	/** Packet sucessfully decoded/encoded */
	MSV2_SUCCESS = 0,
	/** Packed decoding in progress */
	MSV2_PROGRESS,
	/** Packet decoding error due to wrong crc */
	MSV2_WRONG_CRC,
	/** generic error */
	MSV2_ERROR
}MSV2_ERROR_t;

/**
 * @brief Msv2 packet decoded state.
 */
typedef enum MSV2_DECODE_STATE{
	/** Waiting for data Link Escape */
	WAITING_DLE,
	/** Waiting for Start of Text */
	WAITING_STX,
	/** Waiting for Opcode */
	WAITING_OPCODE,
	/** Waiting for Packet Length */
	WAITING_LEN,
	/** Waiting for Data */
	WAITING_DATA,
	/** Waiting for CRC Byte 1 */
	WAITING_CRC1,
	/** Waiting for CRC Byte 2 */
	WAITING_CRC2
}MSV2_DECODE_STATE_t;

typedef struct MSV2_RX_DATA{
	uint8_t opcode;
	uint8_t data_len;
	uint16_t crc;
	MSV2_DECODE_STATE_t state;
	uint8_t escape;
	uint16_t length;
	uint16_t counter;
	uint8_t data[MSV2_MAX_FRAME_LEN];
	uint16_t crc_data[MSV2_MAX_FRAME_LEN/sizeof(uint16_t)];
}MSV2_RX_DATA_t;

typedef struct MSV2_TX_DATA{
	uint8_t opcode;
	uint8_t data_len;
	uint16_t crc;
	uint8_t data[MSV2_MAX_FRAME_LEN];
	uint16_t crc_data[MSV2_MAX_FRAME_LEN/sizeof(uint16_t)];
}MSV2_TX_DATA_t;

typedef struct MSV2_INST{
	uint32_t id;
	MSV2_RX_DATA_t rx;
	MSV2_TX_DATA_t tx;
}MSV2_INST_t;




/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

MSV2_ERROR_t msv2_decode_fragment(MSV2_INST_t * msv2, uint8_t d);

void msv2_init(MSV2_INST_t * msv2);

uint16_t msv2_create_frame(MSV2_INST_t * msv2, uint8_t opcode, uint8_t data_len, uint8_t * data);

uint8_t * msv2_rx_data(MSV2_INST_t * msv2);

uint8_t * msv2_tx_data(MSV2_INST_t * msv2);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* MSV2_H */

/* END */
