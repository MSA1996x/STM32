/*
 * WDG.h
 *
 *  Created on: Jan 24, 2020
 *      Author: Mohammed Samir
 */

#ifndef MCAL_STM32F103_MCAL_H_WDG_H_
#define MCAL_STM32F103_MCAL_H_WDG_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/

/*<Definitions>*/
#define IWDG_KR_ACCESS_KEY 	0x5555
#define IWDG_KR_START_KEY 	0xCCCC
#define IWDG_KR_RELOAD_KEY 	0xAAAA
/*</Definitions>*/

/*<Bit-Band Pointers>*/
#define WWDG_CLOCK_ENABLE_BIT  		BITBAND_PERI(RCC_BASE + RCC_APB1ENR_OFFSET, 11)
#define WWDG_RESET_BIT		  		BITBAND_PERI(RCC_BASE + RCC_APB1RSTR_OFFSET, 11)

#define RCC_CSR_LSIRDY_BIT		  	BITBAND_PERI(RCC_BASE + RCC_CSR_OFFSET, 1)
#define RCC_CSR_LSION_BIT		  	BITBAND_PERI(RCC_BASE + RCC_CSR_OFFSET, 0)

#define IWDG_SR_RVU_BIT		  		BITBAND_PERI(IWDG_BASE + IWDG_SR_OFFSET, 1)
#define IWDG_SR_PVU_BIT		  		BITBAND_PERI(IWDG_BASE + IWDG_SR_OFFSET, 0)

#define WWDG_CR_WDGA_BIT	  		BITBAND_PERI(WWDG_BASE + WWDG_CR_OFFSET, 7)

#define WWDG_CFR_EWI_BIT	  		BITBAND_PERI(WWDG_BASE + WWDG_CFR_OFFSET, 9)

#define WWDG_SR_EWIF_BIT	  		BITBAND_PERI(WWDG_BASE + WWDG_SR_OFFSET, 0)
/*</Bit-Band Pointers>*/



/*<Registers Pointers>*/
#define WWDG_DBGMCU_CR_REG	(*(volatile unsigned int *)(DBGMCU_CR_ADD))

#define IWDG_KR_REG		 	(*(volatile unsigned int *)(IWDG_BASE + IWDG_KR_OFFSET))
#define IWDG_PR_REG		 	(*(volatile unsigned int *)(IWDG_BASE + IWDG_PR_OFFSET))
#define IWDG_RLR_REG	 	(*(volatile unsigned int *)(IWDG_BASE + IWDG_RLR_OFFSET))
#define IWDG_SR_REG	 		(*(volatile unsigned int *)(IWDG_BASE + IWDG_SR_OFFSET))

#define WWDG_CR_REG		 	(*(volatile unsigned int *)(WWDG_BASE + WWDG_CR_OFFSET))
#define WWDG_CFR_REG	 	(*(volatile unsigned int *)(WWDG_BASE + WWDG_CFR_OFFSET))
#define WWDG_SR_REG		 	(*(volatile unsigned int *)(WWDG_BASE + WWDG_SR_OFFSET))
/*</Registers Pointers>*/





/*<Functions>*/
void IWDG_Init(char IWDG_PR, uint16_t Reload_Value, char IWDG_DBGMCU);
void IWDG_Start(void);
void IWDG_Refresh(void);


void WWDG_Init(char Window_Value, char Counter_Value, char WWDG_WDGTB, char WWDG_DBGMCU);
void WWDG_Start(void);
void WWDG_Refresh(void);
char WWDG_Get_Counter(void);
/*</Functions>*/

#endif /* MCAL_STM32F103_MCAL_H_WDG_H_ */
