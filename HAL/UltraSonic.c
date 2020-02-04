/*
 * UltraSonic.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Mohammed Samir
 */


#include "HAL/HAL_H/UltraSonic.h"


void UltraSonic_Init(UltraSonic US){
	GPIO_Config(GPIOB, 1, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_PUSH_PULL);
	GPIO_Config(GPIOB, 0, MODE_INPUT, CONFIG_INPUT_FLOATING);
}

float UltraSonic_Get_Distance(UltraSonic US){

	/*Configure The Timer To Measure The Time*/
	TMR2_Val_Reset();
	TMR2_Conifg(50);
	TIM2_EGR_UG = 1;
	while(!TIM2_SR_UIF);
	TIM2_SR_UIF = 0;

	/*The Distance*/
	float Distance = 0;

	/*Return 0 ON TimeOut*/
	unsigned int TimeOut = 0;
	while(digitalRead(GPIOB, 0)){
		if(++TimeOut > 5000){
			goto Reset;
		}
	}

	TimeOut = 0;
	/*Trigger The Sensor OR Return 0 ON TimeOut*/
	while(!digitalRead(GPIOB, 0)){
		digitalWrite(GPIOB, 1, STATE_HIGH);
		for(int i = 0; i < 100; i++);
		digitalWrite(GPIOB, 1, STATE_LOW);
		for(int i = 0; i < 100; i++);
		if(++TimeOut > 15){
			goto Reset;
		}
	}

	/*Start Measuring The Time OR Return 0 ON TimeOut*/
	TMR2_Start();
	while(digitalRead(GPIOB, 0)){
		if(TMR2_Val() > 5000){
			goto Reset;
		}
	}

	/*Calculate The Distance*/
	Distance = TMR2_Val() / 84.0f;


Reset:
	/*Reset Timer To Its Previous State*/
	TMR2_Stop();
	TMR2_Conifg(1);
	TIM2_EGR_UG = 1;
	while(!TIM2_SR_UIF);
	TIM2_SR_UIF = 0;

	/*Return Distance*/
	return Distance;
}
