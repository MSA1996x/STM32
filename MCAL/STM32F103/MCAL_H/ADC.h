/*
 * ADC.h
 *
 *  Created on: Dec 24, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_ADC_H_
#define HEADERS_ADC_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/


/*<Bit-Band Pointers>*/
#define ADC3_CLOCK_ENABLE  		BITBAND_PERI(RCC_BASE + RCC_APB2ENR_OFFSET, 15)
#define ADC2_CLOCK_ENABLE  		BITBAND_PERI(RCC_BASE + RCC_APB2ENR_OFFSET, 10)
#define ADC1_CLOCK_ENABLE  		BITBAND_PERI(RCC_BASE + RCC_APB2ENR_OFFSET, 9)


#define ADC1_SR_STRT  			BITBAND_PERI(ADC1_BASE + ADC_SR_OFFSET, 4)
#define ADC1_SR_JSTRT  			BITBAND_PERI(ADC1_BASE + ADC_SR_OFFSET, 3)
#define ADC1_SR_JEOC  			BITBAND_PERI(ADC1_BASE + ADC_SR_OFFSET, 2)
#define ADC1_SR_EOC  			BITBAND_PERI(ADC1_BASE + ADC_SR_OFFSET, 1)


#define ADC1_CR1_SCAN  			BITBAND_PERI(ADC1_BASE + ADC_CR1_OFFSET, 8)
#define ADC1_CR1_EOCIE 			BITBAND_PERI(ADC1_BASE + ADC_CR1_OFFSET, 5)


#define ADC1_CR2_TSVREFE 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 23)
#define ADC1_CR2_SWSTART 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 22)
#define ADC1_CR2_JSWSTART 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 21)
#define ADC1_CR2_EXTTRIG 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 20)
#define ADC1_CR2_EXTSEL2 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 19)
#define ADC1_CR2_EXTSEL1 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 18)
#define ADC1_CR2_EXTSEL0 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 17)

#define ADC1_CR2_JEXTTRIG 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 15)
#define ADC1_CR2_JEXTSEL2 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 14)
#define ADC1_CR2_JEXTSEL1 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 13)
#define ADC1_CR2_JEXTSEL0 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 12)

#define ADC1_CR2_ALIGN	 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 11)
#define ADC1_CR2_CONT	 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 1)
#define ADC1_CR2_ADON	 		BITBAND_PERI(ADC1_BASE + ADC_CR2_OFFSET, 0)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define ADC1_JOFR1_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JOFT1_OFFSET))
#define ADC1_JOFR2_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JOFT2_OFFSET))
#define ADC1_JOFR3_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JOFT3_OFFSET))
#define ADC1_JOFR4_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JOFT4_OFFSET))
#define ADC1_HTR_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_HTR_OFFSET))
#define ADC1_LTR_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_LTR_OFFSET))
#define ADC1_SQR1_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_SQR1_OFFSET))
#define ADC1_SQR2_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_SQR2_OFFSET))
#define ADC1_SQR3_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_SQR3_OFFSET))
#define ADC1_JSQR_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JSQR_OFFSET))
#define ADC1_JDR1_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JDR1_OFFSET))
#define ADC1_JDR2_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JDR2_OFFSET))
#define ADC1_JDR3_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JDR3_OFFSET))
#define ADC1_JDR4_REG	 			(*(volatile unsigned int *)(ADC1_BASE + ADC_JDR4_OFFSET))
#define ADC1_DR_REG		 			(*(volatile unsigned int *)(ADC1_BASE + ADC_DR_OFFSET))
#define ADC1_DATA_REG	 			(*(volatile unsigned short *)(ADC1_BASE + ADC_DR_OFFSET))
#define ADC1_ADC2DATA_REG 			(*(volatile unsigned short *)(ADC1_BASE + ADC_DR_OFFSET + 16))
/*</Registers Pointers>*/



/*<Functions' Parameters>*/

/*Cases of ADC_EXTSEL Pram*/
#define _ADC_EXTSEL_OFFSET			0
#define ADC_EXTSEL_T1CC1			(0 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_T1CC2			(1 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_T1CC3			(2 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_T2CC2			(3 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_T3TRGO			(4 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_T4CC4			(5 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_EXTI11			(6 + _ADC_EXTSEL_OFFSET)
#define ADC_EXTSEL_SWSTART			(7 + _ADC_EXTSEL_OFFSET)

/*Cases of ADC_EOCIE Pram*/
#define _ADC_EOCIE_OFFSET			8
#define ADC_EOCIE_DISABLE			(0 + _ADC_EOCIE_OFFSET)
#define ADC_EOCIE_ENABLE			(1 + _ADC_EOCIE_OFFSET)

/*</Functions' Parameters>*/


/*<Functions>*/
void ADC1_Init(char ADC_EOCIE);
void ADC1_Init_Regular(char ADC_EXTSEL);
void ADC1_Init_Injected();
void ADC1_Start();
uint16_t ADC1_Read_Regular(char Channel);
unsigned int ADC1_Read_Injected(char Channel);
float ADC1_Cal_Volt(unsigned int ADC_Value);
float ADC1_Read_Temp_Volt();
/*</Functions>*/


#endif /* HEADERS_ADC_H_ */
