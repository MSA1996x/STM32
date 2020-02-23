/*
 * DS18B20.h
 *
 *  Created on: Feb 22, 2020
 *      Author: Mohammed Samir
 */

#ifndef HAL_HAL_H_DS18B20_H_
#define HAL_HAL_H_DS18B20_H_

#include "MCAL/STM32F103/MCAL_H/USART1.h"

#define DS18B20_RESET_CMD		0xF0
#define DS18B20_SKIP_ROM		0xCC
#define DS18B20_CONVERT_CMD		0x44
#define DS18B20_SCRATCH_READ	0xBE
#define DS18B20_SCRATCH_WRITE	0x4E

void DS18B20_Init(void);
char DS18B20_SendRest(void);
void DS18B20_SendCMD(char CMD);
unsigned int DS18B20_Receive(void);
float DS18B20_Read_Temp(void);


#endif /* HAL_HAL_H_DS18B20_H_ */
