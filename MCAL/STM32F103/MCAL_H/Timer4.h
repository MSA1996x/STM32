/*
 * Timer4.h
 *
 *  Created on: Dec 26, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_TIMER4_H_
#define HEADERS_TIMER4_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/


/*<Bit-Band Pointers>*/
#define TMR4_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_APB1ENR_OFFSET, 2)


#define TMR4_CR1_OPM		BITBAND_PERI(TMR4_BASE + TIMx_CR1, 3)
#define TMR4_CR1_URS		BITBAND_PERI(TMR4_BASE + TIMx_CR1, 2)
#define TMR4_CR1_UDIS		BITBAND_PERI(TMR4_BASE + TIMx_CR1, 1)
#define TMR4_CR1_CEN		BITBAND_PERI(TMR4_BASE + TIMx_CR1, 0)

#define TMR4_CR2_MMS2		BITBAND_PERI(TMR4_BASE + TIMx_CR2, 6)
#define TMR4_CR2_MMS1		BITBAND_PERI(TMR4_BASE + TIMx_CR2, 5)
#define TMR4_CR2_MMS0		BITBAND_PERI(TMR4_BASE + TIMx_CR2, 4)

#define TMR4_DIER_TIE		BITBAND_PERI(TMR4_BASE + TIMx_DIER, 6)
#define TMR4_DIER_CC4IE		BITBAND_PERI(TMR4_BASE + TIMx_DIER, 4)
#define TMR4_DIER_UIE		BITBAND_PERI(TMR4_BASE + TIMx_DIER, 0)

#define TMR4_SR_CC4OF		BITBAND_PERI(TMR4_BASE + TIMx_SR, 12)
#define TMR4_SR_TIF			BITBAND_PERI(TMR4_BASE + TIMx_SR, 6)
#define TMR4_SR_CC4IF		BITBAND_PERI(TMR4_BASE + TIMx_SR, 4)
#define TMR4_SR_UIF			BITBAND_PERI(TMR4_BASE + TIMx_SR, 0)


#define TMR4_CCMR2_OC4CE	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 15)
#define TMR4_CCMR2_OC4M_2	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 14)
#define TMR4_CCMR2_OC4M_1	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 13)
#define TMR4_CCMR2_OC4M_0	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 12)
#define TMR4_CCMR2_OC4FE	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 10)
#define TMR4_CCMR2_CC4S_1	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 9)
#define TMR4_CCMR2_CC4S_0	BITBAND_PERI(TMR4_BASE + TIMx_CCMR2, 8)


#define TMR4_CCER_CC4P		BITBAND_PERI(TMR4_BASE + TIMx_CCER, 13)
#define TMR4_CCER_CC4E		BITBAND_PERI(TMR4_BASE + TIMx_CCER, 12)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define TMR4_CNT_REG 		(*(volatile unsigned int *)(TMR4_BASE + TIMx_CNT))
#define TMR4_PSC_REG 		(*(volatile unsigned int *)(TMR4_BASE + TIMx_PSC))
#define TMR4_ARR_REG 		(*(volatile unsigned int *)(TMR4_BASE + TIMx_ARR))
#define TMR4_CCR4_REG 		(*(volatile unsigned int *)(TMR4_BASE + TIMx_CCR4))
/*</Registers Pointers>*/



/*<Functions' Parameters>*/

/*Cases of TMR_MMS Pram*/
#define _TMR_MMS_OFFSET			0
#define TMR_MMS_RESET			(0 + _TMR_MMS_OFFSET)
#define TMR_MMS_ENABLE			(1 + _TMR_MMS_OFFSET)
#define TMR_MMS_UPDATE			(2 + _TMR_MMS_OFFSET)
#define TMR_MMS_COMP_PULSE		(3 + _TMR_MMS_OFFSET)
#define TMR_MMS_OC1REF			(4 + _TMR_MMS_OFFSET)
#define TMR_MMS_OC2REF			(5 + _TMR_MMS_OFFSET)
#define TMR_MMS_OC3REF			(6 + _TMR_MMS_OFFSET)
#define TMR_MMS_OC4REF			(7 + _TMR_MMS_OFFSET)

/*Cases of TMR_OC4M Pram*/
#define _TMR_OC4M_OFFSET		8
#define TMR_OC4M_Frozen			(0 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_OC4REF_H		(1 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_OC4REF_L		(2 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_TOGGLE			(3 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_F_OC4REF_L		(4 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_F_OC4REF_H		(5 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_PWM1			(6 + _TMR_OC4M_OFFSET)
#define TMR_OC4M_PWM2			(7 + _TMR_OC4M_OFFSET)

/*Cases of TMR_CC4P Pram*/
#define _TMR_CC4P_OFFSET		16
#define TMR_CC4P_ACTIVE_HIGH	(0 + _TMR_CC4P_OFFSET)
#define TMR_CC4P_ACTIVE_LOW		(1 + _TMR_CC4P_OFFSET)

/*</Functions' Parameters>*/


/*<Functions>*/
void TMR4_Conifg(unsigned int PSC, unsigned int ARR, char TMR_MMS);
void TMR4_Config_CC4(unsigned int CCR,char TMR_OC4M, char TMR_CC4P);
void TMR4_Start();
void TMR4_Stop();
unsigned int TMR4_Val();
/*</Functions>*/


#endif /* HEADERS_TIMER4_H_ */
