/*  Title       : GPIO
 *  Filename    : gpio.h
 *  Author      : iacopo sprenger
 *  Date        : 30.03.2021
 *  Version     : 0.1
 *  Description : gpio hardware abstraction
 */

#ifndef GPIO_H
#define GPIO_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/

#define GPIO_PORTA_ADDR	50002000
#define GPIO_PORTB_ADDR	50003000
#define GPIO_PORTC_ADDR	50004000
#define GPIO_PORTD_ADDR	50005000
#define GPIO_PORTE_ADDR	50006000
#define GPIO_PORTF_ADDR	50007000
#define GPIO_PORTG_ADDR	50008000
#define GPIO_PORTH_ADDR	50008000


#define GPIO_PIN0	1<<0
#define GPIO_PIN1	1<<1
#define GPIO_PIN2	1<<2
#define GPIO_PIN3	1<<3
#define GPIO_PIN4	1<<4
#define GPIO_PIN5	1<<5
#define GPIO_PIN6	1<<6
#define GPIO_PIN7	1<<7
#define GPIO_PIN8	1<<8
#define GPIO_PIN9	1<<9
#define GPIO_PIN10	1<<10
#define GPIO_PIN11	1<<11
#define GPIO_PIN12	1<<12
#define GPIO_PIN13	1<<13
#define GPIO_PIN14	1<<14
#define GPIO_PIN15	1<<15



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



#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* GPIO_H */

/* END */
