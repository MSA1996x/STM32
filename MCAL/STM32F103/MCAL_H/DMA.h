/*
 * DMA.h
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */

#ifndef DMA_H_
#define DMA_H_


/*<Includes>*/
#include <MCAL/STM32F103/MCAL_H/DMA.h>
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>
#include <stdarg.h>
/*</Includes>*/



/*<Bit-Band Pointers>*/
#define DMA1_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_AHBENR_OFFSET, 0)
#define DMA2_CLOCK_ENABLE  	BITBAND_PERI(RCC_BASE + RCC_AHBENR_OFFSET, 1)

#define DMA1_CH1_TEIF4			BITBAND_PERI_DMA1(1, DMA_ISR, 15)
#define DMA1_CH1_HTIF4			BITBAND_PERI_DMA1(1, DMA_ISR, 15)
#define DMA1_CH1_TCIF4			BITBAND_PERI_DMA1(1, DMA_ISR, 13)
#define DMA1_CH1_GIF4			BITBAND_PERI_DMA1(1, DMA_ISR, 12)


#define DMA1_CH1_MEM2MEM		BITBAND_PERI_DMA1(1, DMA_CCRx, 14)
#define DMA1_CH1_PL1			BITBAND_PERI_DMA1(1, DMA_CCRx, 13)
#define DMA1_CH1_PL0			BITBAND_PERI_DMA1(1, DMA_CCRx, 12)
#define DMA1_CH1_MSIZE1			BITBAND_PERI_DMA1(1, DMA_CCRx, 11)
#define DMA1_CH1_MSIZE0			BITBAND_PERI_DMA1(1, DMA_CCRx, 10)
#define DMA1_CH1_PSIZE1			BITBAND_PERI_DMA1(1, DMA_CCRx, 9)
#define DMA1_CH1_PSIZE0			BITBAND_PERI_DMA1(1, DMA_CCRx, 8)
#define DMA1_CH1_MINC			BITBAND_PERI_DMA1(1, DMA_CCRx, 7)
#define DMA1_CH1_PINC			BITBAND_PERI_DMA1(1, DMA_CCRx, 6)
#define DMA1_CH1_CIRC			BITBAND_PERI_DMA1(1, DMA_CCRx, 5)
#define DMA1_CH1_DIR			BITBAND_PERI_DMA1(1, DMA_CCRx, 4)
#define DMA1_CH1_TEIE			BITBAND_PERI_DMA1(1, DMA_CCRx, 3)
#define DMA1_CH1_HTIE			BITBAND_PERI_DMA1(1, DMA_CCRx, 2)
#define DMA1_CH1_TCIE			BITBAND_PERI_DMA1(1, DMA_CCRx, 1)
#define DMA1_CH1_EN				BITBAND_PERI_DMA1(1, DMA_CCRx, 0)
/*</Bit-Band Pointers>*/


/*<Registers Pointers>*/
#define DMA1_CH1_PA  REG_PERI_DMA1(1, DMA_CPARx)
#define DMA1_CH1_MA  REG_PERI_DMA1(1, DMA_CMARx)
#define DMA1_CH1_NDT REG_PERI_DMA1(1, DMA_CNDTRx)
/*</Registers Pointers>*/


/*<Functions' Parameters>*/

/*Cases of DMA_M2M Pram*/
#define _DMA_M2M_OFFSET				0
#define DMA_M2M_DISABLE 			(0 + _DMA_M2M_OFFSET)
#define DMA_M2M_ENABLE	 			(1 + _DMA_M2M_OFFSET)

/*Cases of DMA_CIRCULAR Pram*/
#define _DMA_CIRCULAR_OFFSET		2
#define DMA_CIRCULAR_ENABLE	 		(1 + _DMA_CIRCULAR_OFFSET)
#define DMA_CIRCULAR_DISABLE 		(0 + _DMA_CIRCULAR_OFFSET)

/*Cases of DMA_PRIORITY Pram*/
#define _DMA_PRIORITY_OFFSET		4
#define DMA_PRIORITY_LOW			(0 + _DMA_PRIORITY_OFFSET)
#define DMA_PRIORITY_MEDIUM			(1 + _DMA_PRIORITY_OFFSET)
#define DMA_PRIORITY_HIGH			(2 + _DMA_PRIORITY_OFFSET)
#define DMA_PRIORITY_VERY_HIGH		(3 + _DMA_PRIORITY_OFFSET)

/*Cases of DMA_PSIZE Pram*/
#define _DMA_PSIZE_OFFSET			11
#define DMA_PSIZE_8BIT				(0 + _DMA_PSIZE_OFFSET)
#define DMA_PSIZE_16BIT				(1 + _DMA_PSIZE_OFFSET)
#define DMA_PSIZE_32BIT				(2 + _DMA_PSIZE_OFFSET)

/*Cases of DMA_MSIZE Pram*/
#define _DMA_MSIZE_OFFSET			8
#define DMA_MSIZE_8BIT				(0 + _DMA_MSIZE_OFFSET)
#define DMA_MSIZE_16BIT				(1 + _DMA_MSIZE_OFFSET)
#define DMA_MSIZE_32BIT				(2 + _DMA_MSIZE_OFFSET)

/*Cases of DMA_MINC Pram*/
#define _DMA_MINC_OFFSET			14
#define DMA_MINC_ENABLE				(1 + _DMA_MINC_OFFSET)
#define DMA_MINC_DISABLE			(0 + _DMA_MINC_OFFSET)

/*Cases of DMA_PINC Pram*/
#define _DMA_PINC_OFFSET			16
#define DMA_PINC_ENABLE				(1 + _DMA_PINC_OFFSET)
#define DMA_PINC_DISABLE			(0 + _DMA_PINC_OFFSET)

/*Cases of DMA_DIR Pram*/
#define _DMA_DIR_OFFSET				18
#define DMA_DIR_M					(1 + _DMA_DIR_OFFSET)
#define DMA_DIR_P					(0 + _DMA_DIR_OFFSET)

/*</Functions' Parameters>*/



void DMA1_Init(char Ch, char M2M, char CIRCULAR, char PRIORITY, char MSIZE, char PSIZE, char MINC, char PINC, char DIR);
void DMA1_Init_Adv(char Ch, char Num_Of_Args, ...);
void DMA1_SetAddresses(char Ch, uint32_t CPAR, uint32_t CMAR, uint32_t size);
void DMA1_Enable(char Ch);

#endif /* DMA_H_ */
