/*  Title       : DMA
 *  Filename    : dma.h
 *  Author      : iacopo sprenger
 *  Date        : 02.04.2022
 *  Version     : 0.1
 *  Description : dma hardware abstraction
 */

#ifndef DMA_H
#define DMA_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>
#include <util.h>

/**********************
 *  CONSTANTS
 **********************/


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/


/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

error_t dma_copy(void * dst, void * src, uint32_t len);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* DMA_H */

/* END */
