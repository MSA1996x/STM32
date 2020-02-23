/*
 * LM75A.c
 *
 *  Created on: Dec 29, 2019
 *      Author: Mohammed Samir
 */

#include <HAL/HAL_H/LM75A.h>

char LM75A_Init(unsigned char Address7){
	/*Initialize I2C*/
	I2C1_Init(I2C_MODE_FM, I2C_INTERRUPT_DISABLE);
	/*Send Start Bit*/
	I2C1_Start_Bit();
	/*Write To The Sensor To Check If It Is Ready*/
	char tempReturn = I2C1_Send_Address7(Address7, I2C_DIR_WRITE, 100);
	/*Send Stop Bit*/
	I2C1_Send_Stop();

	/*
	 * 1 => Sensor Ready
	 * 0 => Sensor Not Found
	 */
	return tempReturn;
}


float LM75A_Read_Temp(unsigned char Address7){
	/*For Storing The Received Data*/
	unsigned char Buf[2];
	/*Send Start Bit*/
	I2C1_Start_Bit();
	/*Read Temperature Register*/
	I2C1_Read(Address7, Buf, 2, 100);
	/*Calculate The Temperature The Return It*/
	return (Buf[0] & 0b01111111) * ((Buf[0]>>7) == 1 ? -1 : 1) + ((Buf[1]>>7) * 0.5);
}
