#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "test.h"
/*
 *
 * -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4
 * -DSTM32F401RETx -DNUCLEO_F401RE -DDEBUG -DSTM32F401xx -DUSE_STDPERIPH_DRIVER
 * -I"C:\work\workspace_stm\nucleo-f401re_stdperiph_lib"
 * -I"C:\work\workspace_stm\nucleo-f401re_stdperiph_lib\CMSIS\core"
 * -I"C:\work\workspace_stm\nucleo-f401re_stdperiph_lib\CMSIS\device"
 * -I"C:\work\workspace_stm\nucleo-f401re_stdperiph_lib\StdPeriph_Driver\inc"
 * -I"C:\work\workspace_stm\nucleo_i2c/inc" -O0 -g3 -Wall -fmessage-length=0
 * -ffunction-sections -c
 *
 */
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
	 SysTick_Config(RCC_Clocks.SYSCLK_Frequency/timeMs); // hz/s
}
