/*
 * CAN.c
 *
 *  Created on: Jan 12, 2020
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/CAN.h>
#include <MCAL/STM32F103/MCAL_H/MemoryMap.h>

void CAN1_Init(void){
	/*Configure TX and RX Pins as AF Push Pull*/
	GPIO_Config(GPIOA, 11, MODE_INPUT, CONFIG_INPUT_FLOATING);
	GPIO_Config(GPIOA, 12, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);

	/*Enable Clock For CAN1*/
	CAN1_CLOCK_ENABLE = 1;

	/*Reset CAN1*/
	CAN1_RESET = 1;
	CAN1_RESET = 0;
	CAN1_MCR_RESET = 1;

	/*Set Automatic Bus-OFF Management*/
	CAN1_MCR_ABOM = 1;

	/*Set Transmit FIFO priority*/
	CAN1_MCR_TXFP = 1;

	/*Initialization Request*/
	CAN1_MCR_INRQ = 1;

	/*Sleep Mode Request*/
	CAN1_MCR_SLEEP = 0;

	/*Waiting For Initialization Mode*/
	while(CAN1_MSR_SLAK || !CAN1_MSR_INAK);

	/* Configure CAN Bit Timing Register
	* BaudRate = 1 Mbps, BRP[9:0] = 1, TS1[3:0] = 14, TS2[2:0] = 1, SJW[1:0] = 0
	* tq = (BRP[9:0] + 1) x tPCLK = (1 + 1) * (1/36)   = 0.0555 us
	* tBS1 = tq x (TS1[3:0] + 1)  = 0.0555  * (14 + 1) = 0.8325 us
	* tBS2 = tq x (TS2[2:0] + 1)  = 0.0555  * (1 + 1)  = 0.1110 us
	* NominalBitTime = 1 × tq + tBS1 + tBS2 = 0.0555 + 0.8325 + 0.1110 = 0.9990 (1) us
	* BaudRate = 1 / NominalBitTime = 1 MBits/s
	*/
	CAN1_BTR_REG = 0x001E0001;

	/*Normal Mode Request*/
	CAN1_MCR_SLEEP = 0;
	CAN1_MCR_INRQ  = 0;
}

void CAN1_Filter(char Filte_Num, char FLTR_MODE, char FLTR_SCALE, char FLTR_FIFO, uint32_t FiR1, uint32_t FiR2){
	/*Set Filter Init Mode*/
	CAN1_FMR_FINIT = 1;

	/*Set Filter Mode*/
	CAN1_FM1R_FBMx(Filte_Num) = FLTR_MODE - _FLTR_MODE_OFFSET;

	/*Set Filter Scale*/
	CAN1_FS1R_FSCx(Filte_Num) = FLTR_SCALE - _FLTR_SCALE_OFFSET;

	/*Set Filter FIFO*/
	CAN1_FFA1R_FFAx(Filte_Num) = FLTR_FIFO - _FLTR_FIFO_OFFSET;

	/*Set Filters Values*/
	CAN1_FiRx_REG(Filte_Num, 1) = FiR1;
	CAN1_FiRx_REG(Filte_Num, 2) = FiR2;

	/*Activate The Filter*/
	CAN1_FA1R_FACTx(Filte_Num) = 1;

	/*Active Filter Mode*/
	CAN1_FMR_FINIT = 0;
}

void CAN1_Transmit(uint16_t ID, char ID_MODE, char FRAME_MODE, char MAILBOX, char* Data){
	/*Get MailBox Real Number*/
	MAILBOX -= _MAILBOX_OFFSET;

	/*Check if Mailbox Empty*/
	if(CAN1_TSR_TMEx(MAILBOX)){
		/*To Calculate Data Length*/
		uint8_t Length;

		/*Select Identifier Mode*/
		CAN1_TIxR_IDE(MAILBOX) 	= ID_MODE - _ID_MODE_OFFSET;

		/*Select Frame Mode*/
		CAN1_TIxR_RTR(MAILBOX) 	= FRAME_MODE - _FRAME_MODE_OFFSET;

		/*Set ID.*/
		CAN1_TIxR_REG(MAILBOX)  = (CAN1_TIxR_REG(MAILBOX) & 0x001FFFFF) | (ID<<21);

		/*Reset Data Registers*/
		CAN1_TDLxR_REG(MAILBOX) = 0;
		CAN1_TDHxR_REG(MAILBOX) = 0;

		/*Set Data (Max 8 Bytes)*/
		for(Length = 0;*Data != '\0' && Length < 8; Length++)
			if(Length < 4)
				CAN1_TDLxR_REG(MAILBOX) |= (*(Data++))<<(Length * 8);
			else
				CAN1_TDHxR_REG(MAILBOX) |= (*(Data++))<<((Length - 4) * 8);

		/*Set Data Length.*/
		CAN1_TDTxR_REG(MAILBOX) = (CAN1_TDTxR_REG(MAILBOX) & 0xFFFFFFF0) | Length;

		/*Transmission Request*/
		CAN1_TIxR_TXRQ(MAILBOX) = 1;
	}
}

char CAN1_Receive(char FIFO_NUM, char* Data, uint8_t *DLC, uint8_t *FilterIndex){
	/*Check FIFO Message Pending*/
	if(((CAN1_RFxR_REG(FIFO_NUM - _FIFO_NUM_OFFSET)) & 0x03) != 0){


		/*Get Message's DLC*/
		*DLC = CAN1_RDT0R_REG & 0x0F;

		/*Get Message's Filter Index*/
		*FilterIndex = (CAN1_RDT0R_REG>>8) & 0xFF;

		/*Get Message's Data*/
		for(int i = 0; i < *DLC; i++)
			if(i < 4)
				Data[i] = (CAN1_RDL0R_REG>>(i * 8)) & 0xFF;
			else
				Data[i] = (CAN1_RDH0R_REG>>((i - 4) * 8)) & 0xFF;

		/*Release FIFO For The Next Message*/
		CAN1_RF0R_RFOM0 = 1;

		return REC_SUCCESS;
	}
	return REC_FAIL;
}
