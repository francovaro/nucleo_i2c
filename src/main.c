/**
  ******************************************************************************
  * @file    main.c
  * @author  Francesco
  * @version V1.0
  * @date    26-March-2019
  * @brief   Default main function.
  ******************************************************************************
*/


/*
 * Ideas:
 * - display number 0-9 the "actual value" of a sensor -> to start ADC value of a potentiometer
 * - display the bar level [0 min 8 max!] of a sensor ->
 *
 */

/*
 * To display number:
 * - need a binary map for each character
 */

/*
 * To display the bar level:
 * -
 */

/*
 * 24/06
 * I2c with DMA not a good idea for now.
 * Try to write both A&B in one shot
 */

#include "stm32f4xx.h"
#include "mcp23017.h"
#include "led_matrix.h"

#include "test.h"
#include "uart.h"
#include "timer.h"
#include "adc.h"

#define ON  0
#define OFF 1

extern volatile uint32_t i2c_timeOut;
volatile uint8_t changeOutput;

extern volatile uint8_t tim_set;


const t_byte control_onoff[2u] = {
		{.byte = 0x00},
		{.byte = 0xFF}
	};

static void _handleChaneData(e_LedMatrix_number* newVal);

int main(void)
{
	uint8_t adc_val = 0;
	static e_LedMatrix_number numberDisplayed = eLedMatrix_zero;
	int8_t retVal = 0;
	t_byte toWrite[2u] = {0, 0};
	changeOutput = 0;

	setSysTick (1000);	// ?

	//RCC_PCLK2Config(RCC_HCLK_Div2);             // ?

	initLed();	// Init GPIO for the LED on the board
	retVal = Mcp_setInit();	// Init I2C1 and write first config
	//
	if (retVal == 0)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_5,SET);
	}
	else
	{
		return -1;	// if something went wrong, exit...
	}

	TIM2_Configuration();		// Init of TIM2 as count timer+interrupt
	TIM3_Configuration();
	//ADC_fv_Init(eADC_DMA);		// init ADC1+DMA+DMA interrupt

	LedMatrix_writeNumber(eLedMatrix_zero);

	while(1)
	{
		if (tim_set == 1)	// TIM2 event
		{
			toWrite[1] = LedMatrix_getColumn();
			toWrite[0] = control_onoff[OFF]; //LedMatrix_getValue();
			//Mcp_writeToOutput_both(toWrite);

			//Mcp_writeToOutputA(control_onoff[OFF]);	// TURN OFF
			//Mcp_writeToOutputB(toWrite[1]);

			Mcp_writeToOutput_both(toWrite);

			toWrite[0] = LedMatrix_getValue();
			Mcp_writeToOutputA(toWrite[0]);

			LedMatrix_advanceColumn();

			tim_set = 0;
		}

		if (DMA_HT_event == SET)	// Half Transfer Occurred
		{
			DMA_HT_event = RESET;
		}

		if (DMA_FT_event == SET)	// Full Transfer Occurred
		{
			DMA_FT_event = RESET;
			adc_val = ADC_fv_Return_Avg();
		}

		if (changeOutput == 1)
		{
			_handleChaneData(&numberDisplayed);

			GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
			changeOutput = 0;
		}
	}
}

void SysTick_Handler()
{
	static uint16_t count = 0;
	count++;

	if(count == 250)
	{

		changeOutput = 1;
		count = 0;
	}

	if (i2c_timeOut != 0)
	{
		i2c_timeOut--;
	}

}

void _handleChaneData(e_LedMatrix_number* newVal)
{
	*newVal = ((uint8_t)(*newVal+1))%(uint8_t)eLedMatrix_max;
	LedMatrix_writeNumber(*newVal);
}
