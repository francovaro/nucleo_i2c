/*
 * timer.h
 *
 *  Created on: 04 apr 2017
 *      Author: 310262183
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx_tim.h"

volatile uint8_t tim_set;

extern void TIM2_Configuration(void);
extern void TIM5_Configuration(void);

#endif /* TIMER_H_ */
