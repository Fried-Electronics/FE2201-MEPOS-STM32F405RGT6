/*
 * EEPROM.h
 *
 *  Created on: Oct 31, 2022
 *      Author: Tom Fry
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "main.h"

#define DEVICE_INFO_SIZE	1
#define BYTES_PER_PAGE		32
#define NUMBER_OF_PAGES		250
#define EEPROM_SIZE			(BYTES_PER_PAGE * NUMBER_OF_PAGES)

#define ON_TIME_UPDATE_RATE	30			// Minutes per LSB

/*			Device Info			*/

#define PROD_ID				1
#define HW_MAJOR			0
#define HW_MINOR			1
#define SW_MAJOR			0
#define SW_MINOR			1

/*			Exported Functions			*/

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr);
void Update_On_Time (void);
HAL_StatusTypeDef Set_Serial_Number (uint16_t Serial_Number);

HAL_StatusTypeDef Byte_Write (uint16_t Address, uint8_t *pByte);
HAL_StatusTypeDef Page_Write (uint16_t Page_Number, uint8_t *pPage);

HAL_StatusTypeDef Byte_Read (uint16_t Address, uint8_t *pByte);
HAL_StatusTypeDef Page_Read (uint16_t Page_Number, uint8_t *pPage);

#endif /* INC_EEPROM_H_ */
