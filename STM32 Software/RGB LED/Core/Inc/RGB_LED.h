/*
 * @file: RGB_LED.h
 * @created: Sep 13, 2022
 * @Author: Tom Fry
 * @brief: Header file for RGB_LED.c
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

/*			Defines			*/
#define NUMBER_OF_LEDS	1

/*			Types			*/
typedef struct _RGB_LED
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;

	uint8_t Brightness;
} RGB_LED;

/*			Exported Functions			*/


#endif /* INC_RGB_LED_H_ */
