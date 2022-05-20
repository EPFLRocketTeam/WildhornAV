/*  Title		: Threads
 *  Filename	: threads.c
 *	Author		: iacopo sprenger
 *	Date		: 20.02.2022
 *	Version		: 0.1
 *	Description	: template for code files
 */

/**********************
 *	INCLUDES
 **********************/


#include <cmsis_os.h>
#include <threads.h>
#include <wildhorn.h>
#include <feedback/led.h>
#include <feedback/buzzer.h>
#include <driver/serial.h>
#include <driver/i2c.h>


#include <control.h>


/**********************
 *	CONSTANTS
 **********************/

#define DEFAULT_SZ	(1024)

#define CONTROL_SZ		DEFAULT_SZ
#define CONTROL_PRIO	(6)

#define LED_RGB_SZ		DEFAULT_SZ
#define LED_RGB_PRIO	(0)


/**********************
 *	MACROS
 **********************/

#define CREATE_THREAD(handle, name, func, cont, sz, prio) \
	static StaticTask_t name##_buffer; \
	static StackType_t name##_stack[ sz ]; \
	handle = xTaskCreateStatic( \
			func, \
	        #name, \
			sz, \
			( void * ) cont, \
			prio, \
			name##_stack, \
			&name##_buffer)

/**********************
 *	TYPEDEFS
 **********************/


/**********************
 *	VARIABLES
 **********************/

static TaskHandle_t control_handle = NULL;
static TaskHandle_t led_rgb_handle = NULL;

/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/


void threads_init(void) {

	serial_init();

#if WH_HAS_FEEDBACK == WH_TRUE
	buzzer_init();
	led_feedback_init();
	serial_feedback_init();

#endif

#if WH_HAS_SENSORS == WH_TRUE
	i2c_spi_guard();
	i2c_init();
#endif

	CREATE_THREAD(led_rgb_handle, led_rgb, led_rgb_thread, LED_RGB_PRIO, LED_RGB_SZ, 0);


	CREATE_THREAD(control_handle, control, control_thread, 0, CONTROL_SZ, CONTROL_PRIO);

}


/* END */
