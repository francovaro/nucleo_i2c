/*
 * led_matrix.h
 * 17-04-2019 - First implementation
 */

#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_

#include <stdint.h>
#include "mcp23017.h"

/*
 * Matrix common Anode
 * Row (anode - in our point of view)
 * 1 Pin 5  ==> A1
 * 2 Pin 2  ==> A2
 * 3 Pin 7  ==> A3
 * 4 Pin 1  ==> A4
 * 5 Pin 13 ==> A5
 * 6 Pin 8  ==> A6
 * 7 Pin 11 ==> A7
 * 8 Pin 16 ==> A8
 *
 * Coulumn (kat - in our point of view)
 * 1 Pin 9  ==> B1
 * 2 Pin 10 ==> B2
 * 3 Pin 14 ==> B3
 * 4 Pin 6  ==> B4
 * 5 Pin 15 ==> B5
 * 6 Pin 4  ==> B6
 * 7 Pin 3  ==> B7
 * 8 Pin 12 ==> B8
 *
 */


typedef enum
{
	e_column_1,
	e_column_2,
	e_column_3,
	e_column_4,
	e_column_5,
	e_column_6,
	e_column_7,
	e_column_8,
	e_column_max
}t_column;

typedef enum
{
	eLedMatrix_zero,
	eLedMatrix_one,
	eLedMatrix_two,
	eLedMatrix_three,
	eLedMatrix_four,
	eLedMatrix_five,
	eLedMatrix_six,
	eLedMatrix_seven,
	eLedMatrix_eight,
	eLedMatrix_nine,
	eLedMatrix_max
} e_LedMatrix_number;

typedef enum
{
	eLedMatrix_bar_zero,
	eLedMatrix_bar_one,
	eLedMatrix_bar_two,
	eLedMatrix_bar_three,
	eLedMatrix_bar_four,
	eLedMatrix_bar_five,
	eLedMatrix_bar_six,
	eLedMatrix_bar_seven,
	eLedMatrix_bar_eight,
	eLedMatrix_bar_max
} e_LedMatrix_barlevel;

extern void LedMatrix_setColumn(t_column column);
extern void LedMatrix_advanceColumn(void);
extern void LedMatrix_setRow(t_column column, uint8_t row);

extern t_byte LedMatrix_getColumn(void);
extern t_byte LedMatrix_getValue(void);
extern void LedMatrix_writeNumber(e_LedMatrix_number number);
extern void LedMatrix_writeLevel(e_LedMatrix_barlevel number);

#endif
