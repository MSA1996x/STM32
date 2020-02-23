/*
 * LM75A.h
 *
 *  Created on: Dec 29, 2019
 *      Author: Mohammed Samir
 */

#ifndef HEADERS_I2C_LM75A_H_
#define HEADERS_I2C_LM75A_H_

/*<Includes>*/
#include "MCAL/STM32F103/MCAL_H/I2C.h"
/*</Includes>*/


/*<Registers Addresses>*/
#define TEMP_REG	0x00
#define CONFIG_REG	0x01
#define T_HYST_REG	0x02
#define T_OS_REG	0x03
#define ID_REG		0x07
/*</Registers Addresses>*/


/*<Functions>*/
char LM75A_Init(unsigned char Address7);
float LM75A_Read_Temp(unsigned char Address7);
/*</Functions>*/


#endif /* HEADERS_I2C_LM75A_H_ */
