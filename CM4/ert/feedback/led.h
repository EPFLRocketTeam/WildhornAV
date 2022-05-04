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
#define LED_WHITE		0xff, 0xff, 0xff





/**********************
 *  MACROS
 **********************/


/**********************
 *  TYPEDEFS
 **********************/

typedef struct led_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
}led_color_t;



/**********************
 *  VARIABLES
 **********************/

static const led_color_t led_red = {
		.r = 0xff,
		.g = 0x00,
		.b = 0x00
};

static const led_color_t led_green = {
		.r = 0x00,
		.g = 0xff,
		.b = 0x00
};

static const led_color_t led_blue = {
		.r = 0x00,
		.g = 0x00,
		.b = 0xff
};

static const led_color_t led_black = {
		.r = 0x00,
		.g = 0x00,
		.b = 0x00
};



/**********************
 *  PROTOTYPES
 **********************/

#ifdef __cplusplus
extern "C"{
#endif

void led_rgb_init(void);

void led_rgb_set_color(led_color_t color);

void led_rgb_set_rgb(uint8_t r, uint8_t g, uint8_t b);

void led_feedback_init(void);

void led_rgb_thread(void * arg);

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* LED_H */

/* END */
