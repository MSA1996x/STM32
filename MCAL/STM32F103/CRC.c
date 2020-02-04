/*
 * CRC.c
 *
 *  Created on: Jan 22, 2020
 *      Author: Mohammed Samir
 */


#include "MCAL/STM32F103/MCAL_H/CRC.h"


void CRC_Init(){
	/*Enable CRC Clock*/
	CRC_CLOCK_ENABLE = 1;
}

uint32_t CRC32_Calc_HW(uint32_t *Data, unsigned char aSize){
	/*Reset CRC Value*/
	CRC_CR_RESET_BIT = 1;

	/*Calculate CRC Value*/
	for(unsigned char i = 0; i < aSize; i++){
		CRC_DR_REG = *(Data++);
	}

	/*Return CRC Value*/
	return CRC_DR_REG;
}
