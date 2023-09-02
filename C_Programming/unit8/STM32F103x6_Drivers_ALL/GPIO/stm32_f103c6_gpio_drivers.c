/*
 * stm32_f103c6_Driver.c
 *
 *  Created on: Dec 22, 2022
 *      Author: aliab
 */

#include "stm32_f103c6_gpio_drivers.h"


/*======================================================================================
* @Fn			-get_CRLH_position
* @brief		-Gets the specific starting bit of each pin
* @param[in]	-PinNumber: which  pin number according @ref
* 				 GPIO PINS_define to get bit
* @retval		-Starting bit
* Note			-None
======================================================================================*/
uint8_t get_CRLH_position(uint16_t pinNumber){
	switch(pinNumber){
	case  GPIO_PIN_0:
		return 0;
		break;

	case  GPIO_PIN_1:
		return 4;
		break;

	case  GPIO_PIN_2:
		return 8;
		break;

	case  GPIO_PIN_3:
		return 12;
		break;

	case  GPIO_PIN_4:
		return 16;
		break;

	case  GPIO_PIN_5:
		return 20;
		break;

	case  GPIO_PIN_6:
		return 24;
		break;

	case  GPIO_PIN_7:
		return 28;
		break;

	case  GPIO_PIN_8:
		return 0;
		break;

	case  GPIO_PIN_9:
		return 4;
		break;

	case  GPIO_PIN_10:
		return 8;
		break;

	case  GPIO_PIN_11:
		return 12;
		break;

	case  GPIO_PIN_12:
		return 16;
		break;

	case  GPIO_PIN_13:
		return 20;
		break;

	case  GPIO_PIN_14:
		return 24;
		break;

	case  GPIO_PIN_15:
		return 28;
		break;
	}


	return 1;
}











/*======================================================================================
* @Fn			-MCAL_GPIO_init
* @brief		-Initializes the GPIOX PINY according to the specified parameters
* 				 in the PinConfig
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-PinConfig pointer to a GPIO_PinConfig_t structure that contains
*				 the configuration information for the specified GPIO PIN.
* @retval		-None
* Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,but LQFP48 Package
* 				 has only GPIO A,B,PART of C/D exported as external PINS from the M
======================================================================================*/
void MCAL_GPIO_init(GPIO_Typedef * GPIOX, GPIO_pinConfig_t * pinConfig){
	volatile uint32_t * configReg = NULL;
	uint8_t pinMode = 0;

	configReg = (pinConfig->GPIO_pinNumber > GPIO_PIN_7) ? &GPIOX->CRH : &GPIOX->CRL;

	*configReg &= ~(0xf << get_CRLH_position(pinConfig->GPIO_pinNumber));

	if((pinConfig->GPIO_mode == GPIO_MODE_OUTPUT_AF_OD) || (pinConfig->GPIO_mode == GPIO_MODE_OUTPUT_AF_PP) ||
	   (pinConfig->GPIO_mode == GPIO_MODE_OUTPUT_OD) || (pinConfig->GPIO_mode == GPIO_MODE_OUTPUT_PP)){

		pinMode = ((((pinConfig->GPIO_mode - 4) << 2) | (pinConfig->GPIO_output_speed)) & 0x0F);


	}else{

		if((pinConfig->GPIO_mode == GPIO_MODE_INPUT_FLO) || (pinConfig->GPIO_mode == GPIO_MODE_ANALOG)){

			pinMode = (((pinConfig->GPIO_mode) << 2) & 0x0F);

		}else if (pinConfig->GPIO_mode == GPIO_MODE_AF_INPUT){

			pinMode = (((GPIO_MODE_INPUT_FLO) << 2) & 0x0F);

		}else{

			pinMode = (((GPIO_MODE_INPUT_PU) << 2) & 0x0F);

			if(pinConfig->GPIO_mode == GPIO_MODE_INPUT_PU){
				GPIOX->ODR |= pinConfig->GPIO_pinNumber;
			}else{
				GPIOX->ODR &= ~(pinConfig->GPIO_pinNumber);
			}

		}
	}

	*configReg |= (pinMode << get_CRLH_position(pinConfig->GPIO_pinNumber));
}


/*======================================================================================
* @Fn			-MCAL_GPIO_deInit
* @brief		-Reset all the GPIO Registers
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @retval		-None
* Note			-None
======================================================================================*/
void MCAL_GPIO_deInit(GPIO_Typedef * GPIOX){

	if(GPIOX == GPIOA){

		RCC->APB2RSTR |= (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);

	}else if (GPIOX == GPIOB){

		RCC->APB2RSTR |= (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);

	}else if (GPIOX == GPIOC){

		RCC->APB2RSTR |= (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);

	}else if (GPIOX == GPIOD){

		RCC->APB2RSTR |= (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);

	}else if (GPIOX == GPIOE){

		RCC->APB2RSTR |= (1 << 6);
		RCC->APB2RSTR &= ~(1 << 6);
	}
}



/*======================================================================================
* @Fn			-MCAL_GPIO_readPin
* @brief		-Read Specific PIN
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-PinNumber: Set Pin Number according @ref GPIO PINS_define
* @retval		-The input pin value (two values based on @ref GPIO_PIN_state)
* Note			-None
======================================================================================*/
uint8_t MCAL_GPIO_readPin(GPIO_Typedef * GPIOX, uint16_t  pinNumber){

	return (((GPIOX->IDR) & pinNumber) != (uint32_t)GPIO_PIN_RESET) ? GPIO_PIN_SET : GPIO_PIN_RESET;

}


/*======================================================================================
* @Fn			-MCAL_GPIO_readPin
* @brief		-Read Specific Port Value
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @retval		-The input Port Value
* Note			-None
======================================================================================*/
uint16_t MCAL_GPIO_readPort(GPIO_Typedef * GPIOX){
	return (uint16_t)(GPIOX->IDR);
}



/*======================================================================================
* @Fn			-MCAL_GPIO_writePin
* @brief		-write on specific input pin
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-PinNumber: specifies the port bit to read. Set by @ref GPIO_PINS_define
* @param[in]	-value: Pin Value
* @retval		-None
* Note			-None
======================================================================================*/
void MCAL_GPIO_writePin(GPIO_Typedef * GPIOX, uint16_t  pinNumber, uint8_t  value){

	if(value != GPIO_PIN_RESET){
		GPIOX->BSRR = (uint32_t) pinNumber;
	}else{
		GPIOX->BRR = (uint32_t) pinNumber;
	}

}





/*======================================================================================
* @Fn			-MCAL_GPIO_writePort
* @brief		-write on output port
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-value: port Value to be written
* @retval		-None
* Note			-None
======================================================================================*/
void MCAL_GPIO_writePort(GPIO_Typedef * GPIOX, uint16_t  value){
	GPIOX->ODR = (uint32_t) value;
}


/*======================================================================================
* @Fn			-MCAL_GPIO_togglePin
* @brief		-Toggles Specific PIN
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-PinNumber: toggle pin number according @ref GPIO_PINS_define
* @retval		-None
* Note			-None
======================================================================================*/
void MCAL_GPIO_togglePin(GPIO_Typedef * GPIOX, uint16_t  pinNumber){
	GPIOX->ODR ^= (uint32_t) pinNumber;
}



/*======================================================================================
* @Fn			-MCAL_GPIO_lockPin
* @brief		-The locking mechanism allows the IO configuration to be frozen
* @param[in]	-GPIOx: where x can be (A. .E depending on device used) to select
* 				 the GPIO peripheral
* @param[in]	-PinNumber: locks pin number according @ref GPIO_PINS_define
* @retval		-Ok if pin Config is locked Or ERROR if pin not locked
* 				 (OK & ERROR are defined @ref GPIO_LOCK_status)
* Note			-None
======================================================================================*/
uint8_t MCAL_GPIO_lockPin(GPIO_Typedef * GPIOX, uint16_t  pinNumber){

	volatile uint32_t bit = 1 << 16;

	bit |= pinNumber;


	GPIOX->LCKR = bit;


	GPIOX->LCKR = pinNumber;


	GPIOX->LCKR = bit;

	bit = GPIOX->LCKR;


	if((uint32_t) (GPIOX->LCKR & 1 << 16)){
		return GPIO_LOCK_ENABLED;
	}else{
		return GPIO_LOCK_ERROR;
	}
}
