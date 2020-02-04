/*
 * DMA.c
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */

#include <MCAL/STM32F103/MCAL_H/DMA.h>


void DMA1_Init(char Ch, char M2M, char CIRCULAR, char PRIORITY, char MSIZE, char PSIZE, char MINC, char PINC, char DIR){
		/*Enable DMA1 Clock*/
		DMA1_CLOCK_ENABLE = 1;

		/*Channel Will Be Used For Memory To Memory Transfer*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 14) = M2M;
		/*Set Mode*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 5) = CIRCULAR - 2;
		/*Set Priority*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 12) = (PRIORITY - 4) & 0x01;/*PL0*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 13) = (PRIORITY - 4)>>1;/*PL1*/
		/*Source And Destination Data Size*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 10) = (MSIZE - 8) & 0x01;/*MSIZE0*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 11) = (MSIZE - 8)>>1;/*MSIZE1*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 8) = (PSIZE - 11) & 0x01;/*PSIZE0*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 9) = (PSIZE - 11)>>1;/*PSIZE1*/

		/*automatic memory & Peri increment enable. Destination and source*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 7) = MINC - 14;
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 6) = PINC - 16;
		/*Location assigned to peripheral register will be source*/
		BITBAND_PERI_DMA1(Ch, DMA_CCRx, 4) = DIR - 18;
}

void DMA1_Init_Adv(char Ch, char Num_Of_Args, ...){
	DMA1_CLOCK_ENABLE = 1;

	va_list lst;
	va_start(lst, Num_Of_Args);

	for(int i = 0; i < Num_Of_Args; i++)
		switch((char)va_arg(lst, int)){
		case DMA_M2M_ENABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 14) = 1;break;
		case DMA_M2M_DISABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 14) = 0;break;
		case DMA_CIRCULAR_ENABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 5) = 1;break;
		case DMA_CIRCULAR_DISABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 5) = 0;break;
		case DMA_PRIORITY_LOW:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 12) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 13) = 0;
			break;
		case DMA_PRIORITY_MEDIUM:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 12) = 1;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 13) = 0;
			break;
		case DMA_PRIORITY_HIGH:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 12) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 13) = 1;
			break;
		case DMA_PRIORITY_VERY_HIGH:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 12) = 1;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 13) = 1;
			break;
		case DMA_MSIZE_8BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 10) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 11) = 0;
			break;
		case DMA_MSIZE_16BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 10) = 1;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 11) = 0;
			break;
		case DMA_MSIZE_32BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 10) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 11) = 1;
			break;
		case DMA_PSIZE_8BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 8) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 9) = 0;
			break;
		case DMA_PSIZE_16BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 8) = 1;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 9) = 0;
			break;
		case DMA_PSIZE_32BIT:
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 8) = 0;
			BITBAND_PERI_DMA1(Ch, DMA_CCRx, 9) = 1;
			break;
		case DMA_MINC_ENABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 7) = 1;break;
		case DMA_MINC_DISABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 7) = 0;break;
		case DMA_PINC_ENABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 6) = 1;break;
		case DMA_PINC_DISABLE:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 6) = 0;break;
		case DMA_DIR_M:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 4) = 1;break;
		case DMA_DIR_P:BITBAND_PERI_DMA1(Ch, DMA_CCRx, 4) = 0;break;
		}

	va_end(lst);
}


void DMA1_SetAddresses(char Ch, uint32_t CPAR, uint32_t CMAR, uint32_t size){
	/*Source And Destination Start Addresses*/
	REG_PERI_DMA1(Ch, DMA_CPARx) = (uint32_t)CPAR;
	REG_PERI_DMA1(Ch, DMA_CMARx) = (uint32_t)CMAR;
	/*Chunk Of Data To Be Transfered*/
	REG_PERI_DMA1(Ch, DMA_CNDTRx) = size;
}

void DMA1_Enable(char Ch){
	BITBAND_PERI_DMA1(Ch, DMA_ISR, 15) = 0;
	BITBAND_PERI_DMA1(Ch, DMA_ISR, 15) = 0;
	BITBAND_PERI_DMA1(Ch, DMA_ISR, 13) = 0;
	BITBAND_PERI_DMA1(Ch, DMA_ISR, 12) = 0;

	/*Enable DMA1 Channel transfer*/
	BITBAND_PERI_DMA1(Ch, DMA_CCRx, 0) = 1;
}
