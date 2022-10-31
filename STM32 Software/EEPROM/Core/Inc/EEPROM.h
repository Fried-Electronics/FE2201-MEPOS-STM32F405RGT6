/*
 * EEPROM.h
 *
 *  Created on: Oct 31, 2022
 *      Author: Tom Fry
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#include "main.h"

#define BYTES_PER_PAGE		32
#define NUMBER_OF_PAGES		250

void Init_EEPROM (I2C_HandleTypeDef *I2C_Handle, uint8_t I2C_Addr);
HAL_StatusTypeDef Byte_Write (uint16_t Addr, uint8_t Byte);
HAL_StatusTypeDef Word_Write (uint16_t Addr, uint8_t Word);
uint8_t Byte_Read (uint16_t Addr);
uint16_t Word_Read (uint16_t Addr);

#endif /* INC_EEPROM_H_ */
