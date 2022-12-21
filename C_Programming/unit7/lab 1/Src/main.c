/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

#include "MemMap.h"


void clock_init(){


	//enable clock for GPIOA
	//	Bit 2 IOPAEN: I/O port A clock enable
	//	Set and cleared by software.
	//	0: I/O port A clock disabled
	//	1:I/O port A clock enabled

	RCC_APB2ENR |= (1<<2);

	//enable clock for GPIOB
	//	Bit 3 IOPBEN: I/O port B clock enable
	//	Set and cleared by software.
	//	0: I/O port B clock disabled
	//	1:I/O port B clock enabled

	RCC_APB2ENR |=(1<<3);
}

void GPIO_init(){

	//clearing GPIO registers
	GPIOA_CRL = 0;
	GPIOA_CRH = 0;
	GPIOA_ODR = 0;


	//	CNFy[1:0]: Port x configuration bits (y= 0 .. 7)
	//	These bits are written by software to configure the corresponding I/O port.
	//	Refer to Table 20: Port bit configuration table.
	//	In input mode (MODE[1:0]=00):
	//	00: Analog mode
	//	01: Floating input (reset state)
	//	10: Input with pull-up / pull-down
	//	11: Reserved

	//	In output mode (MODE[1:0] > 00):
	//	00: General purpose output push-pull
	//	01: General purpose output Open-drain
	//	10: Alternate function output Push-pull
	//	11: Alternate function output Open-drain

	//	MODEy[1:0]: Port x mode bits (y= 0 .. 7)
	//	These bits are written by software to configure the corresponding I/O port.
	//	Refer to Table 20: Port bit configuration table.
	//	00: Input mode (reset state)
	//	01: Output mode, max speed 10 MHz.
	//	10: Output mode, max speed 2 MHz.
	//	11: Output mode, max speed 50 MHz


	//configure PORT A pin 1 as floating input
	GPIOA_CRL &= ~(0b11<<4);
	GPIOA_CRL |= (0b01<<6);

	//configure PORTA pin 13 as floating input
	GPIOA_CRH &= ~(0b11<<20);
	GPIOA_CRH |= (0b01<<22);

	//configure PORTB pin 1 as output push pull 10MHz
	GPIOB_CRL |= (0b01<<4);
	GPIOB_CRL &= ~(0b11<<6);

	//configure PORTB pin 1 as output push pull 10MHz
	GPIOB_CRH |= (0b01<<20);
	GPIOB_CRH &= ~(0b11<<22);
}

void delay(uint32_t time){
	uint32_t i,j;
	for(i=0;i<=time;i++){
		for(j=0;j<=255;j++);
	}

}

int main(void)
{
	clock_init();

	GPIO_init();

	while(1){
		//check if the button is pressed
		if(((GPIOA_IDR&(1<<1)) >>1) == 0)
		{
			GPIOB_ODR ^= 1<<1;
			while((((GPIOA_IDR &(1<<1)) >>1) == 0)); //single pressing
		}
		if(((GPIOA_IDR&(1<<13)) >>13) == 1)
		{ //multi pressing
			GPIOB_ODR ^= 1<<13;
		}
		delay(1);

	}

}