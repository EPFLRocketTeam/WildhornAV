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

/**
 * @brief This is the I2C Interface associated with the sensors
 */
device_interface_t sensor_interface;

i2c_interface_context_t sensor_interface_context = {
		.i2c = &S2_I2C
};


/**********************
 *	PROTOTYPES
 **********************/

util_error_t i2c_send(void * context, uint8_t * data, uint32_t len);
util_error_t i2c_recv(void * context, uint8_t * data, uint32_t * len);


/**********************
 *	DECLARATIONS
 **********************/

/**
 * @brief This funcion disables completely the SPI for hardware saveguard.
 */
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

/**
 * @brief 	Getter for the interface associated with the sensors
 * 
 * @return	The pointer to the sensor interface object
 */
device_interface_t * i2c_get_sensor_interface(void) {
	return &sensor_interface;
}


/**
 * @brief I2C send
 *
 * @param context	The device interface context generic pointer.
 * @param data		Pointer to the data to be transmitted (first byte is the
 * 					I2C device address.)
 * @param len		length of the data array
 */
util_error_t i2c_send(void * context, uint8_t * data, uint32_t len) {
	i2c_interface_context_t * ctx = (i2c_interface_context_t *) context;
	if(HAL_I2C_Master_Transmit_IT(ctx->i2c, data[0], &(data[1]), len-1) != HAL_OK) {
		return ER_FAILURE;
	}
	return ER_SUCCESS;
}

/**
 * @brief I2C recv
 *
 * @param context	The device interface context generic pointer.
 * @param data		Pointer to store the received data (first byte is the
 * 					I2C device address.)
 * @param len		length of the data array
 *
 * @note 	The received data will start at data+1 as the first byte is the I2C
 * 			device address.
 */
util_error_t i2c_recv(void * context, uint8_t * data, uint32_t * len) {
	i2c_interface_context_t * ctx = (i2c_interface_context_t *) context;
	if(HAL_I2C_Master_Receive_IT(ctx->i2c, data[0], &(data[1]), (*len)-1) != HAL_OK) {
		return ER_FAILURE;
	}
	return ER_SUCCESS;
}

/**
 * @brief	Initializer for the i2c subsystem.
 * @deails	This function initializes the three i2c interfaces which are present on the hostboards.
 *
 */
void i2c_init(void) {
	device_interface_create(&sensor_interface,
									(void *) &sensor_interface_context,
									NULL,
									i2c_send,
									i2c_recv,
									NULL);
}

/* END */
