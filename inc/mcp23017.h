/*
 * mcp23017.h
 * 02-04-2019 - First implementation
 */

#ifndef _MCP_23017_H_
#define _MCP_23017_H_

#include "stdint.h"
// address registers

typedef enum
{
	ioconBank_0 	= 0,
	ioconBank_1 	= 1u,
	ioconBank_max 	= 2u
}t_iocon_bank;

typedef union
{

	struct
	{
		uint8_t bank 	:1;
		uint8_t mirror 	:1;
		uint8_t seqp 	:1;
		uint8_t disslw 	:1;
		uint8_t haen 	:1;
		uint8_t odr 	:1;
		uint8_t intpol 	:1;
		uint8_t nu 		:1;
	}iocon_bit;
	uint8_t ioco_byte;
}t_iocon;

/*
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0472j/chr1360774870320.html
Bitfields are allocated so that the first field specified occupies the lowest-addressed bits of the word, depending on configuration:

Little-endian

    Lowest addressed means least significant.
Big-endian

    Lowest addressed means most significant.
*/

typedef union
{
  struct
  {
	  uint8_t bit0 : 1;
	  uint8_t bit1 : 1;
	  uint8_t bit2 : 1;
	  uint8_t bit3 : 1;
	  uint8_t bit4 : 1;
	  uint8_t bit5 : 1;
	  uint8_t bit6 : 1;
	  uint8_t bit7 : 1;
  }bit;
  uint8_t byte;
}t_byte;

extern int8_t Mcp_setInit(void);
extern void Mcp_writeToOutputA(t_byte valueToWrite);
extern void Mcp_writeToOutputB(t_byte valueToWrite);
extern void Mcp_writeToOutput_both(t_byte* valueToWrite);

#endif
