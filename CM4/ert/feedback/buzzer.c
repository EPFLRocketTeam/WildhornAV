/*  Title       : Buzzer
 *  Filename    : buzzer.h
 *  Author      : iacopo sprenger
 *  Date        : 25.04.2022
 *  Version     : 0.1
 *  Description : software control for a buzzer
 */

/**********************
 *	INCLUDES
 **********************/

#include <main.h>
#include <tim.h>
#include "buzzer.h"
#include <abstraction/gpio.h>
#include <feedback/still_alive.h>
#include "note.h"

/**********************
 *	CONSTANTS
 **********************/

#define NOTE_TIMER_DEV	htim14
#define RYTM_TIMER_DEV	htim16

#define NOTE_TIMER	NOTE_TIMER_DEV.Instance
#define RYTM_TIMER	RYTM_TIMER_DEV.Instance

#define BUZZER_PIN	GPIO_PIN_3
#define BUZZER_PORT	GPIOC


/**********************
 *	MACROS
 **********************/

#define TIMER_FREQ	200e6
#define NOTE_PRESC	10		//timer prescaler+1
#define RYTM_PRESC	20000	//timer prescaler+1
#define TIMER_TRIM	-1e6


#define COMPUTE_NOTE(note) 	((((TIMER_FREQ)+(TIMER_TRIM))*10)/(NOTE_PRESC)/(note))/2
#define RYTM_MS(ms)			(ms)*(((TIMER_FREQ)+(TIMER_TRIM))/(RYTM_PRESC))/(1000)
#define COMPUTE_RYTM(time)	RYTM_MS((time)*100)


/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/
static uint16_t melody_state = 0;
static uint8_t state = 0;
static uint8_t melody_active = 1;

/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

void buzzer_note_interrupt(void) {
	if(melody_active) {
		if(state) {
			gpio_set(BUZZER_PORT, BUZZER_PIN);
			state = 0;
		} else {
			gpio_clr(BUZZER_PORT, BUZZER_PIN);
			state = 1;
		}
	}
}

void buzzer_rytm_interrupt(void) {
	if(still_alive[melody_state] == 0) {
		melody_active = 0;
		gpio_clr(GPIOA, GPIO_PIN_0);
	} else {
		NOTE_TIMER->ARR = COMPUTE_NOTE(still_alive[melody_state]);
		melody_active = 1;
		gpio_set(GPIOA, GPIO_PIN_0);
	}

	melody_state++;
	if(melody_state == still_alive_len) {
		melody_state=0;
	}
}

/*
void buzzer_rytm_interrupt(void) {
	melody_active = 1;
	if(still_alive[melody_state].freq == 0) {
		melody_active = 0;
		gpio_clr(GPIOA, GPIO_PIN_0);
		RYTM_TIMER->ARR = COMPUTE_RYTM(still_alive[melody_state].time)/2;
	} else {
		melody_active = 1;
		gpio_set(GPIOA, GPIO_PIN_0);
		NOTE_TIMER->ARR = COMPUTE_NOTE(still_alive[melody_state].freq);
		RYTM_TIMER->ARR = COMPUTE_RYTM(still_alive[melody_state].time);
	}

	melody_state++;
	if(melody_state == still_alive_len) {
		melody_state=0;
	}
}

*/

void buzzer_enable(void) {
	HAL_TIM_Base_Start_IT(&RYTM_TIMER_DEV);
	HAL_TIM_Base_Start_IT(&NOTE_TIMER_DEV);
}

void buzzer_disable(void) {
	HAL_TIM_Base_Stop_IT(&RYTM_TIMER_DEV);
	HAL_TIM_Base_Stop_IT(&NOTE_TIMER_DEV);
}

void buzzer_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = BUZZER_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

	NOTE_TIMER->ARR = COMPUTE_NOTE(A4);
	RYTM_TIMER->ARR = COMPUTE_RYTM(2);
	RYTM_TIMER->CNT = 0;
	melody_active=0;

	HAL_TIM_Base_Start_IT(&RYTM_TIMER_DEV);
	HAL_TIM_Base_Start_IT(&NOTE_TIMER_DEV);

}

/* END */
