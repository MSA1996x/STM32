/*
 * USART3.c
 *
 *  Created on: Jan 29, 2020
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/USART3.h>


void USART3_Init(uint32_t Baud_Rate){
	/*Enable USART3 Clock*/
	USART3_CLOCK_ENABLE = 1;
	/*Set Baud Rate*/
	USART3_Chage_BR(Baud_Rate);

	GPIO_Config(USART3_PORT, USART3_RX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	/*Enable Reception*/
	USART3_CR1_RE = 1;

	USART3_CR1_RXNEIE = 1;
	EnableNVIC(USART3_IRQn, 3);

	GPIO_Config(USART3_PORT, USART3_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
	/*Enable Transmission*/
	USART3_CR1_TE = 1;

	/*Enable USART*/
	USART3_CR1_UE = 1;
}

void USART3_Init_OneWire(uint32_t Baud_Rate){
	/*Enable USART3 Clock*/
	USART3_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART3_Chage_BR(Baud_Rate);

	/*Configure TX Pin as OUTPUT Open Drain*/
	GPIO_Config(USART3_PORT, USART3_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);

	/*Select Single-Wire Half-Duplex Mode*/
	USART3_CR3_HDSEL = 1;

	/*Enable Reception*/
	USART3_CR1_RE = 1;
	/*Enable Transmission*/
	USART3_CR1_TE = 1;
	/*Enable USART*/
	USART3_CR1_UE = 1;
}

void USART3_Init_Adv(uint32_t Baud_Rate, char Num_Of_Args, ...){
	/*Enable USART3 Clock*/
	USART3_CLOCK_ENABLE = 1;

	/*Set Baud Rate*/
	USART3_Chage_BR(Baud_Rate);

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){

		case U_TX_EN:
			GPIO_Config(USART3_PORT, USART3_TX_PIN, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);
			USART3_CR1_TE = 1;
			break;
		case U_TX_DMA_EN:USART3_CR3_DMAT = 1;break;
		case U_TX_DMA_DE:USART3_CR3_DMAT = 0;break;
		case U_TX_INT_EN:
			//
			break;
		case U_TX_INT_DE:
			//
			break;
		case U_RX_EN:
			GPIO_Config(USART3_PORT, USART3_RX_PIN, MODE_INPUT, CONFIG_INPUT_PULL_UP);
			USART3_CR1_RE = 1;
			break;
		case U_RX_DMA_EN:USART3_CR3_DMAR = 1;break;
		case U_RX_DMA_DE:USART3_CR3_DMAR = 0;break;
		case U_RX_INT_EN:
			USART3_CR1_RXNEIE = 1;
			EnableNVIC(USART3_IRQn, 3);
			break;
		case U_RX_INT_DE:
			USART3_CR1_RXNEIE = 0;
			DisableNVIC(USART3_IRQn);
			break;
		case U_DATA_BITS_8: USART3_CR1_M = 0;break;
		case U_DATA_BITS_9: USART3_CR1_M = 1;break;

		case U_PARITY_NONE:USART3_CR1_PCE = 0;break;
		case U_PARITY_EVEN:
			USART3_CR1_PS = 0;
			USART3_CR1_PCE = 1;
			break;
		case U_PARITY_ODD:
			USART3_CR1_PS = 1;
			USART3_CR1_PCE = 1;
			break;
		case U_STOP_BITS_1:
			USART3_CR2_S0 = 0;
			USART3_CR2_S1 = 0;
			break;
		case U_STOP_BITS_0_5:
			USART3_CR2_S0 = 1;
			USART3_CR2_S1 = 0;
			break;
		case U_STOP_BITS_2:
			USART3_CR2_S0 = 0;
			USART3_CR2_S1 = 1;
			break;
		case U_STOP_BITS_1_5:
			USART3_CR2_S0 = 1;
			USART3_CR2_S1 = 1;
			break;

		case U_LINEN_SET: USART3_CR2_LINEN = 1;break;
		case U_LINEN_CLR: USART3_CR2_LINEN = 0;break;

		case U_LBDIE_SET: USART3_CR2_LBDIE = 1;break;
		case U_LBDIE_CLR: USART3_CR2_LBDIE = 0;break;

		case U_LBDL_10_BIT: USART3_CR2_LBDL = 0;break;
		case U_LBDL_11_BIT: USART3_CR2_LBDL = 1;break;
		}


	USART3_CR1_UE = 1;
}

void USART3_Chage_BR(uint32_t Baud_Rate){
	/*Wait For End of Transmission*/
	while(!USART3_SR_TC);
	/*Backup USART's State*/
	char Temp = USART3_CR1_UE;
	/*Disable USART*/
	USART3_CR1_UE = 0;

	/*Calculate BRR*/
	float BRR = USART3_BUS_CLK / 16 / Baud_Rate;
	/*Calculate Fraction*/
	float Fraction = (BRR - (int)BRR) * 16 ;
	/*Set Mantissa*/
	USART3_BRR = ((int)(BRR + (Fraction >= 15.5 ? 1 : 0)))<<4;
	/*Set Fraction*/
	USART3_BRR |= Fraction >= 15.5 ? 0 :
			(int)Fraction + (Fraction - (int)Fraction >= 0.5 ? 1 : 0);

	/*Return USART To its First State*/
	USART3_CR1_UE = Temp;
}

char USART3_Read(void){
	/*Return The Received Data*/
	return USART3_DR;
}

char USART3_Check_Errors(void){
	/*Check Error Flags*/
	/*
	 *
	*/
	return 0;
}

void USART3_Send(char data){
	USART3_DR = data;
	while(!USART3_SR_TXE);
}

void USART3_Send_Str(char *Str){
	while(*Str != '\0')
		USART3_Send(*(Str++));
	while(!USART3_SR_TC);
}

void USART3_Send_Ln(){
	USART3_Send_Str("\r\n");
}
