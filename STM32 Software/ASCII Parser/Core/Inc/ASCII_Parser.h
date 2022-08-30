/*
 * ASCII_Parser.h
 *
 *  Created on: 30 Aug 2022
 *      Author: Tom Fry
 */

#ifndef INC_ASCII_PARSER_H_
#define INC_ASCII_PARSER_H_

extern uint16_t HeadRxBufferHS;						// Head of the Rx buffer
extern uint16_t TailRxBufferHS;						// Tail of the Rx buffer

/*			Exported Functions			*/
void Increment_Head (uint32_t *Length);

#endif /* INC_ASCII_PARSER_H_ */
