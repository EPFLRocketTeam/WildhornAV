/*  Title		: Control
 *  Filename	: control.c
 *	Author		: iacopo sprenger
 *	Date		: 20.01.2022
 *	Version		: 0.1
 *	Description	: control
 */

/**********************
 *	INCLUDES
 **********************/

#include <main.h>
#include <gpio.h>
#include <usart.h>


#include <cmsis_os.h>

#include <driver/serial.h>
#include <device/device.h>
#include <device/i2c_sensor.h>

#include <control.h>
#include <feedback/led.h>
#include <feedback/buzzer.h>

#include <abstraction/gpio.h>

/**********************
 *	CONSTANTS
 **********************/

#define CONTROL_HEART_BEAT	200


/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/

typedef enum control_state {
	CONTROL_IDLE,
	CONTROL_CALIBRATION,
	CONTROL_ARMED,
	CONTROL_POWERED,
	CONTROL_COAST,
	CONTROL_APOGEE,
	CONTROL_DROGUE,
	CONTROL_EVENT,
	CONTROL_MAIN,
	CONTROL_TOUCHDOWN,
	CONTROL_BALLISTIC,
	CONTROL_ERROR,
	CONTROL_ABORT
}control_state_t;


typedef struct control {
	control_state_t state;
}control_t;


/**********************
 *	VARIABLES
 **********************/

control_t control;

/**********************
 *	PROTOTYPES
 **********************/

void control_idle_start(void);
void control_idle_run(void);

void control_calibration_start(void);
void control_calibration_run(void);

void control_armed_start(void);
void control_armed_run(void);

void control_powered_start(void);
void control_powered_run(void);

void control_supersonic_start(void);
void control_supersonic_run(void);

void control_coast_start(void);
void control_coast_run(void);

void control_apogee_start(void);
void control_apogee_run(void);

void control_drogue_start(void);
void control_drogue_run(void);

void control_event_start(void);
void control_event_run(void);

void control_main_start(void);
void control_main_run(void);

void control_touchdown_start(void);
void control_touchdown_run(void);

void control_ballistic_start(void);
void control_ballistic_run(void);

void control_error_start(void);
void control_error_run(void);

void control_abort_start(void);
void control_abort_run(void);




/**********************
 *	DECLARATIONS
 **********************/

void control_thread(void * arg) {
	static TickType_t last_wake_time;
	static const TickType_t period = pdMS_TO_TICKS(500);
	last_wake_time = xTaskGetTickCount();





	for(;;) {


		vTaskDelayUntil( &last_wake_time, period );
	}
}

void control_idle_start(void) {
	control.state = CONTROL_IDLE;

}
void control_idle_run(void) {

}

void control_calibration_start(void) {

}
void control_calibration_run(void) {

}

void control_armed_start(void) {

}
void control_armed_run(void) {

}

void control_powered_start(void) {

}
void control_powered_run(void) {

}

void control_supersonic_start(void) {

}
void control_supersonic_run(void) {

}

void control_coast_start(void) {

}
void control_coast_run(void) {

}

void control_apogee_start(void) {

}
void control_apogee_run(void) {

}

void control_drogue_start(void) {

}
void control_drogue_run(void) {

}

void control_event_start(void) {

}
void control_event_run(void) {

}

void control_main_start(void) {

}
void control_main_run(void) {

}

void control_touchdown_start(void) {

}
void control_touchdown_run(void) {

}

void control_ballistic_start(void) {

}
void control_ballistic_run(void) {

}

void control_error_start(void) {

}
void control_error_run(void) {

}

void control_abort_start(void) {

}
void control_abort_run(void) {

}


/* END */
