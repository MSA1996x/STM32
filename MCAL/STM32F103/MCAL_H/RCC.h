/*
 * RCC.h
 *
 *  Created on: Dec 14, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_RCC_H_
#define HEADERS_RCC_H_

#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>

#define RMVF BITBAND_PERI(RCC_BASE + RCC_CSR_OFFSET, 24)

#define MCO0 BITBAND_PERI(RCC_BASE + RCC_CFGR_OFFSET, 24)
#define MCO1 BITBAND_PERI(RCC_BASE + RCC_CFGR_OFFSET, 25)
#define MCO2 BITBAND_PERI(RCC_BASE + RCC_CFGR_OFFSET, 26)


#define RCC_CSR 	(*(volatile unsigned int *)(RCC_BASE + RCC_CSR_OFFSET))

#define RST_LPWRSTF		32
#define RST_WWDGRSTF	16
#define RST_IWDGRSTF	8
#define RST_SFTRSTF		4
#define RST_PORRSTF		2
#define RST_PINRSTF		1

#define MCO_NO_CLOCK	0
#define MCO_SYSCLK		4
#define MCO_HSI			5
#define MCO_HSE			6
#define MCO_PLL			7




void SW_Reset(void);
char Reset_Source(void);
void Reset_Soucre_Clear(void);
void RCC_Clock_Out(char MCO);

#endif /* HEADERS_RCC_H_ */
