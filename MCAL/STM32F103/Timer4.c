/*
 * Timer4.c
 *
 *  Created on: Dec 26, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/Timer4.h>


void TMR4_Conifg(unsigned int PSC, unsigned int ARR, char TMR_MMS){
	/*Enable Clocks For TMR4*/
	TMR4_CLOCK_ENABLE = 1;
	/*Set The Prescaler Value*/
	TMR4_PSC_REG = PSC - 1;
	/*Set The Auto-Reload Value*/
	TMR4_ARR_REG = ARR;


	/*Select Master Mode*/
	TMR4_CR2_MMS0 = (TMR_MMS - _TMR_MMS_OFFSET) & 0x01;
	TMR4_CR2_MMS1 = ((TMR_MMS - _TMR_MMS_OFFSET)>>1) & 0x01;
	TMR4_CR2_MMS2 = (TMR_MMS - _TMR_MMS_OFFSET)>>2;
}

void TMR4_Config_CC4(unsigned int CCR,char TMR_OC4M, char TMR_CC4P){
	/*Configure capture/compare register*/
	TMR4_CCR4_REG = CCR;

	/*Configure Output Compare 4 Mode*/
	TMR4_CCMR2_OC4M_0 = (TMR_OC4M - _TMR_OC4M_OFFSET) & 0x01;
	TMR4_CCMR2_OC4M_1 = ((TMR_OC4M - _TMR_OC4M_OFFSET)>>1) & 0x01;
	TMR4_CCMR2_OC4M_2 = (TMR_OC4M - _TMR_OC4M_OFFSET)>>2;

	/*Configure Capture/Compare 4 Output Polarity*/
	TMR4_CCER_CC4P = TMR_CC4P - _TMR_CC4P_OFFSET;
}

inline void TMR4_Start(){
	/*Start TMR4*/
	TMR4_CR1_CEN = 1;
}

void TMR4_Stop(){
	/*Stop TMR4*/
	TMR4_CR1_CEN = 0;
}

inline unsigned int TMR4_Val(){
	return TMR4_CNT_REG;
}


