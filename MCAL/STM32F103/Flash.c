/*
 * Flash.c
 *
 *  Created on: Jan 17, 2020
 *      Author: Mohammed Samir
 */


#include "MCAL/STM32F103/MCAL_H/FLASH.h"


void Flash_Unlock(void){
	/*Unlocking Sequence*/
	FLASH_KEYR_REG = FLASH_KEY_1;
	FLASH_KEYR_REG = FLASH_KEY_2;
}

void Flash_Lock(void){
	/*Lock Flash*/
	FLASH_CR_LOCK_BIT = 1;
}

/*
char Flash_Write_8(char Page, uint16_t Offset, uint8_t Data){

	return 0;
}
*/

char Flash_Write_16(char Page, uint16_t Offset, uint16_t HWord_Data){
	/*Enable Flash Programming*/
	FLASH_CR_PG_BIT = 1;

	/*Wait Busy Flag*/
	while(FLASH_SR_BSY_BIT);

	*FLASH_PAGEx(Page, Offset * 2) = HWord_Data;

	/*Wait Busy Flag*/
	while(FLASH_SR_BSY_BIT);

	/*Disable Flash Programming*/
	FLASH_CR_PG_BIT = 0;

	/*Make Sure The Address Is Written Successfully*/
	return Flash_Read_16(Page, Offset * 2) == HWord_Data;
}

uint8_t Flash_Read_8(char Page, uint16_t Offset){
	return *FLASH_PAGEx(Page, Offset);
}

uint16_t Flash_Read_16(char Page, uint16_t Offset){
	return *FLASH_PAGEx(Page, Offset * 2);
}

void Flash_Page_Erase(char Page){
	/*Wait Busy Flag*/
	while(FLASH_SR_BSY_BIT);

	/*Set Page Erase Bit*/
	FLASH_CR_PER_BIT = 1;

	/*The Address Of Erased Page*/
	FLASH_AR_REG = (uint32_t)FLASH_PAGEx(Page, 0);

	/*Start Erasing*/
	FLASH_CR_STRT_BIT = 1;

	/*Wait Busy Flag*/
	while(FLASH_SR_BSY_BIT);
}

/*
void Flash_Write_Protection(void){

}
*/

/*
void Flash_Write_UnProtection(void){

}
*/

/*
char Flash_Check_Error(void){

	return 0;
}
*/
