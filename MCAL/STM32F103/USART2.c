/*
 * USART2.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/USART2.h>


void USART2_Init(uint32_t Baud_Rate){

	USART2_CLOCK_ENABLE = 1;

	USART2_BRR = (USART2_BUS_CLK / 16 / Baud_Rate)<<4;

	GPIO_Config(USART2_PORT, USART2_RX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	USART2_RE = 1;
	USART2_RXNEIE = 1;
	EnableNVIC(USART2_IRQn, 3);

	GPIO_Config(USART2_PORT, USART2_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
	USART2_TE = 1;

	USART2_UE = 1;
}

void USART2_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...){

	USART2_CLOCK_ENABLE = 1;
	USART2_BRR = (USART2_BUS_CLK / 16 / Baud_Rate)<<4;

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){

		case U_TX_EN:
			GPIO_Config(USART2_PORT, USART2_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
			USART2_TE = 1;
			break;
		case U_TX_DMA_EN:USART2_DMAT = 1;break;
		case U_TX_DMA_DE:USART2_DMAT = 0;break;
		case U_TX_INT_EN:
			//
			break;
		case U_TX_INT_DE:
			//
			break;
		case U_RX_EN:
			GPIO_Config(USART2_PORT, USART2_RX_PIN, MODE_INPUT, CONFIG_INPUT_PULL_UP);
			USART2_RE = 1;
			break;
		case U_RX_DMA_EN:USART2_DMAR = 1;break;
		case U_RX_DMA_DE:USART2_DMAR = 0;break;
		case U_RX_INT_EN:
			USART2_RXNEIE = 1;
			EnableNVIC(USART2_IRQn, 3);
			break;
		case U_RX_INT_DE:
			USART2_RXNEIE = 0;
			DisableNVIC(USART2_IRQn);
			break;
		case U_DATA_BITS_8: USART2_M = 0;break;
		case U_DATA_BITS_9: USART2_M = 1;break;

		case U_PARITY_NONE:USART2_PCE = 0;break;
		case U_PARITY_EVEN:
			USART2_PS = 0;
			USART2_PCE = 1;
			break;
		case U_PARITY_ODD:
			USART2_PS = 1;
			USART2_PCE = 1;
			break;
		case U_STOP_BITS_1:
			USART2_S0 = 0;
			USART2_S1 = 0;
			break;
		case U_STOP_BITS_0_5:
			USART2_S0 = 1;
			USART2_S1 = 0;
			break;
		case U_STOP_BITS_2:
			USART2_S0 = 0;
			USART2_S1 = 1;
			break;
		case U_STOP_BITS_1_5:
			USART2_S0 = 1;
			USART2_S1 = 1;
			break;

		case U_LINEN_SET: USART2_LINEN = 1;break;
		case U_LINEN_CLR: USART2_LINEN = 0;break;

		case U_LBDIE_SET: USART2_LBDIE = 1;break;
		case U_LBDIE_CLR: USART2_LBDIE = 0;break;

		case U_LBDL_10_BIT: USART2_LBDL = 0;break;
		case U_LBDL_11_BIT: USART2_LBDL = 1;break;
		}


	USART2_UE = 1;
}


char USART2_Read(void){
	return USART2_DR;
}

void USART2_Send(char data){
	USART2_DR = data;
	while(!USART2_TXE);
}

void USART2_Send_Str(char *Str){
	while(*Str != '\0')
		USART2_Send(*(Str++));
	while(!USART2_TC);
}

void USART2_Send_Ln(){
	USART2_Send_Str("\r\n");
}
