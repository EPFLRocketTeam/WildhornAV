/*  Title		: I2C
 *  Filename	: i2c.c
 *	Author		: iacopo sprenger
 *	Date		: 22.04.2022
 *	Version		: 0.1
 *	Description	: i2c interface for the generic device driver
 */

/**********************
 *	INCLUDES
 **********************/

#include <main.h>
#include <driver/i2c.h>
#include <device/device.h>
#include <i2c.h>
#include <util.h>

/**********************
 *	CONSTANTS
 **********************/

#define S1_I2C		hi2c1
#define S2_I2C		hi2c2
#define S3_I2C		hi2c5

/**********************
 *	MACROS
 **********************/


/**********************
 *	TYPEDEFS
 **********************/



/**********************
 *	VARIABLES
 **********************/

device_interface_t sensor_interface;

i2c_interface_context_t sensor_interface_context = {
		.i2c = &S2_I2C
};


/**********************
 *	PROTOTYPES
 **********************/


/**********************
 *	DECLARATIONS
 **********************/

void i2c_spi_guard(void) {
	//disable spi on S2 due to broken sensor board...
	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

device_interface_t * i2c_get_sensor_interface(void) {
	return &sensor_interface;
}

void i2c_init(void) {
	util_error_t error = ER_SUCCESS;

	device_interface_create(&sensor_interface, (void *) &sensor_interface_context, NULL, NULL, NULL, NULL);

}

/* END */
