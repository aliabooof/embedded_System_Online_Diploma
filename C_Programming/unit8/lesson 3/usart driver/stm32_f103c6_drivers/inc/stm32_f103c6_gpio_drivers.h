/*
 * stm32_f103c6_Driver.h
 *
 *  Created on: Dec 22, 2022
 *      Author: aliab
 */

#ifndef INC_STM32_F103C6_DRIVER_H_
#define INC_STM32_F103C6_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103x6.h"

//=========================================================================


//Configuration structure
typedef struct {
	uint16_t GPIO_pinNumber; /*Specifies the GPIO pins to be configured
	 	 	 	 	 	 	   this parameter can be a  value of @ref GPIO_PINS_DEFINE*/

	uint8_t GPIO_mode;		/*Specifies the operating mode for the selected pins
	 	 	 	 	 	 	   this parameter can be a  value of @ref GPIO_MODE_DEFINE*/

	uint8_t GPIO_output_speed;/*Specifies the speed  for the selected pins
	 	 	 	 	 	 	   this parameter can be a  value of @ref GPIO_SPEED_DEFINE*/
}GPIO_pinConfig_t;


//--------------------------------
//Macros Configuration References
//--------------------------------

//@ref GPIO_PINS_DEFINE
#define GPIO_PIN_0					((uint16_t)0x0001) // Pin 0 with shifting
#define GPIO_PIN_1					((uint16_t)0x0002) // Pin 1 with shifting
#define GPIO_PIN_2					((uint16_t)0x0004) // Pin 2 with shifting
#define GPIO_PIN_3					((uint16_t)0x0008) // Pin 3 with shifting
#define GPIO_PIN_4					((uint16_t)0x0010) // Pin 4 with shifting
#define GPIO_PIN_5					((uint16_t)0x0020) // Pin 5 with shifting
#define GPIO_PIN_6					((uint16_t)0x0040) // Pin 6 with shifting
#define GPIO_PIN_7					((uint16_t)0x0080) // Pin 7 with shifting
#define GPIO_PIN_8					((uint16_t)0x0100) // Pin 8 with shifting
#define GPIO_PIN_9					((uint16_t)0x0200) // Pin 9 with shifting
#define GPIO_PIN_10					((uint16_t)0x0400) // Pin 10 with shifting
#define GPIO_PIN_11					((uint16_t)0x0800) // Pin 11 with shifting
#define GPIO_PIN_12					((uint16_t)0x1000) // Pin 12 with shifting
#define GPIO_PIN_13					((uint16_t)0x2000) // Pin 13 with shifting
#define GPIO_PIN_14					((uint16_t)0x4000) // Pin 14 with shifting
#define GPIO_PIN_15					((uint16_t)0x8000) // Pin 15 with shifting
#define GPIO_PIN_ALL				((uint16_t)0xFFFF) // Selecting all pins with shifting

#define GPIO_PIN_MASK				(0x0000FFFFu) // PIN mask for assert test

//@ref GPIO_MODE_DEFINE

/*
0: Analog mode
1: Floating input (reset state)
2: Input with pull-up
3: Input with pull-down
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8: Alternate function input*/

#define GPIO_MODE_ANALOG							0x00000000u //Analog mode
#define GPIO_MODE_INPUT_FLO							0x00000001u //Floating input
#define GPIO_MODE_INPUT_PU							0x00000002u //Input with pull-up
#define GPIO_MODE_INPUT_PD							0x00000003u //Input with pull-down
#define GPIO_MODE_OUTPUT_PP							0x00000004u //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD							0x00000005u //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP						0x00000006u //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD						0x00000007u //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT							0x00000008u //Alternate function input


// @ref GPIO_SPEED_DEFINE
/*
1: Output mode, max speed 10 MHz.
2: Output mode, max speed 2 MHz.
3: Output mode, max speed 50 MHz.*/

#define GPIO_SPEED_10M		0x00000001u //Output mode, max speed 10 MHz
#define GPIO_SPEED_2M		0x00000002u //Output mode, max speed 2 MHz
#define GPIO_SPEED_50M		0x00000003u //Output mode, max speed 50 MHz


//@ref GPIO_PIN_ state
#define GPIO_PIN_SET			1
#define GPIO_PIN_RESET			0

//@ref GPIO_LOCK_status
#define GPIO_LOCK_ENABLED		1
#define GPIO_LOCK_ERROR			0



//=========================================================================

//------------------------------------------------------------------------------------------
//								APIs supported by "MCAL GPIO Driver"
//------------------------------------------------------------------------------------------'

//Initializations APIs
void MCAL_GPIO_init(GPIO_Typedef * GPIOX, GPIO_pinConfig_t * pinConfig);
void MCAL_GPIO_deInit(GPIO_Typedef * GPIOX);

//Read APIs
uint8_t MCAL_GPIO_readPin(GPIO_Typedef * GPIOX, uint16_t  pinNumber);
uint16_t MCAL_GPIO_readPort(GPIO_Typedef * GPIOX);

//Write APIs
void MCAL_GPIO_writePin(GPIO_Typedef * GPIOX, uint16_t  pinNumber, uint8_t  value);
void MCAL_GPIO_writePort(GPIO_Typedef * GPIOX, uint16_t  value);

//Other APIs
void MCAL_GPIO_togglePin(GPIO_Typedef * GPIOX, uint16_t  pinNumber);

uint8_t MCAL_GPIO_lockPin(GPIO_Typedef * GPIOX, uint16_t  pinNumber);
#endif /* INC_STM32_F103C6_DRIVER_H_ */
