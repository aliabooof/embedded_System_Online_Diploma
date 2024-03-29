/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "../STM32F103_DRIVERS/inc/STM32_F103X6.h"
#include "../STM32F103_DRIVERS/inc/STM32_F103C6_GPIO_Driver.h"
#include "../STM32F103_DRIVERS/inc/STM32_F103C6_I2C_DRIVER.h"
#include "../HAL/inc/EEPROM.h"

int main(void)
{
	//Enable Clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	//Test Case1
	uint8_t ch1[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7};
	uint8_t ch2[7] = {0};

	eeprom_init();
	eeprom_write_nBytes(0xAF,ch1, 7);
	eeprom_read_nBytes(0xAF, ch2, 7);

	//Test Case2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	eeprom_write_nBytes(0x0FFF,ch1, 4);
	eeprom_read_nBytes(0x0FFF, ch2, 4);

    while(1)
    {

    }
}












