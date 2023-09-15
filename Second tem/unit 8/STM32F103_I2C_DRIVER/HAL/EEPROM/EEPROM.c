/*
 * EEPROM.c
 *
 *  Created on: Sep 15, 2023
 *      Author: aliab
 */

#include "../inc/EEPROM.h"

void eeprom_init(void){
	//I2C init
	//PB6: I2C1_SCL
	//PB7: I2C1_SDA

	I2C_Config_t config;

	config.General_Call_Address_Detection = I2C_ENGC_Enable;
	config.I2C_ACK_Control = I2C_ACK_Enable;
	config.I2C_ClockSpeed = I2C_SCLK_SM_100K;
	config.I2C_Mode = I2C_Mode_I2C;
	config.P_Slave_Event_CallBack = NULL;
	config.StretchMode = I2C_StretchMode_Enable;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &config);

}

unsigned char eeprom_write_nBytes(unsigned int memory_adderss,unsigned char * data, uint8_t dataLen){

	//Because of how the EEPROM works we need to put the address in which it reads/write first
	uint8_t buffer[256], i;

	buffer[0] = (uint8_t)(memory_adderss >> 8); //Upper byte memory address
	buffer[1] = (uint8_t)(memory_adderss); //Lower byte memory address

	for (i = 2; i < (dataLen + 2); ++i) {
		buffer[i] = data[i - 2];
	}

	MCAL_I2C_Master_TX(I2C1, EEPROM_SLAVE_ADDRESS, buffer, (dataLen + 2), WithStop, Start);

	return 0;
}

unsigned char eeprom_read_nBytes(unsigned int memory_adderss,uint8_t * data, uint8_t dataLen){
	uint8_t buffer[2];

	buffer[0] = (uint8_t)(memory_adderss >> 8); //Upper byte memory address
	buffer[1] = (uint8_t)(memory_adderss); //Lower byte memory address

	MCAL_I2C_Master_TX(I2C1, EEPROM_SLAVE_ADDRESS, buffer, 2, WithoutStop, Start); //Write address only
	MCAL_I2C_Master_RX(I2C1, EEPROM_SLAVE_ADDRESS, data, dataLen, WithStop, RepeatedStart); // Read data

	return 0;
}
