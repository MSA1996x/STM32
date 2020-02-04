/*
 * EXTI.c
 *
 *  Created on: Dec 7, 2019
 *      Author: Mohammed Samir
 */

#include <MCAL/STM32F103/MCAL_H/EXTI.h>

void EXTI_Config(GPIO_TypeDef *GPIO, char PIN, char CONFIG, char TRIGGER){
	/*Enable AFIO Clock*/
	AFIO_CLOCK_ENABLE = 1;

	/*Configure The GPIO Pin*/
	GPIO_Config(GPIO, PIN, MODE_INPUT,CONFIG);

	AFIO->EXTICR[PIN / 4] = (GPIO == GPIOA ? 0 : GPIO == GPIOB ? 1 : 2)<<((PIN % 4) * 4);

	EXTI->RTSR |= (TRIGGER & TRIGGER_RISING)<<PIN;
	EXTI->FTSR |= (TRIGGER>>1)<<PIN;


	/*UNMASK*/
	EXTI->IMR |= 1<<PIN;

	/*Enable Event*/
	EXTI->EMR = 1<<PIN;


	/*Trigger EXTI0 By S.W*/
	//EXTI->SWIER = EXTI_SWIER_SWIER0;
}

void EnableNVIC(char IRQn, char Priority){
	/* [7:4] >> 16 Pre-Empt , [3:0] >> Not Used >> 0 Sub-Priority*/
	NVIC_SetPriorityGrouping(3);
	NVIC_SetPriority(IRQn, Priority);
	NVIC_EnableIRQ(IRQn);
	//NVIC_SetPendingIRQ(EXTI0);
}

void DisableNVIC(char IRQn){
	/*Disable IRQ*/
	NVIC_DisableIRQ(IRQn);
}
