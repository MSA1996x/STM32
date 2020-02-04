/*
 * delay.c
 *
 *  Created on: Dec 20, 2019
 *      Author: Mohammed Samir
 */


#include <HAL/HAL_H/Delay.h>

void delay_init(void){
	/*Configure Timer 2*/
	TMR2_Conifg(1);
}

void delay_ms(unsigned int ms){
	/*Reset The Counter*/
	TMR2_Val_Reset();

	/*Start Counting*/
	TMR2_Start();
	for(unsigned int i = 0; i < ms * 2; i++)
	{
		/*Reset The Counter*/
		TMR2_Val_Reset();
		/*Wait For 0.5 ms*/
		while(CNT_HALF_MS > TMR2_Val());
	}
	/*Stop Counting*/
	TMR2_Stop();
}

void delay_us(unsigned int us){
	/*Start Counting*/
	TMR2_Start();
	unsigned int _us = us - us * CNT_US_FACTOR;
	for(unsigned long int i = 0; i < _us; i++)
	{
		/*Reset The Counter*/
		TMR2_Val_Reset();
		/*Wait For 1 us*/
		while(CNT_US > TMR2_Val());
	}
	/*Stop Counting*/
	TMR2_Stop();
}
