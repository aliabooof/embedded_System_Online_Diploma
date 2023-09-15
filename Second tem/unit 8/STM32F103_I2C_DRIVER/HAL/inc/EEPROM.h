/*
 * EEPROM.h
 *
 *  Created on: Sep 15, 2023
 *      Author: aliab
 */

#ifndef EEPROM_H_
#define EEPROM_H_


//-----------------------------
//Includes
//-----------------------------
#include "../../STM32F103_DRIVERS/inc/STM32_F103C6_I2C_DRIVER.h"

//EEPROM is an I2C slave device
//Idle mode: device is in high-impedance state and waits for data
//Master transmitter mode: the device transmits data to a slave device
//Master receiver mode: the device receives data from a slave transmitter


//-------------------------------------------------------------------
//==========================Generic Macros==========================
//-------------------------------------------------------------------
#define EEPROM_SLAVE_ADDRESS 				0x2A


//------------------------------------------------------------------------------------------
//								APIs supported by "HAL EEPROM Device"
//------------------------------------------------------------------------------------------
void eeprom_init(void);
unsigned char eeprom_write_nBytes(unsigned int memory_adderss,unsigned char * data, uint8_t dataLen);
unsigned char eeprom_read_nBytes(unsigned int memory_adderss,uint8_t * data, uint8_t dataLen);

#endif /* EEPROM_H_ */
