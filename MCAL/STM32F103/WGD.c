/*
 * WGD.c
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohammed Samir
 */


#include "MCAL/STM32F103/MCAL_H/WDG.h"


void IWDG_Init(char IWDG_PR, uint16_t Reload_Value, char IWDG_DBGMCU){
	/*Enable Access To IWDG_PR AND IWDG_RLR Registers*/
	IWDG_KR_REG = IWDG_KR_ACCESS_KEY;

	while(IWDG_SR_PVU_BIT);
	/*Set Prescaler Value*/
	IWDG_PR_REG = IWDG_PR;

	while(IWDG_SR_RVU_BIT);
	/*Set Reload Value*/
	IWDG_RLR_REG = Reload_Value;

	/*Start/Stop IWDG During Debugging*/
	WWDG_DBGMCU_CR_REG = (WWDG_DBGMCU_CR_REG & (~(IWDG_DBGMCU<<8))) | IWDG_DBGMCU<<8;
}

void IWDG_Start(void){
	IWDG_KR_REG = IWDG_KR_START_KEY;
}

void IWDG_Refresh(void){
	IWDG_KR_REG = IWDG_KR_RELOAD_KEY;
}


char Counter_Value_BK;
void WWDG_Init(char Window_Value, char Counter_Value, char WWDG_WDGTB, char WWDG_DBGMCU){
	WWDG_CLOCK_ENABLE_BIT = 1;
	/*
	 * APB1 Clock = 36MHz
	 * WWDG_t = PCLK1_t * 4096 * 2 ^ WDGTB[1:0] X (T[5:0] + 1)
	 * Let WDGTB[1:0] = 3
	 * WWDG_t Min at T[5:0] = 0 	==> 00.91 ms
	 * WWDG_t Max at T[5:0] = 0x3F 	==> 58.25 ms
	 *
	 * |-----RESET----|-----------Reload--------|--RESET--
	 * (1<<6) | T[5:0] .... (1<<6) | W[5:0] .... 0x40
	 */

	/*Set Prescaler AND Window Value*/
	WWDG_CFR_REG = ((WWDG_WDGTB)<<7) | (1<<6) | (Window_Value);

	/*Set Counter Value*/
	WWDG_CR_REG = (1<<6) | Counter_Value;
	/*Store Counter Value For Refresh*/
	Counter_Value_BK = Counter_Value;

	/*Start/Stop WWDG During Debugging*/
	WWDG_DBGMCU_CR_REG = (WWDG_DBGMCU_CR_REG & (~(WWDG_DBGMCU<<9))) | (WWDG_DBGMCU<<9);

}


void WWDG_Start(void){
	/*Enable WWDG*/
	WWDG_CR_WDGA_BIT = 1;
}

void WWDG_Refresh(void){
	/*Restore Counter Value*/
	WWDG_CR_REG = (WWDG_CR_REG & 0xFFFFFF80) | (1<<6) | (Counter_Value_BK);
}

char WWDG_Get_Counter(void){
	return 	WWDG_CR_REG & 0x7F;
}
