/*
 * adc.h
 *
 *  Created on: 04 apr 2017
 *      Author: fv
 *  Added on: 24 06 2019
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx_adc.h"

typedef enum{
	eADC_DMA,
	eADC_INTERRUPT,
	eADC_POLLING
}t_ADC_Type;

__IO uint16_t DMA_FT_event;
__IO uint16_t DMA_HT_event;

__IO uint8_t gAdvNewVal;

__IO uint16_t gReadAdcValue;

void ADC_fv_Init(t_ADC_Type config);

uint16_t ADC_fv_Return_Avg();
uint16_t ADC_fv_Read(void);

#endif /* ADC_H_ */
