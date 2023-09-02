/*
 * STM32F103C6_GPIO.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */
#include "STM32F103x6_EXTI.h"


//================================================================
//				Generic Variables
//================================================================

void (* GP_IRQ_CallBack[15])(void);

//================================================================
//				Generic Macros
//================================================================

#define AFIO_GPIO_EXTI_Mapping(x)	  ( (x == GPIOA)?0:\
		(x == GPIOB)?1:\
				(x == GPIOC)?2:\
						(x == GPIOD)?3:0 )

//================================================================
//				Generic Functions
//================================================================

// Enable NVIC Interrupt
void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IQR6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IQR7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IQR8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IQR9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IQR10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IQR23_EXTI5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IQR40_EXTI10_15_Enable;
		break;
	}
}
// Enable NVIC Interrupt
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IQR6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IQR7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IQR8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IQR9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IQR10_EXTI4_Disable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IQR23_EXTI5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IQR40_EXTI10_15_Disable;
		break;
	}
}
void EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	//1- Configure GPIO PIN to be  AF Input (Floating Input)
	MCAL_GPIO_SET_Pin(EXTI_Config->EXTI_PIN.GPIO_Port, EXTI_Config->EXTI_PIN.GPIO_Pin, GPIO_MODE_AF_Input, 0);

	//=============================================================
	//2- Update AFIO to Route between EXTI Line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_Index = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber) / 4;
	uint8_t AFIO_EXTICR_BitField_Position = (EXTI_Config->EXTI_PIN.ETI_InputLineNumber % 4) * 4;

	//clear the four it of EXTICR Register
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_BitField_Position);

	//Update  The EXTICR Register
	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTICR_BitField_Position);

	//=============================================================
	//3- Update Falling or Rising Register.
	//reset Trigger Registers
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);

	switch(EXTI_Config->Trigger_Case)
	{
	case EXTI_Trigger_RISING :
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		break;
	case EXTI_Trigger_FALLING :
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		break;
	case EXTI_Trigger_RisingAndFalling:
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		break;
	}

	//=============================================================
	//4- Update IRQ Handler CALLBACK.
	GP_IRQ_CallBack[EXTI_Config->EXTI_PIN.ETI_InputLineNumber] = EXTI_Config->P_IRQ_CallBack;

	//=============================================================
	//5- Enable/Disable IRQ  EXTI  And NVIC Interrupt .

	// 	 Interrupt Mask on line x where x=[0 : 15]
	//0: Interrupt request from Line x is masked
	//1: Interrupt request from Line x is not masked
	switch(EXTI_Config->IRQ_EN)
	{
	case EXTI_IRQ_Enable:
		EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		break;
	case EXTI_IRQ_Disable:
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.ETI_InputLineNumber);
		break;
	}
}


//================================================================
//				APIs Functions Definition
//================================================================

/**================================================================
 * @Fn			 -MCAL_EXTI_GPIO_Init
 * @brief 		 -Initialize EXTI IRQ for PINy according to the specified parameters in EXTI_Config
 * @param [in]   -PinConfig : pointer to EXTI_PinConfig_t Structure that Contains
 * 				  the configuration information for the specified GPIO EXTI PIN.
 * @retval		 -none
 * Note			 -STM32F103C6 MCU have GPIO A,B,C,D,E Modules
 * 				  But LQFP48 package has A,B,PART Part of C/D exported as external PINS from the Modules
 */
void MCAL_EXTI_GPIO_Init(EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_GPIO_Update(EXTI_Config);
}

/**================================================================
 * @Fn			 -MCAL_EXTI_GPIO_DeInit
 * @brief 		 -Reset EXTI Registers and NVIC corresponding to IRQ Mask
 * @param [in]   -none
 * @retval		 -none
 * Note			 -none
 */
void MCAL_EXTI_GPIO_DeInit()
{
	EXTI->IMR  =  0x00000000;
	EXTI->EMR  =  0x00000000;

	EXTI->FTSR =  0x00000000;
	EXTI->RTSR =  0x00000000;

	EXTI->SWIER=  0x00000000;

	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR  |=  0xFFFFFFFF;

	NVIC_IQR6_EXTI0_Disable;
	NVIC_IQR7_EXTI1_Disable;
	NVIC_IQR8_EXTI2_Disable;
	NVIC_IQR9_EXTI3_Disable;
	NVIC_IQR23_EXTI5_9_Disable;
	NVIC_IQR40_EXTI10_15_Disable;
}

/**================================================================
 * @Fn			 -MCAL_EXTI_GPIO_Update
 * @brief 		 -Update EXTI IRQ for PINy according to the specified parameters in EXTI_Config
 * @param [in]   -PinConfig : pointer to EXTI_PinConfig_t Structure that Contains
 * 				  the configuration information for the specified GPIO EXTI PIN.
 * @retval		 -none
 * Note			 -none
 */
void MCAL_EXTI_GPIO_Update(EXTI_PinConfig_t * EXTI_Config)
{
	EXTI_GPIO_Update(EXTI_Config);
}

void MCAL_EXTI_GPIO_SET_PIN_INFO(EXTI_GPIO_mapping_t EXTI_Pin,uint8_t Trig_Case ,uint8_t IRQ_EN_DIS ,void(*P_IRQ_CallBack_FUN)(void) )
{
	EXTI_PinConfig_t EXTI_PinConfig;
	EXTI_PinConfig.EXTI_PIN= EXTI_Pin;
	EXTI_PinConfig.Trigger_Case = Trig_Case;
	EXTI_PinConfig.IRQ_EN = IRQ_EN_DIS;
	EXTI_PinConfig.P_IRQ_CallBack = P_IRQ_CallBack_FUN;

	MCAL_EXTI_GPIO_Init(&EXTI_PinConfig);
}

//========================================================================
//======================= 	  ISR Functions     ==========================
//========================================================================
void EXTI0_IRQHandler(void)
{
	//clear PIN0 in pending register
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= (1<<0);

	GP_IRQ_CallBack[0]();
}
void EXTI1_IRQHandler(void)
{
	//clear PIN1 in pending register
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= (1<<1);

	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	//clear PIN2 in pending register
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= (1<<2);

	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//clear PIN3 in pending register
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= (1<<3);

	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	//clear PIN4 in pending register
	//This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR |= (1<<4);

	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5) {EXTI->PR |= (1<<5); GP_IRQ_CallBack[5]();}
	else if(EXTI->PR & 1<<6) {EXTI->PR |= (1<<6); GP_IRQ_CallBack[6]();}
	else if(EXTI->PR & 1<<7) {EXTI->PR |= (1<<7); GP_IRQ_CallBack[7]();}
	else if(EXTI->PR & 1<<8) {EXTI->PR |= (1<<8); GP_IRQ_CallBack[8]();}
	else if(EXTI->PR & 1<<9) {EXTI->PR |= (1<<9); GP_IRQ_CallBack[9]();}
}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10) {EXTI->PR |= (1<<10); GP_IRQ_CallBack[10]();}
	else if(EXTI->PR & 1<<11) {EXTI->PR |= (1<<11); GP_IRQ_CallBack[11]();}
	else if(EXTI->PR & 1<<12) {EXTI->PR |= (1<<12); GP_IRQ_CallBack[12]();}
	else if(EXTI->PR & 1<<13) {EXTI->PR |= (1<<13); GP_IRQ_CallBack[13]();}
	else if(EXTI->PR & 1<<14) {EXTI->PR |= (1<<14); GP_IRQ_CallBack[14]();}
	else if(EXTI->PR & 1<<15) {EXTI->PR |= (1<<15); GP_IRQ_CallBack[15]();}
}
