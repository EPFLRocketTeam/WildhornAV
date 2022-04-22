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

#include <util.h>
#include "stm32mp1xx_it.h"

/**********************
 *	CONSTANTS
 **********************/

/**********************
 *	MACROS
 **********************/



/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/

dma_scheduler_dev_t dma2_scheduler;

dma_stream_dev_t dma2_streams[] = {
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream0,
				.dmamux_channel = DMAMUX1_Channel8,
				.number = 0,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream1,
				.dmamux_channel = DMAMUX1_Channel9,
				.number = 1,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream2,
				.dmamux_channel = DMAMUX1_Channel10,
				.number = 2,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream3,
				.dmamux_channel = DMAMUX1_Channel11,
				.number = 3,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream4,
				.dmamux_channel = DMAMUX1_Channel12,
				.number = 4,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream5,
				.dmamux_channel = DMAMUX1_Channel13,
				.number = 5,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream6,
				.dmamux_channel = DMAMUX1_Channel14,
				.number = 6,
				.state = DMA_STREAM_FREE
		},
		{
				.dma = DMA2,
				.dma_stream = DMA2_Stream7,
				.dmamux_channel = DMAMUX1_Channel15,
				.number = 7,
				.state = DMA_STREAM_FREE
		}

};


/**********************
 *	PROTOTYPES
 **********************/

void dma_handle_interrupt(dma_stream_dev_t * stream);


/**********************
 *	DECLARATIONS
 **********************/

/*
 * INTERRUPT HANDLERS
 */

void DMA2_Stream0_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[0]);
}

void DMA2_Stream1_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[1]);
}

void DMA2_Stream2_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[2]);
}

void DMA2_Stream3_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[3]);
}

void DMA2_Stream4_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[4]);
}

void DMA2_Stream5_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[5]);
}

void DMA2_Stream6_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[6]);
}

void DMA2_Stream7_IRQHandler(void) {
	dma_handle_interrupt(&dma2_streams[7]);
}


void dma_handle_interrupt(dma_stream_dev_t * stream) {
	//get status flags for the concerned dma stream
	uint32_t status_flags = 0;
	if(stream->number < 4) {
		status_flags = (stream->dma->LISR & (0b11101 << (stream->number*5))) >> (stream->number*5);
	} else {
		status_flags = (stream->dma->HISR & (0b11101 << ((stream->number-4)*5))) >> ((stream->number-4)*5);
	}

	if(status_flags & DMA_STATUS_TC) { //transfer complete
		stream->transfer_cplt(stream->user_context);
	} else if (status_flags & DMA_STATUS_TH) { //transfer half complete
		stream->transfer_half(stream->user_context);
	} else if (status_flags & DMA_STATUS_TE) { //transfer error
		stream->transfer_error(stream->user_context);
	} else { //unknown situation...
		//do nothing
	}
}


/*
 * External interfaces
 */

error_t dma2_init_scheduler(void) {
	dma_scheduler_init(&dma2_scheduler, dma2_streams, 8);
	return ER_SUCCESS;
}


dma_scheduler_dev_t * dma2_get_scheduler(void) {
	return &dma2_scheduler;
}

dma_stream_dev_t * dma2_get_streams(void) {
	return dma2_streams;
}


/*
 * GENERIC FUNCTIONS
 */

error_t dma_scheduler_init(dma_scheduler_dev_t * dma_scheduler, dma_stream_dev_t * dma_streams, uint16_t nb_dma_streams)
{
	if(nb_dma_streams > DMA_STREAMS_MAX_LEN) {
		return ER_OUT_OF_RANGE;
	}

	for(uint16_t i = 0; i < nb_dma_streams; i++) {
		dma_streams[i].state = DMA_STREAM_FREE;
		dma_scheduler->streams[i] = &(dma_streams[i]);
	}
	//enable_interrupts
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	NVIC_EnableIRQ(DMA2_Stream1_IRQn);
	NVIC_EnableIRQ(DMA2_Stream2_IRQn);
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	NVIC_EnableIRQ(DMA2_Stream4_IRQn);
	NVIC_EnableIRQ(DMA2_Stream5_IRQn);
	NVIC_EnableIRQ(DMA2_Stream6_IRQn);
	NVIC_EnableIRQ(DMA2_Stream7_IRQn);




	return ER_SUCCESS;
}

/*
 * Returns NULL if no stream is available!!
 */
dma_stream_dev_t * dma_scheduler_request_stream(dma_scheduler_dev_t * dma_scheduler) {
	ENTER_CRITICAL();

	//check if a stream is available
	if( !(dma_scheduler->free_stream_count > 0) ) {
		EXIT_CRITICAL();
		return NULL;
	}

	dma_stream_dev_t * stream;

	for(uint16_t i = 0; i < dma_scheduler->stream_count; i++) {
		if(dma_scheduler->streams[i]->state == DMA_STREAM_FREE) {
			stream = dma_scheduler->streams[i];
			break;
		}
	}

	stream->state = DMA_STREAM_BUSY;
	dma_scheduler->free_stream_count--;

	EXIT_CRITICAL();

	return stream;
}

error_t dma_scheduler_release_stream(dma_scheduler_dev_t * dma_scheduler, dma_stream_dev_t * dma_stream) {
	ENTER_CRITICAL();

	dma_stream->state = DMA_STREAM_FREE;
	dma_scheduler->free_stream_count++;


	EXIT_CRITICAL();

	return ER_SUCCESS;
}


error_t dma_start_stream(dma_stream_dev_t * stream, dma_stream_config_t config) {
	stream->dma_stream->CR = 0;
	while (stream->dma_stream->CR && DMA_SxCR_EN); //Wait for transfer to finish

	if(stream->number < 4) {
		WRITE_IN_REG(stream->dma->LISR, 0b11101 << (stream->number*5), 0); //clear interrupt flags
	} else {
		WRITE_IN_REG(stream->dma->HISR, 0b11101 << ((stream->number-4)*5) , 0); //clear interrupt flags
	}

	//set callbacks
	stream->transfer_cplt = config.transfer_cplt;
	stream->transfer_half = config.transfer_half;
	stream->transfer_error = config.transfer_error;
	stream->user_context = config.user_context;
	//set addresses
	stream->dma_stream->PAR = config.p_addr;
	stream->dma_stream->M0AR = config.m0_addr;
	stream->dma_stream->M1AR = config.m1_addr;

	//set transfer size
	stream->dma_stream->NDTR = config.transfer_size;

	//set trigger
	//no synchronization for now!

	if(config.dmamux_request_number > 127) {
		return ER_OUT_OF_RANGE;
	}

	stream->dmamux_channel->CCR = config.dmamux_request_number;


	//flow control
	WRITE_IN_REG(stream->dma_stream->CR, DMA_SxCR_PFCTRL_Msk, config.peripheral_flow_control<<DMA_SxCR_PFCTRL_Pos);

	//priority
	WRITE_IN_REG(stream->dma_stream->CR, DMA_SxCR_PL_Msk, config.priority<<DMA_SxCR_PL_Pos);

	//data direction
	WRITE_IN_REG(stream->dma_stream->CR, DMA_SxCR_DIR_Msk, config.direction<<DMA_SxCR_DIR_Pos);

	//enable transfer complete interrupt




	//start DMA stream
	stream->dma_stream->CR |= DMA_SxCR_EN;
}

/* END */
