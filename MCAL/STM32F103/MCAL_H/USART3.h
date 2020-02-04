/*
 * USART3.h
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_USART3_H_
#define HEADERS_USART3_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
#include <MCAL/STM32F103/MCAL_H/GPIO.h>
#include <MCAL/STM32F103/MCAL_H/EXTI.h>
#include <stdarg.h>
/*</Includes>*/


/*<Definitions>*/
#define USART3_BUS_CLK	 	36000000
#define USART3_PORT			GPIOB
#define USART3_TX_PIN	 	10
#define USART3_RX_PIN		11
/*</Definitions>*/


/*<Bit-Band Pointers>*/
#define USART3_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_APB1ENR_OFFSET, 18)

#define USART3_UE  		BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 13)
#define USART3_M  		BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 12)

#define USART3_PCE  	BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 10)
#define USART3_PS	  	BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 9)
#define USART3_RXNEIE  	BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 5)
#define USART3_TE  		BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 3)
#define USART3_RE	  	BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 2)
#define USART3_SPK	  	BITBAND_PERI(USART3_BASE + USART_CR1_OFFSET, 0)

#define USART3_DMAT	  	BITBAND_PERI(USART3_BASE + USART_CR3_OFFSET, 7)
#define USART3_DMAR	  	BITBAND_PERI(USART3_BASE + USART_CR3_OFFSET, 6)

#define USART3_TXE	  	BITBAND_PERI(USART3_BASE + USART_SR_OFFSET, 7)
#define USART3_TC	  	BITBAND_PERI(USART3_BASE + USART_SR_OFFSET, 6)

#define USART3_LINEN  	BITBAND_PERI(USART3_BASE + USART_CR2_OFFSET, 14)
#define USART3_S1	  	BITBAND_PERI(USART3_BASE + USART_CR2_OFFSET, 13)
#define USART3_S0	  	BITBAND_PERI(USART3_BASE + USART_CR2_OFFSET, 12)
#define USART3_LBDIE  	BITBAND_PERI(USART3_BASE + USART_CR2_OFFSET, 6)
#define USART3_LBDL  	BITBAND_PERI(USART3_BASE + USART_CR2_OFFSET, 5)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define USART3_DR 	(*(volatile unsigned int *)(USART3_BASE + USART_DR_OFFSET))
#define USART3_BRR 	(*(volatile unsigned int *)(USART3_BASE + USART_BRR_OFFSET))
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


#define ON_USART3_REC USART3_IRQHandler


/*<Functions>*/
void USART3_Init(uint32_t Baud_Rate);
void USART3_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...);
char USART3_Read(void);
void USART3_Send(char data);
void USART3_Send_Str(char *Str);
void USART3_Send_Ln();
/*</Functions>*/


#endif /* HEADERS_USART3_H_ */
