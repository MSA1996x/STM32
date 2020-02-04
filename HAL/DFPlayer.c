/*
 * DFPlayer.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */

#include "HAL/HAL_H/DFPlayer.h"


void PDFPlayer_Init(void){
	/*Configure UART*/
	USART2_Init_Adv(9600, 2, U_TX_EN, U_RX_EN);
	/*Reset*/
	PDFPlayer_Send(0x0C01, 0x0000);
}

void PDFPlayer_Set_Vol(char Vol){
	/*Set Volume*/
	PDFPlayer_Send(0x0601, Vol > 30 ? 30 : Vol);
}


void PDFPlayer_Send(uint16_t CMD, uint16_t Pram){
	USART2_Send(START_BYTE);
	USART2_Send(VER_BYTE);
	USART2_Send(LENGTH_BYTE);
	USART2_Send((CMD>>8));
	USART2_Send(CMD & 0xFF);
	USART2_Send(Pram>>8);
	USART2_Send(Pram & 0xFF);
	uint16_t CheckSum = PDFPlayer_Calc_CheckSum(CMD, Pram);
	USART2_Send(CheckSum>>8);
	USART2_Send(CheckSum & 0xFF);
	USART2_Send(END_BYTE);
}

void PDFPlayer_Play(unsigned char Floder, unsigned char File){
	PDFPlayer_Send(0x0F01, (Floder<<8) | File);
}

uint16_t PDFPlayer_Calc_CheckSum(uint16_t CMD, uint16_t Pram){
	return -(VER_BYTE + LENGTH_BYTE + (CMD>>8) + (CMD & 0xFF) + (Pram>>8) + (Pram & 0xFF));
}
