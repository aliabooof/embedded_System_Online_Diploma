/*
 * stm32_f103c6_RCC_driver.h
 *
 *      Author: aliab
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_


#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"


#define HSI_RC_CLK 			(uint32_t)8000000  //Fixed number refer to data sheet if you want verify
#define HSE_CLK				(uint32_t)16000000 //User must input it since it came from external source

//------------------------------------------------------------------------------------------
//								APIs supported by "MCAL RCC Driver"
//------------------------------------------------------------------------------------------

uint32_t MCAL_RCC_getSYSCLKFreq(void);
uint32_t MCAL_RCC_getHCLKFreq(void);
uint32_t MCAL_RCC_getPCLK1Freq(void);
uint32_t MCAL_RCC_getPCLK2Freq(void);

#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
