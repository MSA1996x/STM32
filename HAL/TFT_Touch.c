/*
 * TFT_Touch.c
 *
 *  Created on: Jan 27, 2020
 *      Author: Mohammed Samir
 */


#include "HAL/HAL_H/TFT_Touch.h"

void TS_Init(void){
	ADC1_Init(ADC_EOCIE_DISABLE);
	ADC1_Init_Regular(ADC_EXTSEL_SWSTART);
	ADC1_Start();
}

TS_Point TS_Get_Point(void){
	TS_Point Point;
	Point.Valid = 1;
	int samples[2];

	/*==================X==================*/
	GPIO_Config(GPIO_PORT, Ym, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_PUSH_PULL);
	GPIO_Config(GPIO_PORT, Xp, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_PUSH_PULL);
	GPIO_Config(ADC_PORT, Xm, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_PUSH_PULL);
	GPIO_Config(ADC_PORT, Yp, MODE_INPUT, CONFIG_INPUT_ANALOG);

	digitalWrite(GPIO_PORT, Ym, STATE_LOW);
	digitalWrite(GPIO_PORT, Xp, STATE_HIGH);
	digitalWrite(ADC_PORT, Xm, STATE_LOW);

	for (int i=0; i<2; i++) {
		for(int i = 0; i < 500; i++);
		samples[i] = ADC1_Read_Regular(Yp);
	}

	if (abs(samples[0] - samples[1]) > 50) {
		Point.Valid = 0;
	}

	Point.X = (samples[0] + samples[1]) / 2;


	/*==================Y==================*/
	GPIO_Config(ADC_PORT, Yp, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_GP_PUSH_PULL);
	GPIO_Config(ADC_PORT, Xm, MODE_INPUT, CONFIG_INPUT_ANALOG);

	digitalWrite(GPIO_PORT, Xp, STATE_LOW);
	digitalWrite(ADC_PORT, Yp, STATE_HIGH);


	for (int i=0; i<2; i++) {
		for(int i = 0; i < 500; i++);
		samples[i] = ADC1_Read_Regular(Xm);
	}

	if (abs(samples[0] - samples[1]) > 50) {
		Point.Valid = 0;
	}

	Point.Y = (samples[0] + samples[1]) / 2;


	/*==================Z==================*/
	GPIO_Config(ADC_PORT, Yp, MODE_INPUT, CONFIG_INPUT_ANALOG);

	digitalWrite(GPIO_PORT, Xp, STATE_LOW);
	digitalWrite(GPIO_PORT, Ym, STATE_HIGH);

	Point.Z = ADC1_Read_Regular(Yp) - ADC1_Read_Regular(Xm);

	return Point;
}
