/*  Title       : error codes
 *  Filename    : error.h
 *  Author      : iacopo sprenger
 *  Date        : 21.03.2022
 *  Version     : 0.1
 *  Description : 
 */

#ifndef UTIL_H
#define UTIL_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/


/**********************
 *  MACROS
 **********************/

#define util_list_attribute \
    void* next 

#define util_list_foreach(head, node) \
    for(util_list_t node = head->next; node->next != NULL; node = node->next)


/**********************
 *  TYPEDEFS
 **********************/

typedef enum error {
    ER_SUCCESS = 0,
    ER_DATA_NOT_RDY = 0<<1,
    ER_FAILURE = 1<<1,
    ER_OUT_OF_RANGE = 1<<2
}error_t;

typedef struct util_list {
    void* next;
}util_list_t;


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif


/** head must be of util_list_t type with the next field as the head
 *  any node with the util_list_attribute can be cast to util_list_t
 *  
 * 
 */
static inline void util_list_append(util_list_t* head, util_list_t* node) 
{
    util_list_t** p = &head->next;
    while((*p) != 0) {
        p = &(*p)->next;
    }
    *p = node;
}

/** head must be of util_list_t type with the next field as the head
 *  any node with the util_list_attribute can be cast to util_list_t
 * 
 * 
 */
static inline void util_list_remove(util_list_t* head, util_list_t* node) 
{
    util_list_t** p = &head->next;
    while((*p) != node) {
        p = &(*p)->next;
    }
    *p = node->next; //this remove the node from the list
}

/* data encoding and decoding */

static inline void util_encode_u8(uint8_t * data, uint8_t value) {
    data[0] = value;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0x00;
}

static inline void util_encode_u16(uint8_t * data, uint16_t value) {
    data[0] = value;
    data[1] = value>>8;
    data[2] = 0x00;
    data[3] = 0x00;
}

static inline void util_encode_u32(uint8_t * data, uint32_t value) {
    data[0] = value;
    data[1] = value>>8;
    data[2] = value>>16;
    data[3] = value>>24;
}

static inline void util_encode_i8(uint8_t * data, int8_t value) {
    data[0] = value;
    data[1] = 0x00;
    data[2] = 0x00;
    data[3] = 0x00;
}

static inline void util_encode_i16(uint8_t * data, int16_t value) {
    data[0] = value;
    data[1] = value>>8;
    data[2] = 0x00;
    data[3] = 0x00;
}

static inline void util_encode_i32(uint8_t * data, int32_t value) {
    data[0] = value;
    data[1] = value>>8;
    data[2] = value>>16;
    data[3] = value>>24;
}

static inline uint8_t util_decode_u8(uint8_t * data) {
    return data[0];
}

static inline uint16_t util_decode_u16(uint8_t * data) {
    return (uint16_t) data[0] | data[1] << 8;
}

static inline uint32_t util_decode_u32(uint8_t * data) {
    return (uint32_t) data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24;
}

static inline int8_t util_decode_i8(uint8_t * data) {
    return data[0];
}

static inline int16_t util_decode_i16(uint8_t * data) {
    return (int16_t) data[0] | data[1] << 8;
}

static inline int32_t util_decode_i32(uint8_t * data) {
    return (int32_t) data[0] | data[1] << 8 | data[2] << 16 | data[3] << 24;
}


#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* UTIL_H */

/* END */
