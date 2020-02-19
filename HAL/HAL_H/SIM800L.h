/*
 * SIM800L.h
 *
 *  Created on: Feb 19, 2020
 *      Author: Mohammed Samir
 */

#ifndef HAL_HAL_H_SIM800L_H_
#define HAL_HAL_H_SIM800L_H_

#include "MCAL/STM32F103/MCAL_H/USART2.h"


void SIM800L_Init(void);
void SIM800L_CMD(char *CMD);
void SIM800L_Call(char *Number);

#endif /* HAL_HAL_H_SIM800L_H_ */
