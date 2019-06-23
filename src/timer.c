/*
 * timer.c
 *
 *  Created on: 03 mag 2019
 *      Author: franc
 */

#include "timer.h"

static void NVIC_Configuration(uint8_t channel);

void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructInit(&TIM_InitStruct);
	//84.000.000/100.000=840
	TIM_InitStruct.TIM_Prescaler = ((SystemCoreClock/2) / 100000) - 1; //42.000.000/100.000=420
																		//con prescaler 420 si ha clock: 84.000.000/420 = 200KHz
	TIM_InitStruct.TIM_Period = (10) - 1; //

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

    /* abilito il trigger esterno TIM2 TRGO  */
	//TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
    /* TIM2 enable */
	NVIC_Configuration(TIM2_IRQn);	// this one should be accessible to everywhere
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

// not working :(
void TIM5_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseStructInit(&TIM_InitStruct);

	TIM_InitStruct.TIM_Prescaler = ((SystemCoreClock/2) / 100000) - 1; 	//84.000.000/100.000=840
																		//con prescaler 840 si ha clock: 84.000.000/840=100KHz
	TIM_InitStruct.TIM_Period = (1000) - 1; //1 campione ogni centesimo di sec->100 campioni 1 sec

	TIM_InitStruct.TIM_ClockDivision = 0;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

    /* abilito il trigger esterno TIM2 TRGO  */
	//TIM_SelectOutputTrigger(TIM5, TIM_TRGOSource_Update);	// ????????
    /* TIM2 enable */

    NVIC_Configuration(TIM5_IRQn);	// this one should be accessible to everywhere
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM5, ENABLE);

}

static void NVIC_Configuration(uint8_t channel)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = channel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  NVIC_EnableIRQ(channel);
}

extern void TIM2_IRQHandler(void)
{
	// IRQ for TIM2
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		// INTERRUPT handling ...
		tim_set = 1;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	}

}

extern void TIM5_IRQHandler(void)
{
	// IRQ for TIM2
	if (TIM_GetITStatus(TIM5, TIM_IT_Update))
	{
		// INTERRUPT handling ...
		//tim_set = 1;
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

	}

}
