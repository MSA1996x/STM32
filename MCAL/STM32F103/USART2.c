/*
 * USART2.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/USART2.h>


void USART2_Init(uint32_t Baud_Rate){
	/*Enable USART2 Clock*/
	USART2_CLOCK_ENABLE = 1;
	/*Set Baud Rate*/
	USART2_Chage_BR(Baud_Rate);

	GPIO_Config(USART2_PORT, USART2_RX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	/*Enable Reception*/
	USART2_CR1_RE = 1;

	USART2_CR1_RXNEIE = 1;
	EnableNVIC(USART2_IRQn, 3);

	GPIO_Config(USART2_PORT, USART2_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
	/*Enable Transmission*/
	USART2_CR1_TE = 1;

	/*Enable USART*/
	USART2_CR1_UE = 1;
}

void USART2_Init_OneWire(uint32_t Baud_Rate){
	/*Enable USART2 Clock*/
	USART2_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART2_Chage_BR(Baud_Rate);

	/*Configure TX Pin as OUTPUT Open Drain*/
	GPIO_Config(USART2_PORT, USART2_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);

	/*Select Single-Wire Half-Duplex Mode*/
	USART2_CR3_HDSEL = 1;

	/*Enable Reception*/
	USART2_CR1_RE = 1;
	/*Enable Transmission*/
	USART2_CR1_TE = 1;
	/*Enable USART*/
	USART2_CR1_UE = 1;
}

void USART2_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...){
	/*Enable USART2 Clock*/
	USART2_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART2_Chage_BR(Baud_Rate);

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){

		case U_TX_EN:
			GPIO_Config(USART2_PORT, USART2_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
			USART2_CR1_TE = 1;
			break;
		case U_TX_DMA_EN:USART2_CR3_DMAT = 1;break;
		case U_TX_DMA_DE:USART2_CR3_DMAT = 0;break;
		case U_TX_INT_EN:
			//
			break;
		case U_TX_INT_DE:
			//
			break;
		case U_RX_EN:
			GPIO_Config(USART2_PORT, USART2_RX_PIN, MODE_INPUT, CONFIG_INPUT_PULL_UP);
			USART2_CR1_RE = 1;
			break;
		case U_RX_DMA_EN:USART2_CR3_DMAR = 1;break;
		case U_RX_DMA_DE:USART2_CR3_DMAR = 0;break;
		case U_RX_INT_EN:
			USART2_CR1_RXNEIE = 1;
			EnableNVIC(USART2_IRQn, 3);
			break;
		case U_RX_INT_DE:
			USART2_CR1_RXNEIE = 0;
			DisableNVIC(USART2_IRQn);
			break;
		case U_DATA_BITS_8: USART2_CR1_M = 0;break;
		case U_DATA_BITS_9: USART2_CR1_M = 1;break;

		case U_PARITY_NONE:USART2_CR1_PCE = 0;break;
		case U_PARITY_EVEN:
			USART2_CR1_PS = 0;
			USART2_CR1_PCE = 1;
			break;
		case U_PARITY_ODD:
			USART2_CR1_PS = 1;
			USART2_CR1_PCE = 1;
			break;
		case U_STOP_BITS_1:
			USART2_CR2_S0 = 0;
			USART2_CR2_S1 = 0;
			break;
		case U_STOP_BITS_0_5:
			USART2_CR2_S0 = 1;
			USART2_CR2_S1 = 0;
			break;
		case U_STOP_BITS_2:
			USART2_CR2_S0 = 0;
			USART2_CR2_S1 = 1;
			break;
		case U_STOP_BITS_1_5:
			USART2_CR2_S0 = 1;
			USART2_CR2_S1 = 1;
			break;

		case U_LINEN_SET: USART2_CR2_LINEN = 1;break;
		case U_LINEN_CLR: USART2_CR2_LINEN = 0;break;

		case U_LBDIE_SET: USART2_CR2_LBDIE = 1;break;
		case U_LBDIE_CLR: USART2_CR2_LBDIE = 0;break;

		case U_LBDL_10_BIT: USART2_CR2_LBDL = 0;break;
		case U_LBDL_11_BIT: USART2_CR2_LBDL = 1;break;
		}


	USART2_CR1_UE = 1;
}

void USART2_Chage_BR(uint32_t Baud_Rate){
	/*Wait For End of Transmission*/
	while(!USART2_SR_TC);
	/*Backup USART's State*/
	char Temp = USART2_CR1_UE;
	/*Disable USART*/
	USART2_CR1_UE = 0;

	/*Calculate BRR*/
	float BRR = USART2_BUS_CLK / 16 / Baud_Rate;
	/*Calculate Fraction*/
	float Fraction = (BRR - (int)BRR) * 16 ;
	/*Set Mantissa*/
	USART2_BRR = ((int)(BRR + (Fraction >= 15.5 ? 1 : 0)))<<4;
	/*Set Fraction*/
	USART2_BRR |= Fraction >= 15.5 ? 0 :
			(int)Fraction + (Fraction - (int)Fraction >= 0.5 ? 1 : 0);

	/*Return USART To its First State*/
	USART2_CR1_UE = Temp;
}

char USART2_Read(void){
	/*Return The Received Data*/
	return USART2_DR;
}

char USART2_Check_Errors(void){
	/*Check Error Flags*/
	/*
	 *
	*/
	return 0;
}

void USART2_Send(char data){
	USART2_DR = data;
	while(!USART2_SR_TXE);
}

void USART2_Send_Str(char *Str){
	while(*Str != '\0')
		USART2_Send(*(Str++));
	while(!USART2_SR_TC);
}

void USART2_Send_Ln(){
	USART2_Send_Str("\r\n");
}
