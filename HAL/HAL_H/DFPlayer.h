/*
 * DFPlayer.h
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */

#ifndef HAL_HAL_H_DFPLAYER_H_
#define HAL_HAL_H_DFPLAYER_H_

#include "MCAL/STM32F103/MCAL_H/USART2.h"

#define START_BYTE	0x7E
#define VER_BYTE	0xFF
#define LENGTH_BYTE	0x06
#define END_BYTE	0xEF

void PDFPlayer_Init(void);
void PDFPlayer_Set_Vol(char Vol);
void PDFPlayer_Send(uint16_t CMD, uint16_t Pram);
void PDFPlayer_Play(unsigned char Floder, unsigned char File);
uint16_t PDFPlayer_Calc_CheckSum(uint16_t CMD, uint16_t Pram);



#endif /* HAL_HAL_H_DFPLAYER_H_ */
