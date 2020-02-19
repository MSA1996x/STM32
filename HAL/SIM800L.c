/*
 * SIM800L.c
 *
 *  Created on: Feb 19, 2020
 *      Author: Mohammed Samir
 */


#include "HAL/HAL_H/SIM800L.h"


void SIM800L_Init(void){
	/*Configure UART*/
	USART2_Init_Adv(115200, 2, U_TX_EN, U_RX_EN);

	/*Clear Previous CMD*/
	SIM800L_CMD("");
	/*Stop Echo*/
	SIM800L_CMD("ATE0");
}

void SIM800L_CMD(char *CMD){
	/*Send CMD*/
	USART2_Send_Str(CMD);
	/*Send New Line*/
	USART2_Send_Ln();
}

void SIM800L_Call(char *Number){
	USART2_Send_Str("ATD");
	USART2_Send_Str(Number);
	USART2_Send(';');
	USART2_Send_Ln();
}
