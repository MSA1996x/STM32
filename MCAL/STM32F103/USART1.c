/*
 * USART1.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/USART1.h>


void USART1_Init(uint32_t Baud_Rate){

	USART1_CLOCK_ENABLE = 1;

	USART1_BRR = (USART1_BUS_CLK / 16 / Baud_Rate)<<4;

	GPIO_Config(USART1_PORT, USART1_RX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	USART1_RE = 1;
	USART1_RXNEIE = 1;
	EnableNVIC(USART1_IRQn, 3);

	GPIO_Config(USART1_PORT, USART1_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
	USART1_TE = 1;

	USART1_UE = 1;
}

void USART1_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...){

	USART1_CLOCK_ENABLE = 1;
	USART1_BRR = (USART1_BUS_CLK / 16 / Baud_Rate)<<4;

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){

		case U_TX_EN:
			GPIO_Config(USART1_PORT, USART1_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
			USART1_TE = 1;
			break;
		case U_TX_DMA_EN:USART1_DMAT = 1;break;
		case U_TX_DMA_DE:USART1_DMAT = 0;break;
		case U_TX_INT_EN:
			//
			break;
		case U_TX_INT_DE:
			//
			break;
		case U_RX_EN:
			GPIO_Config(USART1_PORT, USART1_RX_PIN, MODE_INPUT, CONFIG_INPUT_PULL_UP);
			USART1_RE = 1;
			break;
		case U_RX_DMA_EN:USART1_DMAR = 1;break;
		case U_RX_DMA_DE:USART1_DMAR = 0;break;
		case U_RX_INT_EN:
			USART1_RXNEIE = 1;
			EnableNVIC(USART1_IRQn, 3);
			break;
		case U_RX_INT_DE:
			USART1_RXNEIE = 0;
			DisableNVIC(USART1_IRQn);
			break;
		case U_DATA_BITS_8: USART1_M = 0;break;
		case U_DATA_BITS_9: USART1_M = 1;break;

		case U_PARITY_NONE:USART1_PCE = 0;break;
		case U_PARITY_EVEN:
			USART1_PS = 0;
			USART1_PCE = 1;
			break;
		case U_PARITY_ODD:
			USART1_PS = 1;
			USART1_PCE = 1;
			break;
		case U_STOP_BITS_1:
			USART1_S0 = 0;
			USART1_S1 = 0;
			break;
		case U_STOP_BITS_0_5:
			USART1_S0 = 1;
			USART1_S1 = 0;
			break;
		case U_STOP_BITS_2:
			USART1_S0 = 0;
			USART1_S1 = 1;
			break;
		case U_STOP_BITS_1_5:
			USART1_S0 = 1;
			USART1_S1 = 1;
			break;

		case U_LINEN_SET: USART1_LINEN = 1;break;
		case U_LINEN_CLR: USART1_LINEN = 0;break;

		case U_LBDIE_SET: USART1_LBDIE = 1;break;
		case U_LBDIE_CLR: USART1_LBDIE = 0;break;

		case U_LBDL_10_BIT: USART1_LBDL = 0;break;
		case U_LBDL_11_BIT: USART1_LBDL = 1;break;
		}


	USART1_UE = 1;
}


char USART1_Read(void){
	return USART1_DR;
}

void USART1_Send(char data){
	USART1_DR = data;
	while(!USART1_TXE);
}

void USART1_Send_Str(char *Str){
	while(*Str != '\0')
		USART1_Send(*(Str++));
	while(!USART1_TC);
}

void USART1_Send_Ln(){
	USART1_Send_Str("\r\n");
}
