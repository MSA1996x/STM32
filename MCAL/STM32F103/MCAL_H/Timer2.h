/*
 * Timer2.h
 *
 *  Created on: Dec 20, 2019
 *      Author: Mohammed Samir
 */

#ifndef SOURCES_TIMER2_H_
#define SOURCES_TIMER2_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/


/*<Bit-Band Pointers>*/
#define TMR2_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_APB1ENR_OFFSET, 0)

#define TMR2_CR1_CEN		BITBAND_PERI(TMR2_BASE + TIMx_CR1, 0)
#define TIM2_DIER_UIE		BITBAND_PERI(TMR2_BASE + TIMx_DIER, 0)
#define TIM2_SR_UIF			BITBAND_PERI(TMR2_BASE + TIMx_SR, 0)

#define TIM2_CR2_MMS2		BITBAND_PERI(TMR2_BASE + TIMx_CR2, 6)
#define TIM2_CR2_MMS1		BITBAND_PERI(TMR2_BASE + TIMx_CR2, 5)
#define TIM2_CR2_MMS0		BITBAND_PERI(TMR2_BASE + TIMx_CR2, 4)

#define TIM2_EGR_UG			BITBAND_PERI(TMR2_BASE + TIMx_EGR, 0)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define TMR2_PSC 	(*(volatile unsigned int *)(TMR2_BASE + TIMx_PSC))
#define TMR2_CNT 	(*(volatile unsigned int *)(TMR2_BASE + TIMx_CNT))
#define TMR2_ARR 	(*(volatile unsigned int *)(TMR2_BASE + TIMx_ARR))
/*</Registers Pointers>*/



/*<Functions>*/
void TMR2_Conifg(unsigned int PSC);
void TMR2_Start();
void TMR2_Stop();
unsigned int TMR2_Val();
void TMR2_Val_Reset();
/*</Functions>*/


#endif /* SOURCES_TIMER2_H_ */
