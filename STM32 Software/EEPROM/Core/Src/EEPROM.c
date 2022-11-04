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
	I2C_HandleTypeDef *I2C_Handle;

	uint8_t Device_I2C_Addr;
	uint8_t Write_Address;
	uint8_t Read_Address;

	/*			Device Info			*/
	uint16_t On_Time;					// On time updated every 15 mins
	uint16_t Accumulated_On_Time;		// Accumulated on time updated every 15 mins
	uint16_t Product_ID;					// Product ID
	uint16_t Serial_Number;			// Serial Number
	uint16_t Hardware_Major;			// Major hardware version
	uint16_t Hardware_Minor;			// Minor hardware version
	uint16_t Software_Major;			// Major software version
	uint16_t Software_Minor;			// Minor software version
	uint16_t Checksum;					// Checksum
} I2C_EEPROM;

I2C_EEPROM EEPROM;

/*			Functions			*/

HAL_StatusTypeDef Calculate_Checksum (uint16_t *pChecksum)
{
	uint8_t eepromData[EEPROM_SIZE];
	uint32_t eepromChecksum = 0;

	HAL_I2C_Mem_Read(EEPROM.I2C_Handle, EEPROM.Read_Address, 0, 2, &eepromData[0], (EEPROM_SIZE - 4), HAL_MAX_DELAY);

	for (int i = 0; i < EEPROM_SIZE; i++)
	{
		eepromChecksum += eepromData[i];
	}

	*pChecksum = eepromChecksum;

	return HAL_OK;
}

HAL_StatusTypeDef Get_Device_Info (void)
{
	HAL_StatusTypeDef status;
	uint8_t deviceInfoPage[BYTES_PER_PAGE];

	status = Page_Read((NUMBER_OF_PAGES - 1), deviceInfoPage);

	EEPROM.Accumulated_On_Time = 	((deviceInfoPage[0] << 8) | deviceInfoPage[1]);
	EEPROM.Product_ID = 			((deviceInfoPage[2] << 8) | deviceInfoPage[3]);
	EEPROM.Serial_Number = 			((deviceInfoPage[4] << 8) | deviceInfoPage[5]);
	EEPROM.Hardware_Major = 		((deviceInfoPage[6] << 8) | deviceInfoPage[7]);
	EEPROM.Hardware_Minor = 		((deviceInfoPage[8] << 8) | deviceInfoPage[9]);
	EEPROM.Software_Major = 		((deviceInfoPage[10] << 8) | deviceInfoPage[11]);
	EEPROM.Software_Minor = 		((deviceInfoPage[12] << 8) | deviceInfoPage[13]);

	EEPROM.Checksum = 				((deviceInfoPage[30] << 8) | deviceInfoPage[31]);

	return status;
}

HAL_StatusTypeDef Set_Device_Info (void)
{
	uint8_t deviceInfoPage[BYTES_PER_PAGE];

	deviceInfoPage[0] = (EEPROM.Accumulated_On_Time >> 8);
	deviceInfoPage[1] = EEPROM.Accumulated_On_Time;
	deviceInfoPage[2] = (EEPROM.Product_ID >> 8);
	deviceInfoPage[3] = EEPROM.Product_ID;
	deviceInfoPage[4] = (EEPROM.Serial_Number >> 8);
	deviceInfoPage[5] = EEPROM.Serial_Number;
	deviceInfoPage[6] = (EEPROM.Hardware_Major >> 8);
	deviceInfoPage[7] = EEPROM.Hardware_Major;
	deviceInfoPage[8] = (EEPROM.Hardware_Minor >> 8);
	deviceInfoPage[9] = EEPROM.Hardware_Minor;
	deviceInfoPage[10] = (EEPROM.Software_Major >> 8);
	deviceInfoPage[11] = EEPROM.Software_Major;
	deviceInfoPage[12] = (EEPROM.Software_Minor >> 8);
	deviceInfoPage[13] = EEPROM.Software_Minor;

	Calculate_Checksum(&EEPROM.Checksum);
	deviceInfoPage[30] = (EEPROM.Checksum >> 8 );
	deviceInfoPage[31] = EEPROM.Checksum;

	return Page_Write((NUMBER_OF_PAGES - 1), deviceInfoPage);
}

HAL_StatusTypeDef Set_Serial_Number (uint16_t Serial_Number)
{
	EEPROM.Serial_Number = 			Serial_Number;
	EEPROM.Product_ID = 			PROD_ID;
	EEPROM.Hardware_Major = 		HW_MAJOR;
	EEPROM.Hardware_Minor = 		HW_MINOR;
	EEPROM.Software_Major = 		SW_MAJOR;
	EEPROM.Software_Minor = 		SW_MINOR;

	return Set_Device_Info();
}

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr)
{
	EEPROM.I2C_Handle = I2C_Handle;

	EEPROM.Device_I2C_Addr = (0xA0 | I2C_Addr);
	EEPROM.Write_Address = ((0xA0 | I2C_Addr) & ~0x0001);
	EEPROM.Read_Address = ((0xA0 | I2C_Addr) | 0x0001);

	EEPROM.On_Time = 0;

	Get_Device_Info();
	Set_Device_Info();
}

void Update_On_Time (void)
{
	static uint32_t current, start = 0, delta;

	current = HAL_GetTick();
	delta = ((current - start) / 60000);

	if (delta >= ON_TIME_UPDATE_RATE)
	{
		if (EEPROM.On_Time < 0xFFFF)
		{
			EEPROM.On_Time++;
		}

		if (EEPROM.Accumulated_On_Time < 0xFFFF)
		{
			EEPROM.Accumulated_On_Time++;
		}
		start = current;
		Set_Device_Info();
	}
}

HAL_StatusTypeDef Write_all (uint8_t Byte)
{
	uint8_t data[BYTES_PER_PAGE];
	for (int i = 0; i < BYTES_PER_PAGE; i++)
	{
		data[i] = Byte;
	}

	for (int i = 0; i < (NUMBER_OF_PAGES - DEVICE_INFO_SIZE); i++)
	{
		Page_Write(i, &data[0]);
	}

	return HAL_OK;
}

HAL_StatusTypeDef Byte_Write (uint16_t Address, uint8_t *pByte)
{
	if (Address >= EEPROM_SIZE)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Write(EEPROM.I2C_Handle, EEPROM.Write_Address, Address, 2, pByte, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Page_Write (uint16_t Page_Number, uint8_t *pPage)
{
	if (Page_Number >= NUMBER_OF_PAGES)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Write(EEPROM.I2C_Handle, EEPROM.Write_Address, (Page_Number * BYTES_PER_PAGE),
								2, pPage, BYTES_PER_PAGE, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Byte_Read (uint16_t Address, uint8_t *pByte)
{
	if (Address >= EEPROM_SIZE)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Read(EEPROM.I2C_Handle, EEPROM.Read_Address, Address, 2, pByte, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef Page_Read (uint16_t Page_Number, uint8_t *pPage)
{
	if (Page_Number >= NUMBER_OF_PAGES)
	{
		return HAL_ERROR;
	}

	HAL_Delay(5);
	return HAL_I2C_Mem_Read(EEPROM.I2C_Handle, EEPROM.Write_Address, (Page_Number * BYTES_PER_PAGE),
								2, pPage, BYTES_PER_PAGE, HAL_MAX_DELAY);
}



