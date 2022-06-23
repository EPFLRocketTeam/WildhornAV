/*  Title		: Maxon serial v2
 *  Filename	: msv2.c
 *	Author		: iacopo sprenger
 *	Date		: 20.01.2021
 *	Version		: 0.1
 *	Description	: Maxon serial v2 data transport layer
 */

/**********************
 *	INCLUDES
 **********************/

#include "msv2.h"

/**********************
 *	CONFIGURATION
 **********************/

//define serial write
//define serial read

/**********************
 *	CONSTANTS
 **********************/

#define DLE		(0x90)
#define STX		(0x02)



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

static uint16_t calc_field_CRC(uint16_t* p_data_array, uint16_t length);


/**********************
 *	DECLARATIONS
 **********************/

/**
 * @brief	Compute the CRC for a data packet.
 * @details	Function taken from Maxon Serial V2 specification manual.
 *
 * @param	p_data_array	Pointer to the data array of the packet.
 * @param	length			Length of the packet
 *
 * @note	The p_data_array data must contain two empty bytes [0x00, 0x00] at the end,
 * 			where the CRC goes.
 */
uint16_t calc_field_CRC(uint16_t *p_data_array, uint16_t length) {
	uint16_t shifter, c;
	uint16_t carry;
	uint16_t crc = 0;
	while (length--) {
		shifter = 0x8000;
		c = *p_data_array++;
		do {
			carry = crc & 0x8000;
			crc <<= 1;
			if (c & shifter) crc++;
			if (carry) crc ^= 0x1021;
			shifter >>= 1;

		} while (shifter);

	}
	return crc;
}

/**
 * @brief Initialize a msv2 packet creator instance.
 *
 * @param 	msv2	Pointer to the msv2 instance to be initialized.
 */
void msv2_init(MSV2_INST_t * msv2) {
	static uint32_t id_counter = 0;
	msv2->id = id_counter++;
}

/**
 * @brief Generate an msv2 packet
 * @details
 *
 * @param 	msv2		Pointer to the msv2 packet creator instance.
 * @param 	opcode		Opcode to be placed in the packet header.
 * @param 	data_len	Length of the packet data payload.
 * @param 	data		Data to be placed in the packet payload.
 */
uint16_t msv2_create_frame(MSV2_INST_t * msv2, uint8_t opcode, uint8_t data_len, uint8_t * data) {
	uint16_t array_len = data_len+2; //we add 1 for the opcode and len fields and 1 for the crc
	msv2->tx.data_len = data_len;
	msv2->tx.opcode = opcode;
	msv2->tx.data[0] = DLE;
	msv2->tx.data[1] = STX;
	msv2->tx.data[2] = opcode;
	msv2->tx.data[3] = data_len;
	msv2->tx.crc_data[0] = (data_len<<8) | opcode;  //header bytes inverted
	uint16_t counter=4;
	for(uint16_t i = 0; i < data_len; i++) {
		msv2->tx.data[counter++] = data[2*i]; //bytes in data need to be inverted before
		if(msv2->tx.data[counter-1] == DLE) {
			msv2->tx.data[counter++] = DLE;
		}
		msv2->tx.data[counter++] = data[2*i+1];
		if(msv2->tx.data[counter-1] == DLE) {
			msv2->tx.data[counter++] = DLE;
		}
		msv2->tx.crc_data[i+1] = (data[2*i+1]<<8) |  data[2*i];
	}
	msv2->tx.crc_data[array_len-1] = 0x0000;
	uint16_t crc = calc_field_CRC(msv2->tx.crc_data, array_len);
	msv2->tx.data[counter++] = crc&0xff; //crc bytes are inverted (LSB first) !!
	if(msv2->tx.data[counter-1] == DLE) {
		msv2->tx.data[counter++] = DLE;
	}
	msv2->tx.data[counter++] = crc>>8;
	if(msv2->tx.data[counter-1] == DLE) {
		msv2->tx.data[counter++] = DLE;
	}
	return counter;
}

/**
 * @brief Decode an msv2 fragment (one byte at a time)
 * @details
 *
 * @param	msv2	Pointer to the msv2 packet creator instance.
 * @param	d		Fragment to be decoded.
 *
 * @note	This function is to be called upon reception of a byte.
 */
MSV2_ERROR_t msv2_decode_fragment(MSV2_INST_t * msv2, uint8_t d) {
    //if a DLE in data is followed by STX, we start again
    if (msv2->rx.escape == 1 && d == STX) {
    	msv2->rx.state = WAITING_OPCODE;
    	msv2->rx.escape = 0;
        return MSV2_PROGRESS;
    }

    if (msv2->rx.state == WAITING_DLE && d == DLE) {
    	msv2->rx.state = WAITING_STX;
        return MSV2_PROGRESS;
    }
    //escape in case a DLE is in the data
    if (d == DLE && msv2->rx.escape == 0) {
    	msv2->rx.escape = 1;
        return MSV2_PROGRESS;
    }
    //if it is doubled, it counts as data
    if (d == DLE && msv2->rx.escape == 1) {
    	msv2->rx.escape = 0;

    }

    if (msv2->rx.state == WAITING_STX && d == STX) {
    	msv2->rx.state = WAITING_OPCODE;
        return MSV2_PROGRESS;
    }

    if (msv2->rx.state == WAITING_OPCODE) {
    	msv2->rx.opcode = d;
    	msv2->rx.state = WAITING_LEN;
        return MSV2_PROGRESS;
    }

    if (msv2->rx.state == WAITING_LEN) {
    	msv2->rx.data_len = d; //legth in words
    	msv2->rx.length = 2*d; //length in bytes
    	msv2->rx.crc_data[0] = (msv2->rx.data_len<<8) | msv2->rx.opcode;
    	msv2->rx.counter = 0;
    	msv2->rx.state = WAITING_DATA;
        return MSV2_PROGRESS;
    }

    if (msv2->rx.state == WAITING_DATA) {
    	msv2->rx.data[msv2->rx.counter] = d;
    	if(msv2->rx.counter & 0x01) { //LSB == '1'
    		msv2->rx.crc_data[msv2->rx.counter/2 + 1] = (msv2->rx.data[msv2->rx.counter - 1]) |  d<<8;
    	}
    	msv2->rx.counter += 1;
        //the length  is in WORDS, but we read BYTES
        if (msv2->rx.counter==msv2->rx.length) {
        	msv2->rx.state = WAITING_CRC1;
        }
        return MSV2_PROGRESS;
    }

    if (msv2->rx.state == WAITING_CRC1) {
    	msv2->rx.crc = d;
    	msv2->rx.state = WAITING_CRC2;
        return MSV2_PROGRESS;

    }

    if (msv2->rx.state == WAITING_CRC2) {
    	msv2->rx.crc |= d<<8;
    	msv2->rx.state = WAITING_DLE;
    	msv2->rx.crc_data[msv2->rx.data_len+1] = 0;
    	uint16_t crc = calc_field_CRC(msv2->rx.crc_data, msv2->rx.data_len+2);
    	if(msv2->rx.crc == crc) {
    		return MSV2_SUCCESS;
    	} else {
    		return MSV2_WRONG_CRC;
    	}
    }
    msv2->rx.state=WAITING_DLE;
    return MSV2_PROGRESS;
}

/**
 * @brief	Getter for the pointer to the rx data array contained in the msv2 packet creator
 *
 * @param	msv2	Pointer to the msv2 packet creator instance.
 */
uint8_t * msv2_rx_data(MSV2_INST_t * msv2) {
	return msv2->rx.data;
}

/**
 * @brief	Getter for the pointer to the tx data array contained in the msv2 packet creator
 *
 * @param	msv2	Pointer to the msv2 packet creator instance.
 */
uint8_t * msv2_tx_data(MSV2_INST_t * msv2) {
	return msv2->tx.data;
}


/* END */


