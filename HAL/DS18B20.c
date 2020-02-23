/*
 * DS18B20.c
 *
 *  Created on: Feb 22, 2020
 *      Author: Mohammed Samir
 */


#include "HAL/HAL_H/DS18B20.h"

void DS18B20_Init(void){
	/*Configure USART in OneWire Mode*/
	USART1_Init_OneWire(9600);
}

char DS18B20_SendRest(void){
	/*Change Baud Rate To 9600*/
	USART1_Chage_BR(9600);
	/*Send Reset CMD*/
	USART1_Send(DS18B20_RESET_CMD);
	/*Wait For End of Transmission*/
	while(!USART1_SR_TC);
	/*Wait For Data Reception*/
	while(!USART1_SR_RXNE);
	char DataRec = USART1_Read();
	/*Change Baud Rate To 115200*/
	USART1_Chage_BR(115200);
	/*Check if The Sensor is Found*/
	return DataRec != DS18B20_RESET_CMD;
}

void DS18B20_SendCMD(char CMD){
	for(int i = 0; i < 8; i++){
		if(CMD & 0x01)
			USART1_Send(0xFF);
		else
			USART1_Send(0x00);
		CMD = CMD>>1;
	}
	/*Wait For End of Transmission*/
	while(!USART1_SR_TC);
}

unsigned int DS18B20_Receive(void){
	/*For Data Storing*/
	unsigned int Data = 0;
	for(int i = 0; i < 16; i++){
		USART1_Send(0xFF);
		/*Wait For End of Transmission*/
		while(!USART1_SR_TC);
		/*Wait For Data Reception*/
		while(!USART1_SR_RXNE);
		/*Check Bit*/
		if(USART1_Read() == 0xFF)
			Data |= 0x8000;
		Data = Data>>1;
	}
	/*Return The Received Data*/
	return Data;
}

float DS18B20_Read_Temp(void){
	/*Address All Devices*/
	DS18B20_SendCMD(DS18B20_SKIP_ROM);
	/*Start Temperature Conversion*/
	DS18B20_SendCMD(DS18B20_CONVERT_CMD);
	/*Send Reset CMD*/
	DS18B20_SendRest();
	/*Address All Devices*/
	DS18B20_SendCMD(DS18B20_SKIP_ROM);
	/*Read Memory CMD*/
	DS18B20_SendCMD(DS18B20_SCRATCH_READ);
	/*Receive Temperature*/
	unsigned int Data = DS18B20_Receive();
	/*Calculate The Temperature*/
	float Temp = (float)(Data>>4);
	/*Add The Fraction*/
	Temp += ((Data & 0x01) != 0 ? 0.0625 : 0) +
			((Data & 0x02) != 0 ? 0.125 : 0) +
			((Data & 0x04) != 0 ? 0.25 : 0) +
			((Data & 0x08) != 0 ? 0.5 : 0);
	/*Return The Calculated Temperature*/
	return Temp;
}
