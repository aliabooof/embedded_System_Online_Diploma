/*
 * KEYPAD.h
 *
 *  Created on: Feb 5, 2023
 *      Author: aliab
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32_f103c6_gpio_drivers.h"
#include "stm32f103x6.h"
#include <stdlib.h>
#include <stdint.h>


// Keypad Information
#define R0 			GPIO_PIN_0
#define R1 			GPIO_PIN_1
#define R2 			GPIO_PIN_3
#define R3 			GPIO_PIN_4
#define C0 			GPIO_PIN_5
#define C1 			GPIO_PIN_6
#define C2 			GPIO_PIN_7
#define C3 			GPIO_PIN_8

//Keypad PORT
#define keypadPORT	GPIOB


//Functions APIs
void KEYPAD_INIT();
char KEYPAD_GET_CHAR();

#endif /* INC_KEYPAD_H_ */
