/*
 * adc.c
 *
 *  Created on: 24 giu 2019
 *      Author: fv
 */

#include "stm32f4xx.h"
#include "adc.h"
#include "stm32f4xx_dma.h"

#define ADC_BUFFER_SIZE	10
__IO uint16_t sampleCount;
__IO uint16_t writeIndex;
__IO uint16_t buffer[ADC_BUFFER_SIZE];

extern void DMA_Config(void);
extern void DMA_NVIC_Configuration(void);

/*
 * to enable ADC peripheral:
 * 1) enable ADC clock RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADCx, ENABLE);
 * 2) ADC pins config:
 * 		- enable clock to GPIO used
 * 		- configure GPIO in analog mode using GPIO_Init();
 * 3) configure ADC using ADC_Init();
 * 4) activate the ADC using ADC_Cmd();
 */

void DMA_Config(void)
{
	DMA_InitTypeDef       DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	/* DMA2 Stream0 channel2 configuration **************************************/
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&ADC1->DR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&buffer[0];
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ADC_BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;	// not sure
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA2_Stream0, &DMA_InitStructure);

	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC | DMA_IT_HT,  ENABLE);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	DMA_FT_event = RESET;
	DMA_HT_event = RESET;

	//while(DMA_GetCmdStatus(DMA2_Stream0)!=ENABLE);		//controllo se il DMA è a posto

	DMA_NVIC_Configuration();
}

void ADC_fv_Init(t_ADC_Type config)
{
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	sampleCount = 0;
	writeIndex = 0;

	if (config == eADC_DMA)
	{
		DMA_Config();
	}

	GPIO_StructInit(&GPIO_InitStructure);
	ADC_StructInit(&ADC_InitStructure);
	ADC_CommonStructInit(&ADC_CommonInitStructure);
	//NVIC_Init(&NVIC_InitStruct);

	/* Config PIN */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = ( GPIO_Pin_5 );
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

	/*
		ADC_CommonInitStruct : pointer to an
		ADC_CommonInitTypeDef structure that contains the
		configuration information for All ADCs peripherals.
		 	 - adc prescaler
		 	 - ADCCLK = APB2 / ADC_Prescaler
		 	 - APB"_CLK = 25 MHz
	*/

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* ADC Common Init */
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent ;					//0 ;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	/* for multi ADC !*/
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	/* ADC Init */
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;

	if(config == eADC_POLLING)
	{
		ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	}
	else	/* for interrupt and DMA enabled ! */
	{
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	}

	if ( config == eADC_POLLING)
	{
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStructure.ADC_ExternalTrigConv = DISABLE; // sure ?
	}
	else
	{
		ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO; // sure ?
	}

	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1 , &ADC_InitStructure);

	/*
	ADC_IT_EOC : End of conversion interrupt mask
	ADC_IT_AWD : Analog watchdog interrupt mask
	ADC_IT_JEOC : End of injected conversion interrupt mask
	ADC_IT_OVR : Overrun interrupt enable
	 */

	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_15Cycles);

	switch(config)
	{
		case eADC_DMA:	// enable and set DMA
		{
			/* Enable DMA request after last transfer (Single-ADC mode) */
			ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

			ADC_DMACmd(ADC1, ENABLE); /* Enable ADC1 DMA */
		}
		break;
		default:
		case eADC_POLLING:
		{
			// do nothing !
		}
		break;
		case eADC_INTERRUPT:
		{
			ADC_ITConfig(ADC1 , ADC_IT_EOC , ENABLE);
			NVIC_EnableIRQ(ADC_IRQn);     // Enable IRQ for ADC in NVIC
		}
		break;
	}

	/* Enable ADC1 */
	gAdvNewVal = 0;
	ADC_Cmd(ADC1, ENABLE);

}

void ADC_IRQHandler (void )
{
	//uint16_t zReadValue = 0;

	 if(ADC_GetITStatus(ADC1, ADC_IT_EOC) == SET)
	 {
		 gAdvNewVal = 1;
		 ADC_ClearITPendingBit(ADC1 , ADC_IT_EOC);	// ?
		 return;
	 }

	if ( (ADC1->SR & ADC_IT_EOC) == ADC_IT_EOC )
	{
		gAdvNewVal = 1;
		gReadAdcValue = ADC_GetConversionValue(ADC1);

		/*
		buffer[writeIndex] = ADC_GetConversionValue( ADC1 );
		writeIndex = (writeIndex+1)%ADC_BUFFER_SIZE;
		if(sampleCount < ADC_BUFFER_SIZE)
		{
			sampleCount++;
		}
		*/

		ADC_ClearITPendingBit(ADC1 , ADC_IT_EOC);	// ?
	}
}


uint16_t ADC_fv_Return_Avg()
{
	uint32_t sum = 0;
	uint8_t count;

	for(count = 0; count < ADC_BUFFER_SIZE ; count++)
	{
		sum += buffer[count];
	}

	return (((sum/sampleCount)*10)/255);
}

uint16_t ADC_fv_Read(void)
{
    // Start ADC conversion
    ADC_SoftwareStartConv(ADC1);

    // Wait until conversion is finish
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    return ADC_GetConversionValue(ADC1);
}

/**
  * @brief  Configures Vector Table base location.
  * @param  None
  * @retval None
  */
/*
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
*/

void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0))
	{
		DMA_HT_event = SET;
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);
	}

	/* Test on DMA Stream Transfer Complete interrupt */
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
	{
		DMA_FT_event = SET;
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
	}

}

/*ho un solo IRQ..*/
void DMA_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
