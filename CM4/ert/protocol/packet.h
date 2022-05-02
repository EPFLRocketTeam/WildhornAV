/*
 * Packets definitions
 * Iacopo Sprenger
 *
 *
 *
 * packets are sent using the MSV2 protocol
 *
 * The minimum data size of a packet is   2 bytes
 * The maximum data size of a packet is 512 bytes
 *
 * Careful about the min and max size bounds...
 *
 *
 */


#ifndef PACKET_H
#define PACKET_H


#include <stdint.h>


typedef struct packet_def {
	uint8_t opcode; //msv2 opcode
	uint8_t len; 	//length in words
}packet_def_t;

const packet_def_t ping = {0x00, 0x02};






#endif
