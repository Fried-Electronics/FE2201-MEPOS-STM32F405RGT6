/*
 * EEPROM.c
 *
 *  Created on: Oct 31, 2022
 *      Author: Tom Fry
 */

#include "EEPROM.h"

/*			Types			*/

typedef struct _I2C_EEPROM
{
	uint8_t Device_I2C_Addr;
	uint8_t Device_Select;
	I2C_HandleTypeDef *I2C_Handle;
} I2C_EEPROM;

I2C_EEPROM EEPROM;

/*			Functions			*/

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr)
{
	EEPROM.Device_I2C_Addr = I2C_Addr;
	EEPROM.Device_Select = (0xA0 | I2C_Addr);
	EEPROM.I2C_Handle = I2C_Handle;
}

HAL_StatusTypeDef Byte_Write (uint16_t Addr, uint8_t Byte)
{
	HAL_StatusTypeDef status;
	uint8_t buffer[2];

	buffer[0] = EEPROM.Device_Select;
	buffer[0] &= ~0x0001;

	buffer[1] = Byte;

	status = HAL_I2C_Mem_Write(EEPROM.I2C_Handle, buffer[0], Addr, 2, &buffer[1], 1, 100);

	HAL_Delay(100);

	return status;
}

HAL_StatusTypeDef Word_Write (uint16_t Addr, uint8_t Word)
{


	return HAL_OK;
}

uint8_t Byte_Read (uint16_t Addr)
{
	uint8_t buffer[2];

	buffer[0] = EEPROM.Device_Select;
	buffer[0] |= 0x0001;

	buffer[1] = 0;

	HAL_I2C_Mem_Read(EEPROM.I2C_Handle, buffer[0], Addr, 2, &buffer[1], 1, 100);

	HAL_Delay(100);

	return buffer[1];
}

uint16_t Word_Read (uint16_t Addr)
{
	uint16_t word;

	word = 0;

	return word;
}
