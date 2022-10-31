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
	uint8_t Device_Addr;
	I2C_HandleTypeDef *I2C_Handle;
} I2C_EEPROM;

I2C_EEPROM EEPROM;

/*			Functions			*/

static uint8_t Calculate_Memory_Address (void)
{
	uint8_t address = 0xA0;

	address |= EEPROM.Device_Addr;

	return address;
}

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr)
{
	EEPROM.Device_Addr = I2C_Addr;
	EEPROM.I2C_Handle = I2C_Handle;
}

HAL_StatusTypeDef Byte_Write (uint16_t Addr, uint8_t Byte)
{
	uint8_t buffer[4];

	buffer[0] = Calculate_Memory_Address();
	buffer[0] &= ~0x0001;

	buffer[1] = ((Addr &= 0xFF00) >> 8);
	buffer[2] = (Addr &= 0x00FF);
	buffer[3] = Byte;

	return HAL_I2C_Mem_Write(EEPROM.I2C_Handle, buffer[0], buffer[1], 2, &buffer[3], 1, 100);
}

HAL_StatusTypeDef Word_Write (uint16_t Addr, uint8_t Word)
{


	return HAL_OK;
}

uint8_t Byte_Read (uint16_t Addr)
{
	uint8_t buffer[4];

	buffer[0] = Calculate_Memory_Address();
	buffer[0] |= 0x0001;

	buffer[1] = ((Addr &= 0xFF00) >> 8);
	buffer[2] = (Addr &= 0x00FF);
	buffer[3] = 0;

	HAL_I2C_Mem_Read(EEPROM.I2C_Handle, buffer[0], buffer[1], 2, &buffer[3], 1, 100);

	return buffer[3];
}

uint16_t Word_Read (uint16_t Addr)
{
	uint16_t word;

	word = 0;

	return word;
}
