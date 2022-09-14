/*
 * @file: RGB_LED.c
 * @created: Sep 13, 2022
 * @Author: Tom Fry
 * @brief: Source file for controlling the RGB LED on the board
 */

/*			Includes			*/
#include "RGB_LED.h"
#include "main.h"

/*			Global Variables			*/
static uint32_t PWM_Buffer[PWM_BUFFER_LENGTH];
static RGB_LED LED_Buffer[NUMBER_OF_LEDS];
static TIM_HandleTypeDef *RGB_LED_Timer;
static uint8_t RGB_LED_Timer_Channel;

/*			Function Prototypes			*/

/*			Function Implementations			*/

void RGB_LED_Init (TIM_HandleTypeDef *htim, uint8_t TIM_CHANNEL)
{
	RGB_LED led;
	led.Red = 0;
	led.Green = 0;
	led.Blue = 0;
	led.Brightness = 0;

	for (int i = 0; i < NUMBER_OF_LEDS; i++)
	{
		LED_Buffer[i] = led;
	}

	RGB_LED_Timer = htim;
	RGB_LED_Timer_Channel = TIM_CHANNEL;
	Update_All_PWM_Buffer();
}

void Set_Standard_Colour (uint8_t LED_Index, Standard_Colours Colour, uint8_t Brightness)
{
	RGB_LED led;

	switch (Colour) {
		case Red:
			led.Red = 255;
			led.Green = 0;
			led.Blue = 0;
			break;
		case Green:
			led.Red = 0;
			led.Green = 255;
			led.Blue = 0;
			break;
		case Blue:
			led.Red = 0;
			led.Green = 0;
			led.Blue = 255;
			break;
		default:
			break;
	}

	led.Red = (led.Red * (Brightness / 255));
	led.Green = (led.Green * (Brightness / 255));
	led.Blue = (led.Blue * (Brightness / 255));

	LED_Buffer[LED_Index] = led;
	Update_All_PWM_Buffer();
}

void Update_All_PWM_Buffer (void)
{
	for (int ledIndex = 0; ledIndex < NUMBER_OF_LEDS; ledIndex++)
	{
		for (int bitIndex = 7; bitIndex > -1; bitIndex--)
		{
			uint8_t greenValue = LOW_LEVEL;
			uint8_t redValue = LOW_LEVEL;
			uint8_t blueValue = LOW_LEVEL;

			if ((LED_Buffer[ledIndex].Green >> bitIndex) & 0x01)
			{
				greenValue = HIGH_LEVEL;
			}
			if ((LED_Buffer[ledIndex].Red >> bitIndex) & 0x01)
			{
				redValue = HIGH_LEVEL;
			}
			if ((LED_Buffer[ledIndex].Blue >> bitIndex) & 0x01)
			{
				blueValue = HIGH_LEVEL;
			}

			PWM_Buffer[(ledIndex * NUMBER_OF_BITS) + bitIndex] = greenValue;
			PWM_Buffer[(ledIndex * NUMBER_OF_BITS) + bitIndex + 8] = redValue;
			PWM_Buffer[(ledIndex * NUMBER_OF_BITS) + bitIndex + 16] = blueValue;
		}
	}

	HAL_TIM_PWM_Start_DMA(RGB_LED_Timer, RGB_LED_Timer_Channel, PWM_Buffer, PWM_BUFFER_LENGTH);
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_3);
}
