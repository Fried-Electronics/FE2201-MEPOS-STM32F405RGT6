/*
 * ASCII_Parser.h
 *
 *  Created on: 30 Aug 2022
 *      Author: Tom Fry
 */

#ifndef INC_ASCII_PARSER_H_
#define INC_ASCII_PARSER_H_

/*			Defines			*/
#define MAX_NUMBER_OF_COMMANDS 64
#define COMMAND_MAX_LENGTH 64

/*			Types			*/
typedef struct __CommandTypeDef
{
	char Command_String[COMMAND_MAX_LENGTH];
	uint16_t Command_Length;
	uint16_t Enum;
} CommandTypeDef;

/*			Exported Variables			*/
extern uint16_t HeadRxBufferHS;	// Head of the Rx buffer
extern uint16_t TailRxBufferHS;	// Tail of the Rx buffer

/*			Exported Functions			*/
void Increment_Head (uint32_t *Length);

#endif /* INC_ASCII_PARSER_H_ */
