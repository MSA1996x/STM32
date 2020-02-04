/*
 * LIN.c
 *
 *  Created on: Dec 13, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/LIN.h>

void USART1_Send_LIN_Frame(char PID, char *Data, char CheckSum){
	USART1_Send_Break();
	USART1_Send_Sync();
	USART1_Send_PID(PID);
	USART1_Send_Data(Data);
	if(CheckSum == 1)
		USART1_Send_CheckSum1(Data);
	else
		USART1_Send_CheckSum2(Data, PID);
}


void USART1_Send_Break(void){
	USART1_SPK = 1;
}
void USART1_Send_Sync(void){
	USART1_Send(0x55);
}

char Add_PID_Parity(char PID){
	return PID |
			((!( ((PID>>1) & 1) ^ ((PID>>3) & 1) ^ ((PID>>4) & 1) ^ ((PID>>5) & 1)))<<7) |
			((((PID & 1) ^ ((PID>>1) & 1) ^ ((PID>>2) & 1) ^ ((PID>>4) & 1)))<<6);
}


void USART1_Send_PID(char PID){
	USART1_Send(Add_PID_Parity(PID));
}

void USART1_Send_Data(char *Data){
	USART1_Send_Str(Data);
}

void USART1_Send_CheckSum1(char *Data){
	char CheckSum = Data[0];
	for(int i = 1; Data[i] != '\0'; i++)
			CheckSum += Data[i] - (CheckSum + Data[i] > 255 ? 255 : 0);
	USART1_Send(~CheckSum);
}

void USART1_Send_CheckSum2(char *Data, char PID){
	char CheckSum = Data[0];
	for(int i = 1; Data[i] != '\0'; i++)
		CheckSum += Data[i] - (CheckSum + Data[i] > 255 ? 255 : 0);
	PID = Add_PID_Parity(PID);
	CheckSum += PID - (CheckSum + PID > 255 ? 255 : 0);
	USART1_Send(~CheckSum);
}
