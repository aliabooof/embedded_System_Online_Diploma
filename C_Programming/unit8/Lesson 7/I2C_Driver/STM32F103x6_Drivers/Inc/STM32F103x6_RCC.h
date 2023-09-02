/*
 * STM32F103C6_GPIO.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */

#ifndef INC_STM32F103X6_RCC_H_
#define INC_STM32F103X6_RCC_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103x6_GPIO.h"

#define HSI_RC_CLK 		(uint32_t)8000000
#define HSE_CLK			(uint32_t)16000000

uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_Get_HCLKFreq(void);
uint32_t MCAL_RCC_Get_PCLK1Freq(void);
uint32_t MCAL_RCC_Get_PCLK2Freq(void);


#endif /* INC_STM32F103X6_RCC_H_ */
