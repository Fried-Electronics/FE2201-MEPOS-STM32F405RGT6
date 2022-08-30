/*
 * ASCII_Parser.c
 *
 *  Created on: 30 Aug 2022
 *      Author: Tom Fry
 */

/*			Includes			*/
#include "main.h"
#include "usbd_cdc_if.h"
#include "ASCII_Parser.h"


/*			Private Variables			*/
uint16_t HeadRxBufferHS = 0;	// Head of the Rx buffer
uint16_t TailRxBufferHS = 0;	// Tail of the Rx buffer

/*			Function Prototypes			*/

/*			Function Implementations			*/

/**
  * @brief  Increments the head of the USB buffer
  * @param  Length: Length of the last USB message
  * @retval None
  */
void Increment_Head (uint32_t *Length)
{
	HeadRxBufferHS += *Length;
}

/**
  * @brief  Decrements the tail of the USB buffer
  * @param  Length: Length of the size of USB data read
  * @retval None
  */
static void Decrement_Tail (uint32_t *Length)
{
	TailRxBufferHS -= *Length;
}

/**
  * @brief  Checks for new data in the USB buffer
  * @param  None
  * @retval 0 for no new data, 1 for new data to be parsed
  */
uint8_t Check_Data_Available (void)
{
	uint8_t DataAvailable = 0;

	if (HeadRxBufferHS != TailRxBufferHS)
	{
		DataAvailable = 1;
	}

	return DataAvailable;
}
