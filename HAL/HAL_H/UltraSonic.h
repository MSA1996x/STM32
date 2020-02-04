/*
 * UltraSonic.h
 *
 *  Created on: Jan 12, 2020
 *      Author: Mohammed Samir
 */

#ifndef HAL_HAL_H_ULTRASONIC_H_
#define HAL_HAL_H_ULTRASONIC_H_

/*<Includes>*/
#include "MCAL/STM32F103/MCAL_H/GPIO.h"
#include "MCAL/STM32F103/MCAL_H/Timer2.h"
#include "HAL/HAL_H/Delay.h"
/*</Includes>*/


/*<Definitions>*/
typedef struct UltraSonic_Struct{
	GPIO_TypeDef *GPIO;
	char Triger_Pin;
	char Echo_Pin;
} UltraSonic;
/*</Definitions>*/


/*<Functions>*/
void UltraSonic_Init(UltraSonic US);
float UltraSonic_Get_Distance(UltraSonic US);
/*</Functions>*/

#endif /* HAL_HAL_H_ULTRASONIC_H_ */
