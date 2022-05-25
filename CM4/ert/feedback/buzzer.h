/*  Title       : Buzzer
 *  Filename    : buzzer.h
 *  Author      : iacopo sprenger
 *  Date        : 25.04.2022
 *  Version     : 0.1
 *  Description : software control for a buzzer
 */

#ifndef BUZZER_H
#define BUZZER_H



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

void buzzer_note_interrupt(void);
void buzzer_rytm_interrupt(void);
void buzzer_enable(void);
void buzzer_disable(void);
void buzzer_init(void);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* BUZZER_H */

/* END */
