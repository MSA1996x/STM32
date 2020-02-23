/*
 * USART1.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/USART1.h>


void USART1_Init(uint32_t Baud_Rate){
	/*Enable USART1 Clock*/
	USART1_CLOCK_ENABLE = 1;
	/*Set Baud Rate*/
	USART1_Chage_BR(Baud_Rate);

	GPIO_Config(USART1_PORT, USART1_RX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	/*Enable Reception*/
	USART1_CR1_RE = 1;

	USART1_CR1_RXNEIE = 1;
	EnableNVIC(USART1_IRQn, 3);

	GPIO_Config(USART1_PORT, USART1_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
	/*Enable Transmission*/
	USART1_CR1_TE = 1;

	/*Enable USART*/
	USART1_CR1_UE = 1;
}

void USART1_Init_OneWire(uint32_t Baud_Rate){
	/*Enable USART1 Clock*/
	USART1_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART1_Chage_BR(Baud_Rate);

	/*Configure TX Pin as OUTPUT Open Drain*/
	GPIO_Config(USART1_PORT, USART1_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);

	/*Select Single-Wire Half-Duplex Mode*/
	USART1_CR3_HDSEL = 1;

	/*Enable Reception*/
	USART1_CR1_RE = 1;
	/*Enable Transmission*/
	USART1_CR1_TE = 1;
	/*Enable USART*/
	USART1_CR1_UE = 1;
}

void USART1_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...){
	/*Enable USART1 Clock*/
	USART1_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART1_Chage_BR(Baud_Rate);

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){

		case U_TX_EN:
			GPIO_Config(USART1_PORT, USART1_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
			USART1_CR1_TE = 1;
			break;
		case U_TX_DMA_EN:USART1_CR3_DMAT = 1;break;
		case U_TX_DMA_DE:USART1_CR3_DMAT = 0;break;
		case U_TX_INT_EN:
			//
			break;
		case U_TX_INT_DE:
			//
			break;
		case U_RX_EN:
			GPIO_Config(USART1_PORT, USART1_RX_PIN, MODE_INPUT, CONFIG_INPUT_PULL_UP);
			USART1_CR1_RE = 1;
			break;
		case U_RX_DMA_EN:USART1_CR3_DMAR = 1;break;
		case U_RX_DMA_DE:USART1_CR3_DMAR = 0;break;
		case U_RX_INT_EN:
			USART1_CR1_RXNEIE = 1;
			EnableNVIC(USART1_IRQn, 3);
			break;
		case U_RX_INT_DE:
			USART1_CR1_RXNEIE = 0;
			DisableNVIC(USART1_IRQn);
			break;
		case U_DATA_BITS_8: USART1_CR1_M = 0;break;
		case U_DATA_BITS_9: USART1_CR1_M = 1;break;

		case U_PARITY_NONE:USART1_CR1_PCE = 0;break;
		case U_PARITY_EVEN:
			USART1_CR1_PS = 0;
			USART1_CR1_PCE = 1;
			break;
		case U_PARITY_ODD:
			USART1_CR1_PS = 1;
			USART1_CR1_PCE = 1;
			break;
		case U_STOP_BITS_1:
			USART1_CR2_S0 = 0;
			USART1_CR2_S1 = 0;
			break;
		case U_STOP_BITS_0_5:
			USART1_CR2_S0 = 1;
			USART1_CR2_S1 = 0;
			break;
		case U_STOP_BITS_2:
			USART1_CR2_S0 = 0;
			USART1_CR2_S1 = 1;
			break;
		case U_STOP_BITS_1_5:
			USART1_CR2_S0 = 1;
			USART1_CR2_S1 = 1;
			break;

		case U_LINEN_SET: USART1_CR2_LINEN = 1;break;
		case U_LINEN_CLR: USART1_CR2_LINEN = 0;break;

		case U_LBDIE_SET: USART1_CR2_LBDIE = 1;break;
		case U_LBDIE_CLR: USART1_CR2_LBDIE = 0;break;

		case U_LBDL_10_BIT: USART1_CR2_LBDL = 0;break;
		case U_LBDL_11_BIT: USART1_CR2_LBDL = 1;break;
		}


	USART1_CR1_UE = 1;
}

void USART1_Chage_BR(uint32_t Baud_Rate){
	/*Wait For End of Transmission*/
	while(!USART1_SR_TC);
	/*Backup USART's State*/
	char Temp = USART1_CR1_UE;
	/*Disable USART*/
	USART1_CR1_UE = 0;

	/*Calculate BRR*/
	float BRR = USART1_BUS_CLK / 16 / Baud_Rate;
	/*Calculate Fraction*/
	float Fraction = (BRR - (int)BRR) * 16 ;
	/*Set Mantissa*/
	USART1_BRR = ((int)(BRR + (Fraction >= 15.5 ? 1 : 0)))<<4;
	/*Set Fraction*/
	USART1_BRR |= Fraction >= 15.5 ? 0 :
			(int)Fraction + (Fraction - (int)Fraction >= 0.5 ? 1 : 0);

	/*Return USART To its First State*/
	USART1_CR1_UE = Temp;
}

char USART1_Read(void){
	/*Return The Received Data*/
	return USART1_DR;
}

char USART1_Check_Errors(void){
	/*Check Error Flags*/
	/*
	 *
	*/
	return 0;
}

void USART1_Send(char data){
	USART1_DR = data;
	while(!USART1_SR_TXE);
}

void USART1_Send_Str(char *Str){
	while(*Str != '\0')
		USART1_Send(*(Str++));
	while(!USART1_SR_TC);
}

void USART1_Send_Ln(){
	USART1_Send_Str("\r\n");
}
