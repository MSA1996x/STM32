/*
 * CRC.h
 *
 *  Created on: Jan 22, 2020
 *      Author: Mohammed Samir
 */

#ifndef MCAL_STM32F103_MCAL_H_CRC_H_
#define MCAL_STM32F103_MCAL_H_CRC_H_


/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/


/*<Bit-Band Pointers>*/
#define CRC_CLOCK_ENABLE  		BITBAND_PERI(RCC_BASE + RCC_AHBENR_OFFSET, 6)

#define CRC_CR_RESET_BIT  		BITBAND_PERI(CRC_BASE + CRC_CR_OFFSET, 0)
/*<Bit-Band Pointers>*/



/*<Registers Pointers>*/
#define CRC_DR_REG	 	(*(volatile unsigned int *)(CRC_BASE + CRC_DR_OFFSET))
#define CRC_IDR_REG	 	(*(volatile unsigned char *)(CRC_BASE + CRC_IDR_OFFSET))
/*</Registers Pointers>*/



/*<Functions>*/
void CRC_Init();
uint32_t CRC32_Calc_HW(uint32_t *Data, unsigned char aSize);
/*<Functions>*/
#endif /* MCAL_STM32F103_MCAL_H_CRC_H_ */
