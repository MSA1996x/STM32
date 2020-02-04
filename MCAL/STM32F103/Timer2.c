/*
 * Timer2.c
 *
 *  Created on: Dec 20, 2019
 *      Author: Mohammed Samir
 */

#include <MCAL/STM32F103/MCAL_H/Timer2.h>

void TMR2_Conifg(unsigned int PSC){
	TMR2_CLOCK_ENABLE = 1;
	TMR2_PSC = PSC - 1;
	TMR2_ARR = 0xFFFF;
}

inline void TMR2_Start(){
	TMR2_CR1_CEN = 1;
}

inline void TMR2_Stop(){
	TMR2_CR1_CEN = 0;
}

inline unsigned int TMR2_Val(){
	return TMR2_CNT;
}

inline void TMR2_Val_Reset(){
	TMR2_CNT = 0;
}
