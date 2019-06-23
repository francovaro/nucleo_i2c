#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "test.h"

void initLed(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //Per il LED e  canale analogico
	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_5 );
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
}

void setSysTick(uint32_t timeMs)
{
	 RCC_ClocksTypeDef RCC_Clocks;
	 RCC_GetClocksFreq(&RCC_Clocks);
	 SysTick_Config(SystemCoreClock/timeMs); // hz/s
}
