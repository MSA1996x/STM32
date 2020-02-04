/*
 * SPI.c
 *
 *  Created on: Dec 21, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/SPI.h>





void SPI1_Init(char BR, char SPI_MODE, char SPI_RX_INT, char SPI_DFF, char SPI_CPOL, char SPI_CPHA, char SPI_LSBFIRST){

	SPI1_Pin_Config(SPI_MODE);

	SPI1_CLOCK_ENABLE = 1;

	SPI1_CR1_MSTR = SPI_MODE - _SPI_MSTR_OFFSET;

	SPI1_CR2_RXNEIE = (SPI_RX_INT - _SPI_RX_INT_OFFSET);

	SPI1_CR1_DFF = SPI_DFF - _SPI_DFF_OFFSET;

	BR -= _SPI_BR_OFFSET;
	SPI1_CR1_BR0 = BR & 0x01;
	SPI1_CR1_BR1 = (BR>>1) & 0x01;
	SPI1_CR1_BR2 = BR>>2;

	SPI1_CR1_CPOL = SPI_CPOL - _SPI_CPOL_OFFSET;
	SPI1_CR1_CPHA = SPI_CPHA - _SPI_CPHA_OFFSET;

	SPI1_CR1_LSBFIRST = SPI_LSBFIRST - _SPI_LSBFIRST_OFFSET;

	SPI1_CR1_SSM = 1;



	if(SPI_MODE){
		SPI1_CR2_SSOE = 1;
		SPI1_CR1_SSI = 1;
	}

	SPI1_CR1_SPE = 1;
}


void SPI1_Pin_Config(char SPI_MODE){
	/*NSS1 Pin*/
	GPIO_Config(GPIOA, 4, SPI_MODE ? MODE_OUTPUT_50MHZ : MODE_INPUT, SPI_MODE ? CONFIG_OUTPUT_GP_PUSH_PULL : CONFIG_INPUT_PULL_UP);
	PA4 = 1;

	/*SCK1 Pin*/
	GPIO_Config(GPIOA, 5, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);

	/*MISO1 Pin*/
	GPIO_Config(GPIOA, 6, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);

	/*MOSI1 Pin*/
	GPIO_Config(GPIOA, 7, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_PUSH_PULL);



}

void SPI1_Master_Send(unsigned int Data, GPIO_TypeDef *GPIO_SS, char PIN_SS){
	digitalWrite(GPIO_SS, PIN_SS, STATE_LOW);
	SPI1_DR = Data;
	while(SPI1_SR_BSY);
	digitalWrite(GPIO_SS, PIN_SS, STATE_HIGH);
}

void SPI1_Send(unsigned int Data){
	SPI1_DR = Data;
	while(SPI1_SR_TXE);
}

unsigned int SPI1_Rec(void){
	while(!SPI1_SR_RXNE);
	return SPI1_DR;
}
