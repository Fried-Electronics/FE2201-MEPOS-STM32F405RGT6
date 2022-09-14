/*
 * @file: RGB_LED.h
 * @created: Sep 13, 2022
 * @Author: Tom Fry
 * @brief: Header file for RGB_LED.c
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

/*			Includes			*/
#include "main.h"

/*			Defines			*/
#define NUMBER_OF_LEDS	1
#define NUMBER_OF_BITS	24
#define PWM_BUFFER_LENGTH ((NUMBER_OF_BITS * NUMBER_OF_LEDS) + 80)

#define LOW_LEVEL		25
#define HIGH_LEVEL		59

/*			Types			*/
typedef struct _RGB_LED
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;

	uint8_t Brightness;
} RGB_LED;

typedef enum _Standard_Colours
{
	Red,
	Green,
	Blue
} Standard_Colours;

/*			Exported Functions			*/
void Set_Standard_Colour (uint8_t LED_Index, Standard_Colours Colour, uint8_t Brightness);
void Update_All_PWM_Buffer (void);
void RGB_LED_Init (TIM_HandleTypeDef *htim, uint8_t TIM_CHANNEL);

/*			Exported Variables			*/
//extern uint32_t PWM_Buffer[PWM_BUFFER_LENGTH];

#endif /* INC_RGB_LED_H_ */
