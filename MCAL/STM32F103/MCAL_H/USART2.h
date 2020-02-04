/*
 * USART2.h
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_USART2_H_
#define HEADERS_USART2_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
#include <MCAL/STM32F103/MCAL_H/GPIO.h>
#include <MCAL/STM32F103/MCAL_H/EXTI.h>
#include <stdarg.h>
/*</Includes>*/


/*<Definitions>*/
#define USART2_BUS_CLK	 	36000000
#define USART2_PORT			GPIOA
#define USART2_TX_PIN	 	2
#define USART2_RX_PIN		3
/*</Definitions>*/


/*<Bit-Band Pointers>*/
#define USART2_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_APB1ENR_OFFSET, 17)

#define USART2_UE  		BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 13)
#define USART2_M  		BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 12)

#define USART2_PCE  	BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 10)
#define USART2_PS	  	BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 9)
#define USART2_RXNEIE  	BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 5)
#define USART2_TE  		BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 3)
#define USART2_RE	  	BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 2)
#define USART2_SPK	  	BITBAND_PERI(USART2_BASE + USART_CR1_OFFSET, 0)

#define USART2_DMAT	  	BITBAND_PERI(USART2_BASE + USART_CR3_OFFSET, 7)
#define USART2_DMAR	  	BITBAND_PERI(USART2_BASE + USART_CR3_OFFSET, 6)

#define USART2_TXE	  	BITBAND_PERI(USART2_BASE + USART_SR_OFFSET, 7)
#define USART2_TC	  	BITBAND_PERI(USART2_BASE + USART_SR_OFFSET, 6)

#define USART2_LINEN  	BITBAND_PERI(USART2_BASE + USART_CR2_OFFSET, 14)
#define USART2_S1	  	BITBAND_PERI(USART2_BASE + USART_CR2_OFFSET, 13)
#define USART2_S0	  	BITBAND_PERI(USART2_BASE + USART_CR2_OFFSET, 12)
#define USART2_LBDIE  	BITBAND_PERI(USART2_BASE + USART_CR2_OFFSET, 6)
#define USART2_LBDL  	BITBAND_PERI(USART2_BASE + USART_CR2_OFFSET, 5)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define USART2_DR 	(*(volatile unsigned int *)(USART2_BASE + USART_DR_OFFSET))
#define USART2_BRR 	(*(volatile unsigned int *)(USART2_BASE + USART_BRR_OFFSET))
/*</Registers Pointers>*/


/*<Functions' Parameters>*/
#define U_TX_EN				0
#define U_RX_EN				1

#define U_TX_DE				2
#define U_RX_DE				3

#define U_TX_DMA_EN			4
#define U_RX_DMA_EN			5

#define U_TX_DMA_DE			6
#define U_RX_DMA_DE			7

#define U_TX_INT_EN			8
#define U_RX_INT_EN			9

#define U_TX_INT_DE			10
#define U_RX_INT_DE			11


#define U_PARITY_NONE		12
#define U_PARITY_ODD		13
#define U_PARITY_EVEN		14

#define U_DATA_BITS_8		0 + 15
#define U_DATA_BITS_9		1 + 15

#define U_STOP_BITS_1		0 + 17
#define U_STOP_BITS_0_5		1 + 17
#define U_STOP_BITS_2		2 + 17
#define U_STOP_BITS_1_5		3 + 17

#define U_LINEN_SET			21
#define U_LINEN_CLR			22
#define U_LBDIE_SET			23
#define U_LBDIE_CLR			24
#define	U_LBDL_10_BIT		25
#define	U_LBDL_11_BIT		26
/*<Functions' Parameters>*/


#define ON_USART2_REC USART2_IRQHandler


/*<Functions>*/
void USART2_Init(uint32_t Baud_Rate);
void USART2_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...);
char USART2_Read(void);
void USART2_Send(char data);
void USART2_Send_Str(char *Str);
void USART2_Send_Ln();
/*</Functions>*/


#endif /* HEADERS_USART2_H_ */
