/*  Title       : Led
 *  Filename    : led.h
 *  Author      : iacopo sprenger
 *  Date        : 20.01.2021
 *  Version     : 0.1
 *  Description : rgb led control
 */

#ifndef LED_H
#define LED_H



/**********************
 *  INCLUDES
 **********************/

#include <stdint.h>

/**********************
 *  CONSTANTS
 **********************/

#define LED_RED			0xff, 0x00, 0x00
#define LED_GREEN		0x00, 0xff, 0x00
#define LED_BLUE		0x00, 0x00, 0xff

#define LED_ORANGE		0x7f, 0x0f, 0x07
#define LED_YELLOW		0xff, 0x1f, 0x07
#define LED_TEAL		0x00, 0x7f, 0x7f
#define LED_PINK		0x7f, 0x00, 0x7f
#define LED_LILA		0xff, 0x03, 0x4f

#define LED_BLACK		0x00, 0x00, 0x00
#define LED_WHITE		0x2f, 0x2f, 0x2f


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

void led_init(void);

void led_set_color(uint8_t r, uint8_t g, uint8_t b);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* LED_H */

/* END */
