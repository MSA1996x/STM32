/*
 * LIN.h
 *
 *  Created on: Dec 13, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_LIN_H_
#define HEADERS_LIN_H_

#include <MCAL/STM32F103/MCAL_H/USART1.h>

#define CHECKSUM_CLASSIC	1
#define CHECKSUM_ENHANCED	2

void USART1_Send_Break(void);
void USART1_Send_Sync(void);
char Add_PID_Parity(char PID);
void USART1_Send_PID(char PID);
void USART1_Send_Data(char *Data);
void USART1_Send_CheckSum1(char *Data);
void USART1_Send_CheckSum2(char *Data, char PID);
void USART1_Send_LIN_Frame(char PID, char *Data, char CheckSum);


#endif /* HEADERS_LIN_H_ */
