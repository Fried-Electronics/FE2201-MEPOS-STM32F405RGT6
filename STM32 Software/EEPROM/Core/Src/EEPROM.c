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
	I2C_HandleTypeDef *I2C_Handle;

	uint8_t Device_Select;
	uint8_t Write_Address;
	uint8_t Read_Address;
} I2C_EEPROM;

I2C_EEPROM EEPROM;

/*			Functions			*/

uint32_t Calculate_Checksum (void)
{
	uint32_t checksum = 0;

	return checksum;
}

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr)
{
	EEPROM.Device_I2C_Addr = I2C_Addr;
	EEPROM.I2C_Handle = I2C_Handle;

	EEPROM.Device_Select = (0xA0 | I2C_Addr);
	EEPROM.Write_Address = ((0xA0 | I2C_Addr) & ~0x0001);
	EEPROM.Read_Address = ((0xA0 | I2C_Addr) | 0x0001);
}

HAL_StatusTypeDef Byte_Write (uint16_t Address, uint8_t *pByte)
{
	if (Address > EEPROM_SIZE)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Write(EEPROM.I2C_Handle, EEPROM.Write_Address, Address, 2, pByte, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Page_Write (uint16_t Page_Number, uint8_t *pPage)
{
	if (Page_Number > NUMBER_OF_PAGES)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Write(EEPROM.I2C_Handle, EEPROM.Write_Address, (Page_Number * BYTES_PER_PAGE),
								2, pPage, BYTES_PER_PAGE, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Byte_Read (uint16_t Address, uint8_t *pByte)
{
	if (Address > EEPROM_SIZE)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Read(EEPROM.I2C_Handle, EEPROM.Read_Address, Address, 2, pByte, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Page_read (uint16_t Page_Number, uint8_t *pPage)
{
	if (Page_Number > NUMBER_OF_PAGES)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Read(EEPROM.I2C_Handle, EEPROM.Write_Address, (Page_Number * BYTES_PER_PAGE),
								2, pPage, BYTES_PER_PAGE, HAL_MAX_DELAY);
}



