/*
 * EXTI.h
 *
 *  Created on: Dec 7, 2019
 *      Author: Mohammed Samir
 */

#ifndef EXTI_H_
#define EXTI_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/GPIO.h>
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/


/*<Bit-Band Pointers>*/
#define _EXTI_PR_PR0 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 0)
#define _EXTI_PR_PR1 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 1)
#define _EXTI_PR_PR2 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 2)
#define _EXTI_PR_PR3 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 3)
#define _EXTI_PR_PR4 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 4)
#define _EXTI_PR_PR5 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 5)
#define _EXTI_PR_PR6 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 6)
#define _EXTI_PR_PR7 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 7)
#define _EXTI_PR_PR8 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 8)
#define _EXTI_PR_PR9 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 9)
#define _EXTI_PR_PR10 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 10)
#define _EXTI_PR_PR11 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 11)
#define _EXTI_PR_PR12 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 12)
#define _EXTI_PR_PR13 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 13)
#define _EXTI_PR_PR14 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 14)
#define _EXTI_PR_PR15 	BITBAND_PERI(EXTI_BASE + EXTI_PR_OFFSET, 15)
/*</Bit-Band Pointers>*/



/*<Functions' Parameters>*/

/*Cases of TRIGGER Pram*/
#define TRIGGER_DISABLE 	0
#define TRIGGER_RISING 		1
#define TRIGGER_FALLING 	2
#define TRIGGER_ON_CANGE 	3

/*</Functions' Parameters>*/


/*<Functions>*/
void EXTI_Config(GPIO_TypeDef *GPIO, char PIN, char CONFIG, char TRIGGER);
void EnableNVIC(char IRQn, char Priority);
void DisableNVIC(char IRQn);
/*</Functions>*/


#endif /* EXTI_H_ */
