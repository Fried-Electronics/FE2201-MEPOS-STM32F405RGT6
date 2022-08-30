/*
 * ASCII_Parser.c
 *
 *  Created on: 30 Aug 2022
 *      Author: Tom Fry
 */

/*			Includes			*/
#include "main.h"
#include "ASCII_Parser.h"
#include "usbd_cdc_if.h"

/*			Private Variables			*/
extern uint8_t UserRxBufferHS[APP_RX_DATA_SIZE];	// Rx buffer from usbd_cdc_if.c
extern uint8_t UserTxBufferHS[APP_TX_DATA_SIZE];	// Tx buffer from usbd_cdc_if.c
uint16_t HeadRxBufferHS = 0;						// Head of the Rx buffer
uint16_t TailRxBufferHS = 0;						// Tail of the Rx buffer

/*			Function Prototypes			*/

/*			Function Implementations			*/
static void Increment_Head (uint32_t *Length)
{
	HeadRxBufferHS += *Length;
}

void Decrement_Tail (uint32_t *Length)
{
	TailRxBufferHS -= *Length;
}
