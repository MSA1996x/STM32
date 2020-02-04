/*
 * MemoryMap.h
 *
 *  Created on: Dec 8, 2019
 *      Author: Mohammed Samir
 */

#ifndef MEMORYMAP_H_
#define MEMORYMAP_H_

#include "stm32f10x.h"

#define EXTI_PR_OFFSET	0x14

#define CRL_OFFSET		0x00
#define CRH_OFFSET		0x04
#define IDR_OFFSET 		0x08
#define ODR_OFFSET 		0x0C
#define BRR_OFFSET		0x14



/*<DMA>*/
#define BITBAND_PERI_DMA1(Ch, Reg, Bit)	(*(volatile unsigned int *)((BITBAND_ALIAS_PERI_BASE + ( (DMA1_BASE + Reg + 0x14 * (Ch - 1)) - PERIPH_BASE) * 0x20 + (Bit * 4))))
#define REG_PERI_DMA1(Ch, Reg)			(*(volatile uint32_t *)((DMA1_BASE + Reg + 0x14 * (Ch - 1))))

#define DMA_ISR 		0x00
#define DMA_CCRx 		0x08
#define DMA_CNDTRx 		0x0C
#define DMA_CPARx 		0x10
#define DMA_CMARx 		0x14
/*</DMA>*/


#define USART_SR_OFFSET		0x00
#define USART_DR_OFFSET 	0x04
#define USART_BRR_OFFSET	0x08
#define USART_CR1_OFFSET	0x0C
#define USART_CR2_OFFSET	0x10
#define USART_CR3_OFFSET	0x14


#define TMR1_BASE			0x40012C00
#define TMR2_BASE			0x40000000
#define TMR4_BASE			0x40000800
#define TMR6_BASE			0x40001000



#define TIMx_CR1			0x00
#define TIMx_CR2			0x04
#define TIMx_SMCR			0x08
#define TIMx_DIER			0x0C
#define TIMx_SR				0x10
#define TIMx_EGR			0x14
#define TIMx_CCMR1			0x18
#define TIMx_CCMR2			0x1C
#define TIMx_CCER			0x20
#define TIMx_CNT			0x24
#define TIMx_PSC			0x28
#define TIMx_ARR			0x2C
#define TIMx_CCR1			0x34
#define TIMx_CCR2			0x38
#define TIMx_CCR3			0x3C
#define TIMx_CCR4			0x40
#define TIMx_DCR			0x48
#define TIMx_DMAR			0x4C




#define SCB_SCR_OFFSET		0x10

#define PWR_CR_OFFSET		0x00
#define PWR_CSR_OFFSET		0x04

#define SPI_CR1_OFFSET		0x00
#define SPI_CR2_OFFSET		0x04
#define SPI_SR_OFFSET		0x08
#define SPI_DR_OFFSET		0x0C
#define SPI_CRCPR_OFFSET	0x10
#define SPI_RXCRCR_OFFSET	0x14
#define SPI_TXCRCR_OFFSET	0x18
#define SPI_I2SCFGR_OFFSET	0x1C
#define SPI_I2SPR_OFFSET	0x20


#define RCC_CFGR_OFFSET		0x04
#define RCC_APB1RSTR_OFFSET	0x10
#define RCC_AHBENR_OFFSET 	0x14
#define RCC_APB1ENR_OFFSET	0x1C
#define RCC_APB2ENR_OFFSET 	0x18
#define RCC_CSR_OFFSET		0x24


/*<ADC>*/
#define ADC_SR_OFFSET 		0x00
#define ADC_CR1_OFFSET 		0x04
#define ADC_CR2_OFFSET 		0x08
#define ADC_SMPR1_OFFSET 	0x0C
#define ADC_SMPR2_OFFSET 	0x10
#define ADC_JOFR1_OFFSET 	0x14
#define ADC_JOFR2_OFFSET 	0x18
#define ADC_JOFR3_OFFSET 	0x1C
#define ADC_JOFR4_OFFSET 	0x20
#define ADC_HTR_OFFSET 		0x24
#define ADC_LTR_OFFSET 		0x28
#define ADC_SQR1_OFFSET 	0x2C
#define ADC_SQR2_OFFSET 	0x30
#define ADC_SQR3_OFFSET 	0x34
#define ADC_JSQR_OFFSET 	0x38
#define ADC_JDR1_OFFSET 	0x3C
#define ADC_JDR2_OFFSET 	0x40
#define ADC_JDR3_OFFSET 	0x44
#define ADC_JDR4_OFFSET 	0x48
#define ADC_DR_OFFSET 		0x4C
/*</ADC>*/


#define DAC_CR_OFFSET 		0x00
#define DAC_SWTRIGR_OFFSET 	0x04
#define DAC_DHR12R1_OFFSET 	0x08
#define DAC_DHR12L1_OFFSET 	0x0C
#define DAC_DHR8R1_OFFSET 	0x10
#define DAC_DHR12R2_OFFSET 	0x14
#define DAC_DHR12L2_OFFSET 	0x18
#define DAC_DHR8R2_OFFSET 	0x1C
#define DAC_DHR12RD_OFFSET 	0x20
#define DAC_DHR12LD_OFFSET 	0x24
#define DAC_DHR8RD_OFFSET 	0x28
#define DAC_DOR1_OFFSET 	0x2C
#define DAC_DOR2_OFFSET 	0x30


/*<I2C>*/
#define I2C_CR1_OFFSET 		0x00
#define I2C_CR2_OFFSET 		0x04
#define I2C_OAR1_OFFSET 	0x08
#define I2C_OAR2_OFFSET 	0x0C
#define I2C_DR_OFFSET 		0x10
#define I2C_SR1_OFFSET 		0x14
#define I2C_SR2_OFFSET 		0x18
#define I2C_CCR_OFFSET 		0x1C
#define I2C_TRISE_OFFSET 	0x20
/*</I2C>*/


/*<CAN>*/
#define CAN_MCR_OFFSET 			0x00
#define CAN_MSR_OFFSET 			0x04
#define CAN_TSR_OFFSET 			0x08
#define CAN_RF0R_OFFSET 		0x0C
#define CAN_RF1R_OFFSET 		0x10
#define CAN_IER_OFFSET 			0x14
#define CAN_ESR_OFFSET 			0x18
#define CAN_BTR_OFFSET 			0x1C
#define CAN_TI0R_OFFSET 		0x180
#define CAN_TDT0R_OFFSET 		0x184
#define CAN_TDL0R_OFFSET 		0x188
#define CAN_TDH0R_OFFSET 		0x18C
#define CAN_TI1R_OFFSET 		0x190
#define CAN_TDT1R_OFFSET 		0x194
#define CAN_TDL1R_OFFSET 		0x198
#define CAN_TDH1R_OFFSET 		0x19C
#define CAN_TI2R_OFFSET 		0x1A0
#define CAN_TDT2R_OFFSET 		0x1A4
#define CAN_TDL2R_OFFSET 		0x1A8
#define CAN_TDH2R_OFFSET 		0x1AC
#define CAN_RI0R_OFFSET 		0x1B0
#define CAN_RDT0R_OFFSET 		0x1B4
#define CAN_RDL0R_OFFSET 		0x1B8
#define CAN_RDH0R_OFFSET 		0x1BC
#define CAN_RI1R_OFFSET 		0x1C0
#define CAN_RDT1R_OFFSET 		0x1C4
#define CAN_RDL1R_OFFSET 		0x1C8
#define CAN_RDH1R_OFFSET 		0x1CC
#define CAN_FMR_OFFSET 			0x200
#define CAN_FM1R_OFFSET 		0x204
#define CAN_FS1R_OFFSET 		0x20C
#define CAN_FFA1R_OFFSET 		0x214
#define CAN_FA1R_OFFSET 		0x21C
#define CAN_F0R1_OFFSET 		0x240
#define CAN_F0R2_OFFSET 		0x244
#define CAN_F1R1_OFFSET 		0x248
#define CAN_F1R2_OFFSET 		0x24C
#define CAN_F2R1_OFFSET 		0x250
#define CAN_F2R2_OFFSET 		0x254
#define CAN_F3R1_OFFSET 		0x258
#define CAN_F3R2_OFFSET 		0x25C
#define CAN_F4R1_OFFSET 		0x260
#define CAN_F4R2_OFFSET 		0x264
/* .
 * .
 * .
 */
#define CAN_F27R1_OFFSET 		0x318
#define CAN_F27R2_OFFSET 		0x31C
/*</CAN>*/



/*<Flash>*/
#define FLASH_REG_BASE			0x40022000
#define FLASH_ACR_OFFSET		0x00
#define FLASH_KEYR_OFFSET		0x04
#define FLASH_OPTKEYR_OFFSET	0x08
#define FLASH_SR_OFFSET			0x0C
#define FLASH_CR_OFFSET			0x10
#define FLASH_AR_OFFSET			0x14
#define FLASH_OBR_OFFSET		0x1C
#define FLASH_WRPR_OFFSET		0x20
/*</Flash>*/


/*<CRC>*/
#define CRC_DR_OFFSET			0x00
#define CRC_IDR_OFFSET			0x04
#define CRC_CR_OFFSET			0x08
/*</CRC>*/


/*<IWDG>*/
#define IWDG_KR_OFFSET			0x00
#define IWDG_PR_OFFSET			0x04
#define IWDG_RLR_OFFSET			0x08
#define IWDG_SR_OFFSET			0x0C
/*</IWDG>*/

/*<WWDG>*/
#define WWDG_CR_OFFSET			0x00
#define WWDG_CFR_OFFSET			0x04
#define WWDG_SR_OFFSET			0x08
/*</WWDG>*/


#define DBGMCU_CR_ADD			0xE0042004

#define BITBAND_ALIAS_PERI_BASE (PERIPH_BASE + 0x02000000)



#define BITBAND_PERI(REG_PERI, PIN_NUM) (*(volatile unsigned int *)((BITBAND_ALIAS_PERI_BASE + ((uint32_t)REG_PERI - PERIPH_BASE) * 0x20 + ((PIN_NUM) * 4))))


#endif
