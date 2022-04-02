/*  Title		: DMA
 *  Filename	: dma.c
 *	Author		: iacopo sprenger
 *	Date		: 02.04.2022
 *	Version		: 0.1
 *	Description	: dma hardware abstraction
 */

/**********************
 *	INCLUDES
 **********************/

#include "dma.h"
#include <dma.h>

/**********************
 *	CONSTANTS
 **********************/

#define DMA_COPY_DEV	hdma_memtomem_dma2_stream6

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

error_t dma_copy(void * dst, void * src, uint32_t len)
{
	HAL_DMA_Start(&DMA_COPY_DEV, (uint32_t) src, (uint32_t) dst, len);
	return ER_SUCCESS;
}

/* END */
