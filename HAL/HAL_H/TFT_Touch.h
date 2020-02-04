/*
 * TFT_Touch.h
 *
 *  Created on: Jan 27, 2020
 *      Author: Mohammed Samir
 */

#ifndef HAL_HAL_H_TFT_TOUCH_H_
#define HAL_HAL_H_TFT_TOUCH_H_

/*<Includes>*/
#include "MCAL/STM32F103/MCAL_H/GPIO.h"
#include "MCAL/STM32F103/MCAL_H/ADC.h"
#include "stdlib.h"
/*</Includes>*/


/*<Definitions>*/
#define GPIO_PORT 	GPIOA
#define Xp 			7
#define Ym 			6

#define ADC_PORT 	GPIOA
#define Yp 			5
#define Xm 			4


typedef struct TS_Point_Struct{
	unsigned short X : 12;
	unsigned short Y : 12;
	unsigned short Z : 12;
	unsigned short Valid : 1;
} TS_Point;
/*</Definitions>*/


/*<Functions>*/
void TS_Init(void);
TS_Point TS_Get_Point(void);
/*</Functions>*/

#endif /* HAL_HAL_H_TFT_TOUCH_H_ */
