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
#include "string.h"

/*			Private Variables			*/
uint16_t HeadRxBufferHS = 0;	// Head of the Rx buffer
uint16_t TailRxBufferHS = 0;	// Tail of the Rx buffer

CommandTypeDef CommandBuffer[MAX_NUMBER_OF_COMMANDS];
uint16_t CommandBufferCount = 0;

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

/**
  * @brief  Adds a new command to the command buffer
  * @param	String: String for the command
  * @param	Enum: Enum value to be returned when this command is matched when parsed
  * @retval -1 for error, 1 for no error
  */
int8_t New_Command (char *String, uint16_t Enum)
{
	int8_t ReturnValue = 1; // No error
	CommandTypeDef Command;

	if (CommandBufferCount >= MAX_NUMBER_OF_COMMANDS)
	{
		ReturnValue = -1;
	}

	if (ReturnValue != -1)
	{
		strcpy(Command.Command_String, String);
		Command.Command_Length = strlen(String);
		Command.Enum = Enum;

		CommandBuffer[CommandBufferCount++] = Command;
	}
	return ReturnValue;
}

/**
  * @brief  Searches the command buffer for the string
  * @param  String: String of the new incoming command
  * @retval -1 for invalid command, any other value for a match
  */
int16_t Search_Command_Buffer (char *String)
{
	int8_t ReturnEnum = -1;

	for (int i = 0; i < CommandBufferCount; i++)
	{
		if (strncmp(String, CommandBuffer[i].Command_String, CommandBuffer[i].Command_Length) == 0)
		{
			ReturnEnum = CommandBuffer[i].Enum;
			break;
		}
	}
	return ReturnEnum;
}
