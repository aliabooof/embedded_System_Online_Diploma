/*
 * Stm32_f103c6_Drivers_Gpio.c
 *
 *  
 *      Author: aliab
 */
#include "Stm32_f103c6_Drivers_EXTI.h"
#include "Stm32_f103c6_Drivers_Gpio.h"



/*=====================================================================================
 *                        GENERIRC MACROS
 *=====================================================================================
 * */
void (* GP_IRQ_CALLBACK[16])(void);//Global Array of Ptrs To Function

/*=====================================================================================
 *                        GENERIRC MACROS
 *=====================================================================================	*/
//THIS EXTIx_IRQHandler; Call automatically when the IRQ happened
void EXTI0_IRQHandler() {
	//Clear EXTI_PR at First
	EXTI_PR->PR |= (1 << 0);
	//Call IRQ_Call
	GP_IRQ_CALLBACK[0]();
}
void EXTI1_IRQHandler() {
	EXTI_PR->PR |= (1 << 1);
	GP_IRQ_CALLBACK[1]();
}
void EXTI2_IRQHandler() {
	EXTI_PR->PR |= (1 << 2);
	GP_IRQ_CALLBACK[2]();
}
void EXTI3_IRQHandler() {
	EXTI_PR->PR |= (1 << 3);
	GP_IRQ_CALLBACK[3]();
}
void EXTI4_IRQHandler() {
	EXTI_PR->PR |= (1 << 4);
	GP_IRQ_CALLBACK[4]();
}
void EXTI9_5_IRQHandler() {//When IRQ Happened the PR Already Happened.
	if (EXTI_PR->PR & (1 << 5)) {
		EXTI_PR->PR |= (1 << 5);
		GP_IRQ_CALLBACK[5]();
	} else if (EXTI_PR->PR & (1 << 6)) {
		EXTI_PR->PR |= (1 << 6);
		GP_IRQ_CALLBACK[6]();
	} else if (EXTI_PR->PR & (1 << 7)) {
		EXTI_PR->PR |= (1 << 7);
		GP_IRQ_CALLBACK[7]();
	} else if (EXTI_PR->PR & (1 << 8)) {
		EXTI_PR->PR |= (1 << 8);
		GP_IRQ_CALLBACK[8]();
	} else if (EXTI_PR->PR & (1 << 9)) {
		EXTI_PR->PR |= (1 << 9);
		GP_IRQ_CALLBACK[9]();
	}
}
void EXTI15_10_IRQHandler() {
	if (EXTI_PR->PR & (1 << 10)) {
		EXTI_PR->PR |= (1 << 10);
		GP_IRQ_CALLBACK[10]();
	} else if (EXTI_PR->PR & (1 << 11)) {
		EXTI_PR->PR |= (1 << 11);
		GP_IRQ_CALLBACK[11]();
	} else if (EXTI_PR->PR & (1 << 12)) {
		EXTI_PR->PR |= (1 << 12);
		GP_IRQ_CALLBACK[12]();
	} else if (EXTI_PR->PR & (1 << 13)) {
		EXTI_PR->PR |= (1 << 13);
		GP_IRQ_CALLBACK[13]();
	} else if (EXTI_PR->PR & (1 << 14)) {
		EXTI_PR->PR |= (1 << 14);
		GP_IRQ_CALLBACK[14]();
	} else if (EXTI_PR->PR & (1 << 15)) {
		EXTI_PR->PR |= (1 << 15);
		GP_IRQ_CALLBACK[15]();
	}

}

/*=====================================================================================
 *                        GENERIRC MACROS
 *=====================================================================================
 * */
#define AFIO_GPIO_EXTI_MAPPING(x)		((x==GPIOA_PR)?0:\
										(x==GPIOB_PR)?1:\
										(x==GPIOC_PR)?2:\
										(x==GPIOA_PR)?3:0)


/*=====================================================================================
 *                        GENERIRC FUNCTIONS DESCRIPTIONS
 *=====================================================================================
 * */

void Enable_NVIC(uint16_t IRQ){
	switch (IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Enable;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI_5_9_Enable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI_10_15_Enable;
		break;

	}
}
void Disable_NVIC(uint16_t IRQ){
	switch (IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI_5_9_Disable;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI_10_15_Disable;
		break;

	}
}

void Update_EXTI(EXTI_Pinconfig_t *EXTI_Config){
	/*
	 * 1. Pin Must be configured as floating input
	 * 2. Configure the selected port using AFIO_EXTIx By Routting Between A,B,C,D.
	 * 3. Configure Trigger edge(Falling/Rissing)
	 * 4. Update IRQ Handling CallBack
	 * 5. Enable/Disable the IRQ & NVIC
	 * 6. Call the IRQ Handler
	 */
	//1==================================================
	GPIO_PIN_CONFIG_T CFG;
	CFG.GPIO_PinNumber=EXTI_Config->EXTI_PIN.GPIO_PIN;
	CFG.GPIO_PinMode=GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_PORT,&CFG);
	//2==================================================
	uint8_t AFIO_EXTICR_Index	=EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER / 4;//I Can Determine the EXTICR By Dividing the Line Number /4.
	uint8_t AFIO_EXTICR_Position=(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER % 4)*4;//Determine the position of my 4 bits ..
	//can calculate any position for any EXTI

	//Clear the four Bit First
	AFIO_PR->EXTICR[AFIO_EXTICR_Index] &=~(0xF <<AFIO_EXTICR_Position);
	//Set the four Bits
	AFIO_PR->EXTICR[AFIO_EXTICR_Index] |=((AFIO_GPIO_EXTI_MAPPING(EXTI_Config->EXTI_PIN.GPIO_PORT) &0xF) <<AFIO_EXTICR_Position);
	//3==================================================
	//Clear Bits of Rissing And Falling
	EXTI_PR->RTSR &=~(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	EXTI_PR->FTSR &=~(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_RAISING){
		EXTI_PR->RTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}
	else if (EXTI_Config->Trigger_Case == EXTI_TRIGGER_FALLING){

		EXTI_PR->FTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}
	else if(EXTI_Config->Trigger_Case == EXTI_TRIGGER_BOTH){
		EXTI_PR->RTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		EXTI_PR->FTSR |=(1<<EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}
	//4==================================================

	GP_IRQ_CALLBACK[EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER]=EXTI_Config->P_IRQ_CALLBACK;//Initialize your Ptr of function
	//of EXTI_Pinconfig_t to The Function you Created

	//5==================================================
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE) {
		EXTI_PR->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);

	}
	else if (EXTI_Config->IRQ_EN == EXTI_IRQ_DISABLE) {
		EXTI_PR->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_LINE_NUMBER);
	}

}


/*=====================================================================================
 *                          APIS FUNCTIONS DESCRIPTIONS
 *=====================================================================================
 * */

/*======================================================================================
 * @Fn			-MCAL_EXTI_GPIO_DeInit
 * @brief		-Reset EXTI Registers and NVIC Corresponding IRQ Mask
 * @retval		-none
 * Note			-none
======================================================================================*/
void MCAL_EXTI_GPIO_DeInit(void){
	EXTI_PR->IMR=0x00000000;
	EXTI_PR->EMR=0x00000000;
	EXTI_PR->RTSR=0x00000000;
	EXTI_PR->FTSR=0x00000000;
	EXTI_PR->PR  =0xFFFFFFFF;//Cleared by writing a ‘1’ into the bit.
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI_5_9_Disable;
	NVIC_IRQ40_EXTI_10_15_Disable;

}

/*======================================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief		-This is used to intialize the EXTI From Specific GPIO PIN/Trigger Condition and IRQ CAllBack
 * @param [in]	 - EXTI_Config :pointer to a structure that contains the pin configuration information
 * 							 Must be initialized from @ref  EXTI_Mapping ,
 * 							 @ref EXTI_Trigger_define ,@ref EXTI_Enable_define
 * @retval 		- none
 * Note			 -Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,but LQFP48 Package
 * 				 has only GPIO A,B,PART of C/D exported as external PINS from the M
======================================================================================*/

void MCAL_EXTI_GPIO_Init(EXTI_Pinconfig_t *EXTI_Config){
	Update_EXTI(EXTI_Config);
}

/*======================================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief		-This is used to intialize the EXTI From Specific GPIO PIN/Trigger Condition and IRQ CAllBack
 * @param [in]	 - EXTI_Config :pointer to a structure that contains the pin configuration information
 * 							 Must be initialized from @ref  EXTI_Mapping ,
 * 							 @ref EXTI_Trigger_define ,@ref EXTI_Enable_define
 * @retval 		- none
 * Note			 -Stm32F103C6 MCU has GPIO A,B,C,D,E Modules,but LQFP48 Package
 * 				 has only GPIO A,B,PART of C/D exported as external PINS from the M
======================================================================================*/

void MCAL_EXTI_GPIO_Update(EXTI_Pinconfig_t *EXTI_Config){
	Update_EXTI(EXTI_Config);
}