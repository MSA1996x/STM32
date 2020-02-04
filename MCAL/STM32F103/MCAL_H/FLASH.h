/*
 * FLASH.h
 *
 *  Created on: Jan 17, 2020
 *      Author: Mohammed Samir
 */

#ifndef MCAL_STM32F103_MCAL_H_FLASH_H_
#define MCAL_STM32F103_MCAL_H_FLASH_H_

/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
/*</Includes>*/

/*<Definitions>*/
#define FLASH_KEY_1 			0x45670123
#define FLASH_KEY_2 			0xCDEF89AB

#define FLASH_PAGEx(Page, Offset)	(volatile uint16_t *)(FLASH_BASE + (1024 * Page) + (Offset))
/*</Definitions>*/

/*<Bit-Band Pointers>*/
#define FLASH_ACR_PRFTBS_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_ACR_OFFSET, 5)
#define FLASH_ACR_PRFTBE_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_ACR_OFFSET, 4)
#define FLASH_ACR_HLFCYA_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_ACR_OFFSET, 3)

#define FLASH_SR_EOP_BIT  			BITBAND_PERI(FLASH_REG_BASE + FLASH_SR_OFFSET, 5)
#define FLASH_SR_WRPRTERR_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_SR_OFFSET, 4)
#define FLASH_SR_PGERR_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_SR_OFFSET, 2)
#define FLASH_SR_BSY_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_SR_OFFSET, 0)

#define FLASH_CR_EOPIE_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 12)
#define FLASH_CR_ERRIE_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 10)
#define FLASH_CR_OPTWRE_BIT  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 9)
#define FLASH_CR_LOCK_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 7)
#define FLASH_CR_STRT_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 6)
#define FLASH_CR_OPTER_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 5)
#define FLASH_CR_OPTPG_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 4)
#define FLASH_CR_MER_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 2)
#define FLASH_CR_PER_BIT	  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 1)
#define FLASH_CR_PG_BIT		  		BITBAND_PERI(FLASH_REG_BASE + FLASH_CR_OFFSET, 0)
/*</Bit-Band Pointers>*/



/*<Registers Pointers>*/
#define FLASH_ACR_REG	 	(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_ACR_OFFSET))
#define FLASH_KEYR_REG	 	(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_KEYR_OFFSET))
#define FLASH_OPTKEYR_REG	(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_OPTKEYR_OFFSET))
#define FLASH_SR_REG		(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_SR_OFFSET))
#define FLASH_CR_REG	 	(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_CR_OFFSET))
#define FLASH_AR_REG		(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_AR_OFFSET))
#define FLASH_OBR_REG		(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_OBR_OFFSET))
#define FLASH_WRPR_REG	 	(*(volatile unsigned int *)(FLASH_REG_BASE + FLASH_WRPR_OFFSET))
/*</Registers Pointers>*/


/*<Functions>*/
void Flash_Unlock(void);
void Flash_Lock(void);
/*char Flash_Write_8(char Page, uint16_t Offset, uint8_t Data);*/
char Flash_Write_16(char Page, uint16_t Offset, uint16_t HWord_Data);
uint8_t Flash_Read_8(char Page, uint16_t Offset);
uint16_t Flash_Read_16(char Page, uint16_t Offset);
void Flash_Page_Erase(char Page);
/*void Flash_Write_Protection(void);*/
/*void Flash_Write_UnProtection(void);*/
/*char Flash_Check_Error(void);*/
/*</Functions>*/

#endif /* MCAL_STM32F103_MCAL_H_FLASH_H_ */
