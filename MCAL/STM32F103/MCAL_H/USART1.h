/*
 * USART1.h
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_USART1_H_
#define HEADERS_USART1_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
#include <MCAL/STM32F103/MCAL_H/GPIO.h>
#include <MCAL/STM32F103/MCAL_H/EXTI.h>
#include <stdarg.h>
/*</Includes>*/


/*<Definitions>*/
#define USART1_BUS_CLK	 	72000000
#define USART1_PORT			GPIOA
#define USART1_TX_PIN	 	9
#define USART1_RX_PIN		10
/*</Definitions>*/


/*<Bit-Band Pointers>*/
#define USART1_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_APB2ENR_OFFSET, 14)

#define USART1_UE  		BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 13)
#define USART1_M  		BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 12)

#define USART1_PCE  	BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 10)
#define USART1_PS	  	BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 9)
#define USART1_RXNEIE  	BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 5)
#define USART1_TE  		BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 3)
#define USART1_RE	  	BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 2)
#define USART1_SPK	  	BITBAND_PERI(USART1_BASE + USART_CR1_OFFSET, 0)

#define USART1_DMAT	  	BITBAND_PERI(USART1_BASE + USART_CR3_OFFSET, 7)
#define USART1_DMAR	  	BITBAND_PERI(USART1_BASE + USART_CR3_OFFSET, 6)

#define USART1_TXE	  	BITBAND_PERI(USART1_BASE + USART_SR_OFFSET, 7)
#define USART1_TC	  	BITBAND_PERI(USART1_BASE + USART_SR_OFFSET, 6)

#define USART1_LINEN  	BITBAND_PERI(USART1_BASE + USART_CR2_OFFSET, 14)
#define USART1_S1	  	BITBAND_PERI(USART1_BASE + USART_CR2_OFFSET, 13)
#define USART1_S0	  	BITBAND_PERI(USART1_BASE + USART_CR2_OFFSET, 12)
#define USART1_LBDIE  	BITBAND_PERI(USART1_BASE + USART_CR2_OFFSET, 6)
#define USART1_LBDL  	BITBAND_PERI(USART1_BASE + USART_CR2_OFFSET, 5)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define USART1_DR 	(*(volatile unsigned int *)(USART1_BASE + USART_DR_OFFSET))
#define USART1_BRR 	(*(volatile unsigned int *)(USART1_BASE + USART_BRR_OFFSET))
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


#define ON_USART1_REC USART1_IRQHandler


/*<Functions>*/
void USART1_Init(uint32_t Baud_Rate);
void USART1_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...);
char USART1_Read(void);
void USART1_Send(char data);
void USART1_Send_Str(char *Str);
void USART1_Send_Ln();
/*</Functions>*/


#endif /* HEADERS_USART1_H_ */
