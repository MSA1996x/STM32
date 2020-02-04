/*
 * RCC.c
 *
 *  Created on: Dec 14, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/RCC.h>
#include <MCAL/STM32F103/MCAL_H/GPIO.h>


void SW_Reset(void){
	__DSB();
	SCB->AIRCR  = ((0x5FA << SCB_AIRCR_VECTKEY_Pos)      |
				 (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
				 SCB_AIRCR_SYSRESETREQ_Msk);
	__DSB();
	while(1);
}

char Reset_Source(void){
	return RCC_CSR>>26;
}

void Reset_Soucre_Clear(void){
	RMVF = 1;
}

void RCC_Clock_Out(char MCO){
	GPIO_Config(GPIOA, PIN_8, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);

	MCO0 = MCO & 1;
	MCO1 = (MCO>>1) & 1;
	MCO2 = (MCO>>2);

}
