/*
 * STM32F103C6_GPIO.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */
#include "STM32F103x6.h"
#include "STM32F103x6_GPIO.h"

uint8_t GET_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	// CRL Register
	case GPIO_PIN_0 :
		return 0;
		break;
	case GPIO_PIN_1 :
		return 4;
		break;
	case GPIO_PIN_2 :
		return 8;
		break;
	case GPIO_PIN_3 :
		return 12;
		break;
	case GPIO_PIN_4 :
		return 16;
		break;
	case GPIO_PIN_5 :
		return 20;
		break;
	case GPIO_PIN_6 :
		return 24;
		break;
	case GPIO_PIN_7 :
		return 28;
		break;
		// CRH Register
	case GPIO_PIN_8 :
		return 0;
		break;
	case GPIO_PIN_9 :
		return 4;
		break;
	case GPIO_PIN_10 :
		return 8;
		break;
	case GPIO_PIN_11 :
		return 12;
		break;
	case GPIO_PIN_12 :
		return 16;
		break;
	case GPIO_PIN_13 :
		return 20;
		break;
	case GPIO_PIN_14 :
		return 24;
		break;
	case GPIO_PIN_15 :
		return 28;
		break;
	}
	return 0;
}

/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initialize GPIOx PINy according to the specified parameters in PinConfig
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @param [in]   -PinConfig : pointer to GPIO_PinConfig_t Structure that Contains
 * 				 the configuration information for the specified GPIO PIN.
 * @retval		-none
 * Note			-STM32F103C6 MCU have GPIO A,B,C,D,E Modules
 * 				 But LQFP48 package has A,B,PART Part of C/D exported as external PINS from the Modules
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx , GPIO_PINConfig_t *PinConfig)
{
	//Port configuration register low (GPIOx_CRL) Configure PINS from Pin 0 ---> 7
	//Port configuration register high (GPIOx_CRH)Configure PINS from Pin 8 ---> 15
	volatile uint32_t* Config_Register = NULL;
	uint8_t Pin_Config = 0;
	Config_Register = (PinConfig->GPIO_PinNumber < GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH ;

	// Clear CNFx[1:0] MODEx[1:0] where x is Number of Pin from (0 ---> 15)
	(*Config_Register) &= ~(0xF << GET_CRLH_Position(PinConfig->GPIO_PinNumber) );

	// if Pin is Output
	if((PinConfig->GPIO_PinMode == GPIO_MODE_Output_PP) || (PinConfig->GPIO_PinMode == GPIO_MODE_Output_OD) || (PinConfig->GPIO_PinMode == GPIO_MODE_Output_AF_PP) || (PinConfig->GPIO_PinMode == GPIO_MODE_Output_AF_OD))
	{
		Pin_Config = ( (((PinConfig->GPIO_PinMode - 4 ) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0F );
	}
	// if Pin is Intput
	else
	{
		if((PinConfig->GPIO_PinMode == GPIO_MODE_Analog) || (PinConfig->GPIO_PinMode == GPIO_MODE_Input_FLO))
		{

			Pin_Config = (( (PinConfig->GPIO_PinMode << 2) | 0x0 ) & 0x0F );
		}
		else if(PinConfig->GPIO_PinMode == GPIO_MODE_AF_Input) //if Pin is AF Input
		{
			Pin_Config = (( (GPIO_MODE_Input_FLO << 2) | 0x0 ) & 0x0F); //Consider if as Floating Input
		}
		else // PU Or PD Input
		{
			Pin_Config = (( (GPIO_MODE_Input_PU << 2) | 0x0 ) & 0x0F);

			if(PinConfig->GPIO_PinMode == GPIO_MODE_Input_PU)
			{
				//PxODR = 1 Input Pull_UP :Table 20. Port bit configuration table
				GPIOx->ODR |= (PinConfig->GPIO_PinNumber);
			}
			else
			{
				//PxODR = 0 Input Pull_Down :Table 20. Port bit configuration table
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}
	}
	// Set CNFx[1:0] MODEx[1:0] where x is Number of Pin from (0 ---> 15)
	(*Config_Register) |= (Pin_Config << (GET_CRLH_Position(PinConfig->GPIO_PinNumber)) );
}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Reset GPIOx
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @retval		-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	// If MCU Dosen't Have Reset Controller
	//	GPIOx->CRL =  0x44444444;
	//	GPIOx->CRH =  0x44444444;
	//	 //GPIOx->IDR; (Read Only)
	//	GPIOx->ODR  =  0x00000000;
	//	GPIOx->BSRR =  0x00000000;
	//	GPIOx->BRR =   0x00000000;
	//	GPIOx->LCKR =  0x00000000;
	//Or you can use Reset Controller
	//APB2 peripheral reset register (APB2RSTR)
	//Set and cleared by software
	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR &= ~(1<<2); // Bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR |= (1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB2RSTR &= ~(1<<3); // Bit 3 IOPBRST: IO port B reset
		RCC->APB2RSTR |= (1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR &= ~(1<<4); // Bit 4 IOPCRST: IO port C reset
		RCC->APB2RSTR |= (1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR &= ~(1<<5); // Bit 5 IOPDRST: IO port D reset
		RCC->APB2RSTR |= (1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR &= ~(1<<6); // Bit 6 IOPERST: IO port E reset
		RCC->APB2RSTR |= (1<<6);
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read Specific PIN Value
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @param [in]   -PinNumber : Specifies The Port bit to Read According  to @ref GPIO_PINS_Define
 * @retval		-The input Pin value (Two Values based on @ref GPIO_PIN_state
 * Note			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx , uint16_t PinNumber)
{
	uint8_t PinStatus;
	if( ((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		PinStatus = GPIO_PIN_SET;
	}
	else
	{
		PinStatus = GPIO_PIN_RESET;
	}
	return PinStatus ;
}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read Specific PORT Value
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @retval		-The input PORT value
 * Note			-none
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t Port_Value;
	Port_Value = (uint16_t)(GPIOx->IDR);
	return Port_Value ;
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write Specific PIN Value
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @param [in]   -PinNumber :  Specifies The Port bit to Write According  to @ref GPIO_PINS_Define
 * @param [in]   -Value : Pin Value
 * @retval		-none
 * Note			-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx , uint16_t PinNumber , uint8_t Value)
{
	if(Value != GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= PinNumber;
		//Or
		//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		//GPIOx->ODR &= ~PinNumber;
		//Or
		//		Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber;
	}
}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Write Specific PORT Value
 * @param [in]   -GPIOx : were x can be (A...G depending on device used)to select the GPIO Peripheral
 * @param [in]   -Value : Port Value
 * @retval		-none
 * Note			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx , uint16_t Value)
{
	GPIOx->ODR = (uint32_t)Value;
}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-Toggle Specific PIN Value
 * @param [in]   -GPIOx : were x can be (A...E depending on device used)to select the GPIO Peripheral
 * @param [in]   -PinNumber : Specifies The Port bit to Toggle According  to @ref GPIO_PINS_Define
 * @retval		-Result of Locking The Pin (OK --> Locking pin Success , Error --> Locking pin Failed)
 * 				 According to @ref GPIO_PIN_LOCK_State
 * Note			-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx , uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}

/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-Lock Specific PIN
 * @param [in]   -GPIOx : were x can be (A...E depending on device used)to select the GPIO Peripheral
 * @param [in]   -PinNumber : Specifies The Port bit to be Locked According  to @ref GPIO_PINS_Define
 * @retval		-Ok if pin Config locked Or ERROR if pin Config not locked (OK & ERROR are defined @ref GPIO_PIN_LOCK_State)
 * Note			-none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx , uint16_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1

	// Set LCKK[16]
	volatile uint32_t tmp = (1<<16); // 0b0001 0000 0000 0000 0000 (Set Pin 16)
	// Set the LCKy : where  y=(0 --> 15)
	tmp |= PinNumber; 		// 0b0001 0000 0000 0001 0000 (Set Pin(PinNumber) to be Locked)
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Write 0
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = tmp;
	//	Read 0
	tmp = GPIOx->LCKR;
	//	Read 1
	if( (uint32_t) (GPIOx->LCKR & (1<<16)) ) //Read Pin 16 Or use this>>>> if( (uint32_t)(GPIOx->LCKR >>16) & 1)
	{
		return GPIO_RETURN_LOCK_EN;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}
}
void MCAL_GPIO_SET_Pin(GPIO_TypeDef *GPIOx, uint16_t Pin_number, uint8_t mode, uint8_t speed)
{
	GPIO_PINConfig_t PinConfig;
    PinConfig.GPIO_PinNumber = Pin_number;
    PinConfig.GPIO_PinMode = mode;
    PinConfig.GPIO_Output_Speed = speed;
    MCAL_GPIO_Init(GPIOx, &PinConfig);
}
