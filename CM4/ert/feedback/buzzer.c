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
#include "note.h"
#include "still_alive.h"

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
#define NOTE_MAGIC	4
#define RYTM_MAGIC  2000


#define COMPUTE_NOTE(note) (TIMER_FREQ)/(NOTE_MAGIC)/(note)

#define COMPUTE_RYTM(time) (TIMER_FREQ)/(RYTM_MAGIC)/(time)


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

void buzzer_note_interrupt(void) {
	static uint8_t state = 0;
	if(state) {
		gpio_set(BUZZER_PORT, BUZZER_PIN);
		state = 0;
	} else {
		gpio_clr(BUZZER_PORT, BUZZER_PIN);
		state = 1;
	}
}

void buzzer_rytm_interrupt(void) {
	NOTE_TIMER->ARR = COMPUTE_NOTE(A4);
}

void buzzer_init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = BUZZER_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);

	NOTE_TIMER->ARR = 0;
	HAL_TIM_Base_Start_IT(&RYTM_TIMER_DEV);
	HAL_TIM_Base_Start_IT(&NOTE_TIMER_DEV);

}

/* END */
