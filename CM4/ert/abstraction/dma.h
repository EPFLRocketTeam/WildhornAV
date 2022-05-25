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
#include <main.h>
#include <stdint.h>
#include <util.h>

/**********************
 *  CONSTANTS
 **********************/

#define DMA_STREAMS_MAX_LEN 8


/*
 * DMAMUX channel allocation
 * Source ChibiOS source
 */

#define STM32_DMAMUX1_REQ_GEN0      1
#define STM32_DMAMUX1_REQ_GEN1      2
#define STM32_DMAMUX1_REQ_GEN2      3
#define STM32_DMAMUX1_REQ_GEN3      4
#define STM32_DMAMUX1_REQ_GEN4      5
#define STM32_DMAMUX1_REQ_GEN5      6
#define STM32_DMAMUX1_REQ_GEN6      7
#define STM32_DMAMUX1_REQ_GEN7      8
#define STM32_DMAMUX1_ADC1          9
#define STM32_DMAMUX1_ADC2          10
#define STM32_DMAMUX1_TIM1_CH1      11
#define STM32_DMAMUX1_TIM1_CH2      12
#define STM32_DMAMUX1_TIM1_CH3      13
#define STM32_DMAMUX1_TIM1_CH4      14
#define STM32_DMAMUX1_TIM1_UP       15
#define STM32_DMAMUX1_TIM1_TRIG     16
#define STM32_DMAMUX1_TIM1_COM      17
#define STM32_DMAMUX1_TIM2_CH1      18
#define STM32_DMAMUX1_TIM2_CH2      19
#define STM32_DMAMUX1_TIM2_CH3      20
#define STM32_DMAMUX1_TIM2_CH4      21
#define STM32_DMAMUX1_TIM2_UP       22
#define STM32_DMAMUX1_TIM3_CH1      23
#define STM32_DMAMUX1_TIM3_CH2      24
#define STM32_DMAMUX1_TIM3_CH3      25
#define STM32_DMAMUX1_TIM3_CH4      26
#define STM32_DMAMUX1_TIM3_UP       27
#define STM32_DMAMUX1_TIM3_TRIG     28
#define STM32_DMAMUX1_TIM4_CH1      29
#define STM32_DMAMUX1_TIM4_CH2      30
#define STM32_DMAMUX1_TIM4_CH3      31
#define STM32_DMAMUX1_TIM4_UP       32
#define STM32_DMAMUX1_I2C1_RX       33
#define STM32_DMAMUX1_I2C1_TX       34
#define STM32_DMAMUX1_I2C2_RX       35
#define STM32_DMAMUX1_I2C2_TX       36
#define STM32_DMAMUX1_SPI1_RX       37
#define STM32_DMAMUX1_SPI1_TX       38
#define STM32_DMAMUX1_SPI2_RX       39
#define STM32_DMAMUX1_SPI2_TX       40
#define STM32_DMAMUX1_RSVD41        41
#define STM32_DMAMUX1_RSVD42        42
#define STM32_DMAMUX1_USART2_RX     43
#define STM32_DMAMUX1_USART2_TX     44
#define STM32_DMAMUX1_USART3_RX     45
#define STM32_DMAMUX1_USART3_TX     46
#define STM32_DMAMUX1_TIM8_CH1      47
#define STM32_DMAMUX1_TIM8_CH2      48
#define STM32_DMAMUX1_TIM8_CH3      49
#define STM32_DMAMUX1_TIM8_CH4      50
#define STM32_DMAMUX1_TIM8_UP       51
#define STM32_DMAMUX1_TIM8_TRIG     52
#define STM32_DMAMUX1_TIM8_COM      53
#define STM32_DMAMUX1_RSVD54        54
#define STM32_DMAMUX1_TIM5_CH1      55
#define STM32_DMAMUX1_TIM5_CH2      56
#define STM32_DMAMUX1_TIM5_CH3      57
#define STM32_DMAMUX1_TIM5_CH4      58
#define STM32_DMAMUX1_TIM5_UP       59
#define STM32_DMAMUX1_TIM5_TRIG     60
#define STM32_DMAMUX1_SPI3_RX       61
#define STM32_DMAMUX1_SPI3_TX       62
#define STM32_DMAMUX1_UART4_RX      63
#define STM32_DMAMUX1_UART4_TX      64
#define STM32_DMAMUX1_UART5_RX      65
#define STM32_DMAMUX1_UART5_TX      66
#define STM32_DMAMUX1_DAC1_CH1      67
#define STM32_DMAMUX1_DAC1_CH2      68
#define STM32_DMAMUX1_TIM6_UP       69
#define STM32_DMAMUX1_TIM7_UP       70
#define STM32_DMAMUX1_USART6_RX     71
#define STM32_DMAMUX1_USART6_TX     72
#define STM32_DMAMUX1_I2C3_RX       73
#define STM32_DMAMUX1_I2C3_TX       74
#define STM32_DMAMUX1_DCMI          75
#define STM32_DMAMUX1_CRYP2_IN      76
#define STM32_DMAMUX1_CRYP2_OUT     77
#define STM32_DMAMUX1_HASH2_IN      78
#define STM32_DMAMUX1_UART7_RX      79
#define STM32_DMAMUX1_UART7_TX      80
#define STM32_DMAMUX1_UART8_RX      81
#define STM32_DMAMUX1_UART8_TX      82
#define STM32_DMAMUX1_SPI4_RX       83
#define STM32_DMAMUX1_SPI4_TX       84
#define STM32_DMAMUX1_SPI5_RX       85
#define STM32_DMAMUX1_SPI5_TX       86
#define STM32_DMAMUX1_SAI1_A        87
#define STM32_DMAMUX1_SAI1_B        88
#define STM32_DMAMUX1_SAI2_A        89
#define STM32_DMAMUX1_SAI2_B        90
#define STM32_DMAMUX1_DFSDM1_FLT4   91
#define STM32_DMAMUX1_DFSDM1_FLT5   92
#define STM32_DMAMUX1_SPDIFRX_DT    93
#define STM32_DMAMUX1_SPDIFRX_CS    94
#define STM32_DMAMUX1_RSVD95        95
#define STM32_DMAMUX1_RSVD96        96
#define STM32_DMAMUX1_RSVD97        97
#define STM32_DMAMUX1_RSVD98        98
#define STM32_DMAMUX1_SAI4_A        99
#define STM32_DMAMUX1_SAI4_B        100
#define STM32_DMAMUX1_DFSDM1_FLT0   101
#define STM32_DMAMUX1_DFSDM1_FLT1   102
#define STM32_DMAMUX1_DFSDM1_FLT2   103
#define STM32_DMAMUX1_DFSDM1_FLT3   104
#define STM32_DMAMUX1_TIM15_CH1     105
#define STM32_DMAMUX1_TIM15_UP      106
#define STM32_DMAMUX1_TIM15_TRIG    107
#define STM32_DMAMUX1_TIM15_COM     108
#define STM32_DMAMUX1_TIM16_CH1     109
#define STM32_DMAMUX1_TIM16_UP      110
#define STM32_DMAMUX1_TIM17_CH1     111
#define STM32_DMAMUX1_TIM17_UP      112
#define STM32_DMAMUX1_SAI3_A        113
#define STM32_DMAMUX1_SAI3_B        114
#define STM32_DMAMUX1_I2C5_RX       115
#define STM32_DMAMUX1_I2C5_TX       116
#define STM32_DMAMUX1_RSVD117       117
#define STM32_DMAMUX1_RSVD118       118
#define STM32_DMAMUX1_RSVD119       119
#define STM32_DMAMUX1_RSVD120       120
#define STM32_DMAMUX1_RSVD121       121
#define STM32_DMAMUX1_RSVD122       122
#define STM32_DMAMUX1_RSVD123       123
#define STM32_DMAMUX1_RSVD124       124
#define STM32_DMAMUX1_RSVD125       125
#define STM32_DMAMUX1_RSVD126       126
#define STM32_DMAMUX1_RSVD127       127


#define DMA_STATUS_TC 				(0b1<<5)
#define DMA_STATUS_TH 				(0b1<<4)
#define DMA_STATUS_TE 				(0b1<<3)


/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef enum dma_stream_state {
	DMA_STREAM_BUSY,
	DMA_STREAM_FREE
}dma_stream_state_t;

typedef enum dma_stream_dir {
	DMA_STREAM_P2M = 0b00,
	DMA_STREAM_M2P = 0b01,
	DMA_STREAM_M2M = 0b10
}dma_stream_dir_t;






//struct for a peripheral torequest the use of a DMA stream
typedef struct dma_request {
	uint32_t src;
	uint32_t dst;
	uint32_t tranfser_len;
	uint8_t dst_inc;
	uint8_t src_inc;

}dma_request_t;

typedef struct dma_stream_config {
	uint32_t stream_number;
	uint32_t p_addr;
	uint32_t m0_addr;
	uint32_t m1_addr;
	uint32_t transfer_size;
	uint16_t dmamux_request_number;
	uint8_t priority;
	dma_stream_dir_t direction;
	uint8_t peripheral_flow_control;
	void * user_context;
	void (*transfer_cplt)(void*);
	void (*transfer_half)(void*);
	void (*transfer_error)(void*);

}dma_stream_config_t;

typedef struct dma_stream_dev {
	DMA_TypeDef * dma;
	DMA_Stream_TypeDef * dma_stream;
	DMAMUX_Channel_TypeDef * dmamux_channel;
	DMAMUX_ChannelStatus_TypeDef * dmamux_channel_status;
	dma_stream_state_t state;
	uint16_t number;
	void * user_context;
	void (*transfer_cplt)(void*);
	void (*transfer_half)(void*);
	void (*transfer_error)(void*);

}dma_stream_dev_t;

typedef struct dma_scheduler_dev {
	uint16_t stream_count;
	uint16_t free_stream_count;
	dma_stream_dev_t * streams[DMA_STREAMS_MAX_LEN];

}dma_scheduler_dev_t;

/**********************
 *  VARIABLES
 **********************/


/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

util_error_t dma2_init_scheduler(void);
dma_scheduler_dev_t * dma2_get_scheduler(void);
dma_stream_dev_t * dma2_get_streams(void);


util_error_t dma_scheduler_init(dma_scheduler_dev_t * dma_scheduler, dma_stream_dev_t * dma_streams, uint16_t nb_dma_streams);
dma_stream_dev_t * dma_scheduler_request_stream(dma_scheduler_dev_t * dma_scheduler);
util_error_t dma_scheduler_release_stream(dma_scheduler_dev_t * dma_scheduler, dma_stream_dev_t * dma_stream) ;
util_error_t dma_start_stream(dma_stream_dev_t * stream, dma_stream_config_t config);
util_error_t dma_stop_stream(dma_stream_dev_t * stream);


util_error_t dma_copy(void * dst, void * src, uint32_t len);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* DMA_H */

/* END */
