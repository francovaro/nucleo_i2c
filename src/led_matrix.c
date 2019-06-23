/*
 * led_matrix.c
 *
 *  Created on: 17 apr 2019
 *      Author: franc
 */

#include "led_matrix.h"

static t_column actualColumn = e_column_1;
static t_byte led_matrix[8u] = {0};
/*
const t_byte matrix_zero[8u] = {
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00}
	};

const t_byte matrix_one[8u] = {
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00}
	};

const t_byte matrix_test[8u] = {
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00},
		{.byte = 0x00}
	};
*/
const t_byte column_matrix[8u] = {
		{.byte = 0x01},
		{.byte = 0x02},
		{.byte = 0x04},
		{.byte = 0x08},
		{.byte = 0x10},
		{.byte = 0x20},
		{.byte = 0x40},
		{.byte = 0x80}
	};

void LedMatrix_setColumn(t_column column)
{
	actualColumn = column;
}

void LedMatrix_advanceColumn(void)
{
	actualColumn++;

	if( actualColumn >= e_column_max)
	{
		actualColumn = e_column_1;
	}
}

void LedMatrix_setRow(t_column column, uint8_t row)
{
	if (column < e_column_max)
	{
		led_matrix[(uint8_t)column].byte = row;
	}
}

t_byte LedMatrix_getColumn(void)
{
	return column_matrix[actualColumn];
}

t_byte LedMatrix_getValue(void)
{
	return led_matrix[(uint8_t)actualColumn];
}

void LedMatrix_writeNumber(e_LedMatrix_number number)
{
	switch (number)
	{
		case eLedMatrix_zero:
		{
			LedMatrix_setRow(e_column_1, 0xFF);
			LedMatrix_setRow(e_column_2, 0xC3);
			LedMatrix_setRow(e_column_3, 0xBD);
			LedMatrix_setRow(e_column_4, 0x7E);
			LedMatrix_setRow(e_column_5, 0x7E);
			LedMatrix_setRow(e_column_6, 0xBD);
			LedMatrix_setRow(e_column_7, 0xC3);
			LedMatrix_setRow(e_column_8, 0xFF);
		}
		break;
		case eLedMatrix_one:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0xff);
			LedMatrix_setRow(e_column_4, 0x00);
			LedMatrix_setRow(e_column_5, 0x00);
			LedMatrix_setRow(e_column_6, 0xfd);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_two:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xfb);
			LedMatrix_setRow(e_column_3, 0x75);
			LedMatrix_setRow(e_column_4, 0x6e);
			LedMatrix_setRow(e_column_5, 0x5e);
			LedMatrix_setRow(e_column_6, 0x39);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_three:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0x99);
			LedMatrix_setRow(e_column_4, 0x66);
			LedMatrix_setRow(e_column_5, 0x7e);
			LedMatrix_setRow(e_column_6, 0x99);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_four:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0xef);
			LedMatrix_setRow(e_column_4, 0x00);
			LedMatrix_setRow(e_column_5, 0xed);
			LedMatrix_setRow(e_column_6, 0xe3);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_five:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0xff);
			LedMatrix_setRow(e_column_4, 0x06);
			LedMatrix_setRow(e_column_5, 0x76);
			LedMatrix_setRow(e_column_6, 0x70);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_six:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0xff);
			LedMatrix_setRow(e_column_4, 0x0e);
			LedMatrix_setRow(e_column_5, 0x6e);
			LedMatrix_setRow(e_column_6, 0x00);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_seven:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0xef);
			LedMatrix_setRow(e_column_4, 0x00);
			LedMatrix_setRow(e_column_5, 0xee);
			LedMatrix_setRow(e_column_6, 0xfe);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_eight:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0x89);
			LedMatrix_setRow(e_column_4, 0x76);
			LedMatrix_setRow(e_column_5, 0x76);
			LedMatrix_setRow(e_column_6, 0x89);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_nine:
		{
			LedMatrix_setRow(e_column_1, 0xff);
			LedMatrix_setRow(e_column_2, 0xff);
			LedMatrix_setRow(e_column_3, 0x81);
			LedMatrix_setRow(e_column_4, 0x76);
			LedMatrix_setRow(e_column_5, 0x76);
			LedMatrix_setRow(e_column_6, 0xf9);
			LedMatrix_setRow(e_column_7, 0xff);
			LedMatrix_setRow(e_column_8, 0xff);
		}
		break;
		default:
		{
			LedMatrix_setRow(e_column_1, 0x00);
			LedMatrix_setRow(e_column_2, 0x01);
			LedMatrix_setRow(e_column_3, 0x03);
			LedMatrix_setRow(e_column_4, 0x07);
			LedMatrix_setRow(e_column_5, 0x0F);
			LedMatrix_setRow(e_column_6, 0x1F);
			LedMatrix_setRow(e_column_7, 0x3F);
			LedMatrix_setRow(e_column_8, 0x7F);
		}
	}
}

void LedMatrix_writeLevel(e_LedMatrix_barlevel number)
{
	switch (number)
	{
		case eLedMatrix_bar_zero:
		{
			LedMatrix_bar_setRow(e_column_1, 0xFF);
			LedMatrix_bar_setRow(e_column_2, 0xC3);
			LedMatrix_bar_setRow(e_column_3, 0xBD);
			LedMatrix_bar_setRow(e_column_4, 0x7E);
			LedMatrix_bar_setRow(e_column_5, 0x7E);
			LedMatrix_bar_setRow(e_column_6, 0xBD);
			LedMatrix_bar_setRow(e_column_7, 0xC3);
			LedMatrix_bar_setRow(e_column_8, 0xFF);
		}
		break;
		case eLedMatrix_bar_one:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0xff);
			LedMatrix_bar_setRow(e_column_4, 0x00);
			LedMatrix_bar_setRow(e_column_5, 0x00);
			LedMatrix_bar_setRow(e_column_6, 0xfd);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_two:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xfb);
			LedMatrix_bar_setRow(e_column_3, 0x75);
			LedMatrix_bar_setRow(e_column_4, 0x6e);
			LedMatrix_bar_setRow(e_column_5, 0x5e);
			LedMatrix_bar_setRow(e_column_6, 0x39);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_three:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0x99);
			LedMatrix_bar_setRow(e_column_4, 0x66);
			LedMatrix_bar_setRow(e_column_5, 0x7e);
			LedMatrix_bar_setRow(e_column_6, 0x99);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_four:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0xef);
			LedMatrix_bar_setRow(e_column_4, 0x00);
			LedMatrix_bar_setRow(e_column_5, 0xed);
			LedMatrix_bar_setRow(e_column_6, 0xe3);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_five:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0xff);
			LedMatrix_bar_setRow(e_column_4, 0x06);
			LedMatrix_bar_setRow(e_column_5, 0x76);
			LedMatrix_bar_setRow(e_column_6, 0x70);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_six:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0xff);
			LedMatrix_bar_setRow(e_column_4, 0x0e);
			LedMatrix_bar_setRow(e_column_5, 0x6e);
			LedMatrix_bar_setRow(e_column_6, 0x00);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_seven:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0xef);
			LedMatrix_bar_setRow(e_column_4, 0x00);
			LedMatrix_bar_setRow(e_column_5, 0xee);
			LedMatrix_bar_setRow(e_column_6, 0xfe);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		case eLedMatrix_bar_eight:
		{
			LedMatrix_bar_setRow(e_column_1, 0xff);
			LedMatrix_bar_setRow(e_column_2, 0xff);
			LedMatrix_bar_setRow(e_column_3, 0x89);
			LedMatrix_bar_setRow(e_column_4, 0x76);
			LedMatrix_bar_setRow(e_column_5, 0x76);
			LedMatrix_bar_setRow(e_column_6, 0x89);
			LedMatrix_bar_setRow(e_column_7, 0xff);
			LedMatrix_bar_setRow(e_column_8, 0xff);
		}
		break;
		default:
		{
			LedMatrix_bar_setRow(e_column_1, 0xAA);
			LedMatrix_bar_setRow(e_column_2, 0x55);
			LedMatrix_bar_setRow(e_column_3, 0xAA);
			LedMatrix_bar_setRow(e_column_4, 0x55);
			LedMatrix_bar_setRow(e_column_5, 0xAA);
			LedMatrix_bar_setRow(e_column_6, 0x55);
			LedMatrix_bar_setRow(e_column_7, 0xAA);
			LedMatrix_bar_setRow(e_column_8, 0x55);
		}
	}

}
