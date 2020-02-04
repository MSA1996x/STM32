/*
 * delay.h
 *
 *  Created on: Dec 20, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_DELAY_H_
#define HEADERS_DELAY_H_

/*<Includes>*/
#include "MCAL/STM32F103/MCAL_H/Timer2.h"
#include "HAL/HAL_H/Delay.h"
/*</Includes>*/


/*<Definitions>*/
#define CNT_HALF_MS		(SystemCoreClock / 2000)
#define CNT_US			(SystemCoreClock / 2000000)
#define CNT_US_FACTOR	0.2
/*</Definitions>*/


/*<Functions>*/
void delay_init(void);
void delay_ms(unsigned int ms);
void delay_us(unsigned int us);
/*</Functions>*/


#endif /* HEADERS_DELAY_H_ */
