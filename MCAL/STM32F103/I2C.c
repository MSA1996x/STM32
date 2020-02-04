/*
 * I2C.c
 *
 *  Created on: Dec 27, 2019
 *      Author: Mohammed Samir
 */


#include <MCAL/STM32F103/MCAL_H/I2C.h>


void I2C1_Init(char I2C_MODE, char I2C_INTERRUPT){
	/*Configure SCL1 and SDA1 Pins as AF Open Drain*/
	GPIO_Config(GPIOB, PIN_6, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);
	GPIO_Config(GPIOB, PIN_7, MODE_OUTPUT_50MHZ, CONFIG_OUTPUT_AF_OPEN_DRAIN);

	/*Enable Clock For I2C1*/
	I2C1_CLOCK_ENABLE = 1;

	/*Reset I2C1*/
	I2C1_RESET = 1;
	I2C1_RESET = 0;

	/*Make Sure I2C Is Disable While Configuration*/
	I2C1_CR1_PE = 0;

	/*Clean Old FREQ Then Set The New One*/
	I2C1_CR2_REG &= 0xFFC0;
	I2C1_CR2_REG |= 0b100100;//Pram [2:50MHz]


	/*Master Mode Selection*/
	I2C1_CCR_F_S = I2C_MODE == I2C_MODE_SM ? 0 : 1;//Pram [Standard, Fast]

	/*Set Duty Bit*/
	I2C1_CCR_DUTY = I2C_MODE == I2C_MODE_SM ? 0 : 1;//[0=> 1/2  ,1=> 9/16]

	/*
	 * Fast Mode Example (I2C1_CCR_F_S == 1)
	 * T_high = 9 * CCR * T_PCLK1
	 * T_low = 16 * CCR * T_PCLK1
	 *
	 * I2C_Clock_Period = T_high + T_LOW
	 * 					= CCR * T_PCLK1 * (9 + 16)
	 *
	 * -> CCR = I2C_Clock_Period / (25 * T_PCLK1)
	 * 		  = PCLK1 / (25 * I2C_Clock_Freq)
	 *		  = (36000000 / (25 * 400000)
	 *		  = 3.6 -> 3 OR 4
	 * 	  if CCR = 3 -> I2C_Clock_Freq = 480000 > Max Speed of Fast Mode => NOK
	 * 	  if CCR = 4 -> I2C_Clock_Freq = 360000 < Max Speed of Fast Mode => OK
	 *
	 * 	  T_high = (9 * 4)  / 36000000 = 1us    > 0.6us => OK
	 * 	  T_low  = (16 * 4) / 36000000 = 1.78us > 1.3us => OK
	 */
	/*Clean Old CCR The Set The New One*/
	I2C1_CCR_REG &= 0xF000;
	I2C1_CCR_REG |= (I2C_MODE == I2C_MODE_SM ? 180 : 4);

	/*
	 * Rise Time Configuration For Detect Clock Stretching By The Slave
	 * Max For Fast	    Mode Is	300ns
	 * Max For Standard Mode Is 1000ns
	 *
	 * TRISE = Max / T_PCLK1
	 * 		 = 300ns / (1/36000000s)
	 * 		 = 300ns / 27.78ns		 = 10.8
	 * 	if TRISE = 11 => Max = 305.58ns < 300 => NOK
	 * 	if TRISE = 10 => Max = 277.8ns  < 300 => OK
	 */
	/*Clean Old TRISE The Set The New One*/
	I2C1_TRISE_REG &= 0xFFC2;
	I2C1_TRISE_REG |= (I2C_MODE == I2C_MODE_SM ? 36 : 10) + 1;



	/*Enable Stretching*/
	I2C1_CR1_NOSTRETCH = 0;

	/*Enable General Call ACK*/
	I2C1_CR1_ENGC = 1;

	/*Buffer Interrupt Enable/Disable*/
	I2C1_CR2_ITBUFEN = I2C_INTERRUPT - _I2C_INTERRUPT_OFFSET;

	/*Event Interrupt Enable/Disable*/
	I2C1_CR2_ITEVTEN = I2C_INTERRUPT - _I2C_INTERRUPT_OFFSET;

	/*Error Interrupt Enable/Disable*/
	I2C1_CR2_ITERREN = I2C_INTERRUPT - _I2C_INTERRUPT_OFFSET;

	/*Enable I2C*/
	I2C1_CR1_PE = 1;
}

void I2C1_Set_Add7(unsigned char Address){
	I2C1_OAR1_REG = Address<<1;
}


void I2C1_Start_Bit(void){
	/*Send Start Bit*/
	I2C1_CR1_START = 1;

	/*Wait For Start Bit Generation*/
	while(!I2C1_SR1_SB);

	/*Clear Start Bit*/
	(void)I2C1_SR1_REG;
}

char I2C1_Send_SR(void){
	/*Check I2C Mode*/
	if(I2C1_SR2_MSL)
		/*If Master Then Send Start Repeat*/
		I2C1_Start_Bit();
	else
		/*Return Failed*/
		return 0;
	/*Return Success*/
	return 1;
}

char I2C1_Send_Address7(unsigned char Address7, char I2C_DIR, char TimeOut_us){
	/*Counts The Number Of us*/
	unsigned int Counter = 0;

	/*Set DR Register With The Address & R/W Bit To Be Sent*/
	I2C1_DR_REG = (Address7<<1) | (I2C_DIR - _I2C_DIR_OFFSET);

	/*Configure TMR2 For TimeOut*/
	TMR2_Conifg(1);
	/*Reset The Counter*/
	TMR2_Val_Reset();
	/*Start TMR2*/
	TMR2_Start();

	/*Wait For ACK To Be Received Or TimeOut*/
	while(!I2C1_SR1_ADDR){
		if(CNT_US <= TMR2_Val() || TimeOut_us == 0){
			TMR2_Val_Reset();
			if(++Counter >= TimeOut_us){
				/*Stop Counting*/
				TMR2_Stop();
				/*Return Failed*/
				return 0;
			}
		}
	}

	/*Clear ADDR Bit*/
	(void)I2C1_SR1_REG;
	(void)I2C1_SR2_REG;

	/*Return Success*/
	return 1;
}

void I2C1_Send_Data(unsigned char Data){
	/*Wait For DR Empty*/
	while(!I2C1_SR1_TxE);
	/*Set DR Register With The Data To Be Sent*/
	I2C1_DR_REG = Data;
}

void I2C1_Send_ACK(void){
	/*Send ACK For Receive More Then One Byte From The Slave*/
	I2C1_CR1_ACK = 1;
}


void I2C1_Send_NACK(void){
	/*Send ACK Bit*/
	I2C1_CR1_ACK = 0;
}

void I2C1_Send_Stop(void){
	/*Send STOP Bit*/
	I2C1_CR1_STOP = 1;
}

char I2C1_Read(unsigned char Address7, unsigned char* Buf, char Num, char TimeOut_us){

	/*Send ACK When Reading More Then One Byte*/
	if(Num > 1)
		I2C1_Send_ACK();
	else
		I2C1_Send_NACK();

	I2C1_Send_Address7(Address7, I2C_DIR_READ, TimeOut_us);

	/*Configure TMR2 For TimeOut*/
	TMR2_Conifg(1);

	for(int i = 0; i < Num; i++){

		/*Counts The Number Of us*/
		unsigned int Counter = 0;
		/*Reset The Counter*/
		TMR2_Val_Reset();
		/*Start TMR2*/
		TMR2_Start();

		/*Wait For Byte Receiving Or TimeOut*/
		while(!I2C1_SR1_RxNE){
			if(CNT_US <= TMR2_Val()){
				TMR2_Val_Reset();
				if(++Counter >= 50){
					/*Send Stop Bit*/
					I2C1_CR1_STOP = 1;
					/*Stop Counting*/
					TMR2_Stop();
					/*Return Failed*/
					return 0;
				}
			}
		}

		/*Read Data Received*/
		Buf[i] = I2C1_DR_REG;

		/*Send NACK Before Reading The Last Byte*/
		if(i == Num - 2){
			/*Send NACK*/
			I2C1_Send_NACK();
			/*Send Stop Bit*/
			I2C1_CR1_STOP = 1;
		}
	}


	/*Return Success*/
	return 1;
}
