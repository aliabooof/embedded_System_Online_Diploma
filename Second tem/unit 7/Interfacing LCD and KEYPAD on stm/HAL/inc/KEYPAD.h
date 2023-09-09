/*
 * KEYPAD.h
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "../STM32F103_DRIVERS/inc/STM32_F103C6_Driver.h"



#define KEYPAD_PORT GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4

#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8


void KEYPAD_INIT();
char KEYPAD_GETCHAR();

#endif /* INC_KEYPAD_H_ */
