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
#include <device/i2c_sensor.h>
#include <control.h>
#include <device/hostproc.h>
#include <sensor.h>
#include <od/od.h>


/**********************
 *	CONSTANTS
 **********************/

#define DEFAULT_SZ	(1024)

#define OD_SZ           DEFAULT_SZ
#define OD_PRIO         (6)

#define CONTROL_SZ		DEFAULT_SZ
#define CONTROL_PRIO	(6)

#define LED_RGB_SZ		DEFAULT_SZ
#define LED_RGB_PRIO	(1)

#define SENSOR_I2C_SZ	DEFAULT_SZ
#define SENSOR_I2C_PRIO	(6)


/**********************
 *	MACROS
 **********************/

/**
 * @brief 	macro to declare a static thread in FreeRTOS
 * @details	This macros make the necessary funtion calls to setup a stack and
 * 			working area for the declaration of a static FreeRTOS thread.
 *
 * @param	handle	A @p TaskHandle_t object to reference the created Thread.
 * @param	name	A name for thread.
 * @param 	func	The entry point for the thread.
 * @param 	cont	The context for the thread.
 * @param 	sz		The desired size for the thread stack.
 * @param	prio	The priority for the thread.
 */
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

static TaskHandle_t od_handle = NULL;
static TaskHandle_t control_handle = NULL;
static TaskHandle_t led_rgb_handle = NULL;
static TaskHandle_t sensor_i2c_handle = NULL;

/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

/**
 * @brief	Initialize all the threads of Wildhorn AV
 * @details	This is the only function that needs to be called from the ST
 * 			Auto-generated files. This is clever in case the autogeneration
 * 			fails. This will minimize the code to be rewritten.
 *
 */
void threads_init(void) {

	//initialize serial
	serial_init();

	//initialize hostproc comm
	hostproc_init();

	// initialize object dictionary
	od_init();

#if WH_HAS_FEEDBACK == WH_TRUE
#if WH_USE_BUZZER == WH_TRUE
	buzzer_init();
#endif
	led_feedback_init();
#endif

#if WH_HAS_SENSORS == WH_TRUE
	i2c_spi_guard();
	i2c_init();
	i2c_sensor_init();
#endif


	CREATE_THREAD(od_handle, od, od_update_task, NULL, OD_SZ, OD_PRIO);


	CREATE_THREAD(led_rgb_handle, led_rgb, led_rgb_thread, NULL, LED_RGB_SZ, LED_RGB_PRIO);


	CREATE_THREAD(control_handle, control, control_thread, NULL, CONTROL_SZ, CONTROL_PRIO);


	CREATE_THREAD(sensor_i2c_handle, sensor_i2c, sensor_i2c_thread, NULL, SENSOR_I2C_SZ, SENSOR_I2C_PRIO);


}


/* END */
