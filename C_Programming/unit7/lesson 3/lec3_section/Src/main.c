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

#include "stm32_f103c6_Driver.h"
#include "stm32_f103x6.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "TIM.h"

#define ZERO 0x01
#define ONE 0x79
#define TWO 0x24
#define THREE 0x30
#define FOUR 0x4C
#define FIVE 0x12
#define SIX 0x02
#define SEVEN 0x19
#define EIGHT 0x00
#define NINE 0x10

void clock_init() {
	RCC->CFGR |= (5<<11);
	RCC_TIM1_CLK_EN();
	//Enable clock GPIOA
	RCC_GPIOA_CLK_EN();
	//Enable clock GPIOB Bit 3 IOPBEN: IO port B clock enable
	RCC_GPIOB_CLK_EN();
}
/*void GPIO_init() {

	GPIO_PIN_Config_t PinCfg;

	//PA1 input HighZ Floating input (reset state)
	//	PinCfg.GPIO_PinNumber = GPIO_PIN_1;
	//	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	//	MCAL_GPIO_Init(GPIOA, &PinCfg);

	//PB1 (output PUSH pull Mode)
	//01: Output mode, max speed 10 MHz.
	//CNF 00: General purpose output push-pull
	PinCfg.GPIO_PinNumber = GPIO_PIN_9;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_10;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_11;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_12;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

	PinCfg.GPIO_PinNumber = GPIO_PIN_13;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);


	//============================

	//PA13 input HighZ Floating input (reset state)
	PinCfg.GPIO_PinNumber = GPIO_PIN_14;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);


	//PB13 (output PUSH pull Mode)
	PinCfg.GPIO_PinNumber = GPIO_PIN_15;
	PinCfg.GPIO_PinMode = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &PinCfg);

}*/
GPIO_PIN_Config_t* PinCfg ;

int main(void) {
//	int i;
	/*clock_init();
	LCD_INIT();
	unsigned char key_pressed;
	LCD_WRITE_STRING("HEY,  DEVELOPED BY ENG-->ALI");
	delay_ms(30);
	LCD_clearscreen();
	GPIO_init();
	unsigned char LCD_DISPLAY [11] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
	unsigned char DISPLAY [11] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO};
	for (unsigned char i = 0; i < 11; i++) {
		LCD_WRITE_CHAR(LCD_DISPLAY[i]);
		MCAL_GPIO_WritePort(GPIOB, DISPLAY[i] << 9);  write data on to the LED port
		delay_ms(100);
		 wait for 1 second
	}
	//	MCAL_GPIO_WritePort(GPIOB, 0xDE);
	//	delay_ms(100);
	LCD_clearscreen();
	LCD_WRITE_STRING("Keypad is ready");
	KEYPAD_INIT();
	delay_ms(30);
	LCD_clearscreen();


	while (1) {

		key_pressed = KEYPAD_GETCHAR();
		switch (key_pressed) {
		case 'A':
			break;
		case '?':
			LCD_clearscreen();
			break;
		default:
			LCD_WRITE_CHAR(key_pressed);
			break;
		}

	}*/
	clock_init();
	PinCfg->GPIO_PinNumber=GPIO_PIN_13;
	PinCfg->GPIO_PinMode= GPIO_MODE_OUTPUT_PP;
	PinCfg->GPIO_OUTPUT_SPEED=GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, PinCfg);


	while(1){
		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		delay(1000);

		MCAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);


	}
}

