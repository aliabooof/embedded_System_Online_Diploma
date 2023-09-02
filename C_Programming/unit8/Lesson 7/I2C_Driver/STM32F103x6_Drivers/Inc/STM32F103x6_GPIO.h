/*
 * STM32F103C6_GPIO.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */

#ifndef INC_STM32F103X6_GPIO_H_
#define INC_STM32F103X6_GPIO_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

//Config Structure
typedef struct
{
	volatile uint16_t GPIO_PinNumber;//Specifies the GPIOx Pins to be Configured
								 	 //This Parameter must be set based on @ref GPIO_PINS_Define
	volatile uint8_t GPIO_PinMode;  //Specifies the Operation Mode for The Selected Pins
									 //This Parameter can be value of @ref GPIO_MODE_Define
	volatile uint8_t GPIO_Output_Speed; //Specifies the Speed of The Selected Pins That in Output MODE
									 //This Parameter must be selected based on @ref GPIO_Speed_Define
}GPIO_PINConfig_t;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref GPIO_PIN_state
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

//@ref GPIO_PIN_LOCK_State
#define GPIO_RETURN_LOCK_EN			1
#define GPIO_RETURN_LOCK_ERROR		0

//@ref GPIO_PINS_Define
#define GPIO_PIN_0			 ((uint16_t)0X0001u) // Pin 0 Selected
#define GPIO_PIN_1			 ((uint16_t)0X0002u) // Pin 1 Selected
#define GPIO_PIN_2			 ((uint16_t)0X0004u)// Pin 2 Selected
#define GPIO_PIN_3			 ((uint16_t)0X0008u) // Pin 3 Selected
#define GPIO_PIN_4			 ((uint16_t)0X0010u) // Pin 4 Selected
#define GPIO_PIN_5			 ((uint16_t)0X0020u) // Pin 5 Selected
#define GPIO_PIN_6			 ((uint16_t)0X0040u) // Pin 6 Selected
#define GPIO_PIN_7			 ((uint16_t)0X0080u) // Pin 7 Selected
#define GPIO_PIN_8			 ((uint16_t)0X0100u) // Pin 8 Selected
#define GPIO_PIN_9			 ((uint16_t)0X0200u) // Pin 9 Selected
#define GPIO_PIN_10			 ((uint16_t)0X0400u) // Pin 10 Selected
#define GPIO_PIN_11			 ((uint16_t)0X0800u) // Pin 11 Selected
#define GPIO_PIN_12			 ((uint16_t)0X1000u) // Pin 12 Selected
#define GPIO_PIN_13			 ((uint16_t)0X2000u) // Pin 13 Selected
#define GPIO_PIN_14			 ((uint16_t)0X4000u) // Pin 14 Selected
#define GPIO_PIN_15			 ((uint16_t)0X8000u) // Pin 15 Selected
#define GPIO_PIN_ALL	     ((uint16_t)0XFFFFu) // All Pins Selected

#define GPIO_PIN_MASK		 0X0000FFFFu // PIN mask for assert test

//----------------------
//@ref GPIO_MODE_Define
//----------------------
//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function Input
#define GPIO_MODE_Analog				0x00000000u //Analog mode
#define GPIO_MODE_Input_FLO				0x00000001u //Floating input (reset state)
#define GPIO_MODE_Input_PU				0x00000002u //Input with pull-up
#define GPIO_MODE_Input_PD				0x00000003u //Input with pull-down
#define GPIO_MODE_Output_PP				0x00000004u //output push-pull
#define GPIO_MODE_Output_OD				0x00000005u //output Open-drain
#define GPIO_MODE_Output_AF_PP			0x00000006u //Alternate function output Push-pull
#define GPIO_MODE_Output_AF_OD			0x00000007u //Alternate function output Open-drain
#define GPIO_MODE_AF_Input				0x00000008u //Alternate function Input

//----------------------
//@ref GPIO_Speed_Define
//----------------------
//1: Output mode, max speed 10 MHz.
//2: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz
#define GPIO_MAX_Speed_10M				0x000000001u // Output mode, max speed 10 MHz.
#define GPIO_MAX_Speed_2M				0x000000002u // Output mode, max speed 2 MHz.
#define GPIO_MAX_Speed_50M 				0x000000003u // Output mode, max speed 50 MHz.
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_PINConfig_t *PinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx ,  uint16_t PinNumber , uint8_t Value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx , uint16_t Value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , uint16_t PinNumber);


uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx , uint16_t PinNumber);
void MCAL_GPIO_SET_Pin(GPIO_TypeDef *GPIOx, uint16_t Pin_number, uint8_t mode, uint8_t speed);
#endif /* INC_STM32F103X6_GPIO_H_ */
