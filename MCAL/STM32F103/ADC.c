/*
 * ADC.c
 *
 *  Created on: Dec 24, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/ADC.h>


void ADC1_Init(char ADC_EOCIE){
	/*Enable Clock For ADC1*/
	ADC1_CLOCK_ENABLE = 1;

	/*Enable/Disable End of Conversion Interrupt*/
	ADC1_CR1_EOCIE = ADC_EOCIE - _ADC_EOCIE_OFFSET;
}

void ADC1_Init_Regular(char ADC_EXTSEL){
	/*Enable External Trigger Conversion Mode For Regular Channels*/
	ADC1_CR2_EXTTRIG = 1;

	/*Start Conversion Trigger For Regular Channel*/
	ADC1_CR2_EXTSEL0 = (ADC_EXTSEL - _ADC_EXTSEL_OFFSET) & 0x01;
	ADC1_CR2_EXTSEL1 = ((ADC_EXTSEL - _ADC_EXTSEL_OFFSET)>>1) & 0x01;
	ADC1_CR2_EXTSEL2 = (ADC_EXTSEL - _ADC_EXTSEL_OFFSET)>>2;
}


void ADC1_Init_Injected(){
	/*Start Conversion by SoftWare as a Trigger For Injected Channel*/
	ADC1_CR2_JEXTSEL2 = 1;
	ADC1_CR2_JEXTSEL1 = 1;
	ADC1_CR2_JEXTSEL0 = 1;
}

void ADC1_Start(){
	/*Enable ADC1*/
	ADC1_CR2_ADON = 1;
}



unsigned short ADC1_Read_Regular(char Channel){
	/*Regular channel sequence length*/
	ADC1_SQR1_REG &= ~((uint32_t)(0b1111<<20));
	ADC1_SQR1_REG |= 0b0000<<20;


	/*First conversion in regular sequence*/
	/*Select Channel*/
	ADC1_SQR3_REG &= 0xFFFFFFF0;
	ADC1_SQR3_REG |= Channel;


	/*Enable Trigger For Regular Channels*/
	ADC1_CR2_EXTTRIG = 1;
	/*Start Conversion of Regular Channels*/
	ADC1_CR2_SWSTART = 1;

	/*Wait for End of Conversion*/
	while(!ADC1_SR_EOC);

	/*Return Regular ADC Value*/
	return ADC1_DR_REG;
}


unsigned int ADC1_Read_Injected(char Channel){
	/*Injected Channel Sequence Length*/
	ADC1_JSQR_REG &= ~((uint32_t)(0b11<<20));
	ADC1_JSQR_REG |= 0b00<<20;

	/*First conversion in injected sequence*/
	/*Select Channel*/
	ADC1_JSQR_REG &= ~((uint32_t)0b1111<<15);
	ADC1_JSQR_REG |= (Channel)<<15;

	/*Enable Trigger For Injected Channels*/
	ADC1_CR2_JEXTTRIG = 1;
	/*Start Conversion of Injected Channels*/
	ADC1_CR2_JSWSTART = 1;


	/*Wait For End Of Conversion*/
	while(!ADC1_SR_JEOC);

	/*Return Injected ADC Value*/
	return ADC1_JDR1_REG;
}

float ADC1_Cal_Volt(unsigned int ADC_Value){
	//Return The Corresponding Voltage Value
	return ADC_Value * 3.3 / 4095;
}

float ADC1_Read_Temp_Volt(){
	/*Enable Temperature Sensor and VREFINT Channel*/
	ADC1_CR2_TSVREFE = 1;
	/*Return Temperature Sensor Voltage Value*/
	return ADC1_Cal_Volt(ADC1_Read_Regular(16));
}
