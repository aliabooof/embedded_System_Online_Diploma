/*
 * Stm32_f103c6_Drivers_Gpio.c
 *
 *  
 *      Author: aliab
 */
#include "Stm32_F103C6_EXTI_driver.h"
#include "stm32_f103c6_gpio_drivers.h"

/*
 * ===========================================================================================
 * 									Global Variables
 * ===========================================================================================
 * */

void (* GP_IRQ_Callback[15])(void);

/*
 * ===========================================================================================
 * 									Generic Macros
 * ===========================================================================================
 * */
#define AFIO_GPIO_EXTI_MAPPING(x)		((x == GPIOA)? 0 :\
										 (x == GPIOB)? 1 :\
										 (x == GPIOC)? 2 :\
										 (x == GPIOD)? 3 : 0)

/*
 * ===========================================================================================
 * 									Helper Functions
 * ===========================================================================================
 * */
void enable_NVIC(uint16_t EXTI_LineNumber){
	switch(EXTI_LineNumber){
		case 0:
			NVIC_IRQ6_EXTI0_ENABLE;
			break;

		case 1:
			NVIC_IRQ7_EXTI1_ENABLE;
			break;

		case 2:
			NVIC_IRQ8_EXTI2_ENABLE;
			break;

		case 3:
			NVIC_IRQ9_EXTI3_ENABLE;
			break;

		case 4:
			NVIC_IRQ10_EXTI4_ENABLE;
			break;

		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_ENABLE;
			break;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_ENABLE;
			break;
	}
}

void disable_NVIC(uint16_t EXTI_LineNumber){
	switch(EXTI_LineNumber){
		case 0:
			NVIC_IRQ6_EXTI0_DISABLE;
			break;

		case 1:
			NVIC_IRQ7_EXTI1_DISABLE;
			break;

		case 2:
			NVIC_IRQ8_EXTI2_DISABLE;
			break;

		case 3:
			NVIC_IRQ9_EXTI3_DISABLE;
			break;

		case 4:
			NVIC_IRQ10_EXTI4_DISABLE;
			break;

		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_DISABLE;
			break;

		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_DISABLE;
			break;
	}
}

void update_EXTI(EXTI_PinConfig_t * EXTI_config){
	//Step 1: Configure GPIO to be AF input

	GPIO_pinConfig_t GPIO_config;

	//Update the GPIO pin to be input floating
	GPIO_config.GPIO_pinNumber = EXTI_config->EXTI_Pin.GPIO_Pin;
	GPIO_config.GPIO_mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_init(EXTI_config->EXTI_Pin.GPIO_Port, &GPIO_config);


	/*Step 2: Update AFIO to route between EXTI line with one of
	* the Ports A,B,C,D*/

	//To get which EXTICR register to write in it according to the line
	uint8_t AFIO_EXTICR_index = (EXTI_config->EXTI_Pin.EXTI_LineNumber / 4);

	//To shift the line in the register
	uint8_t AFIO_EXTICR_shiftValue = ((EXTI_config->EXTI_Pin.EXTI_LineNumber % 4) * 4);

	/*To eliminate unwanted values we clear the four bits according to
	 * the EXTI line*/
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF << AFIO_EXTICR_shiftValue);
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_MAPPING(EXTI_config->EXTI_Pin.GPIO_Port) & 0xF) << AFIO_EXTICR_shiftValue);

	//Step 3: Update rising or falling edge
	EXTI->RTSR &= ~(1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
	EXTI->FTSR &= ~(1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);

	switch(EXTI_config->Trigger_Case){

		case EXTI_Trigger_Rising:
			EXTI->RTSR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
			break;

		case EXTI_Trigger_Falling:
			EXTI->FTSR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
			break;

		case EXTI_Trigger_RisingandFalling:
			EXTI->RTSR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
			EXTI->FTSR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
			break;

		default:
			EXTI->RTSR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
	}


	//Step 4: Update IRQ handling callback
	GP_IRQ_Callback[EXTI_config->EXTI_Pin.EXTI_LineNumber] = EXTI_config->P_IRQ_Callback;

	//Step 5: Enable/disable IRQ && NVIC
	if(EXTI_config->IRQ_EN == EXTI_IRQ_ENABLE){
		EXTI->IMR |= (1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
		enable_NVIC(EXTI_config->EXTI_Pin.EXTI_LineNumber);
	} else{
		EXTI->IMR &= ~(1 << EXTI_config->EXTI_Pin.EXTI_LineNumber);
		disable_NVIC(EXTI_config->EXTI_Pin.EXTI_LineNumber);
	}
}



/*
 * ===========================================================================================
 * 									APIs Functions Definitions
 * ===========================================================================================
 * */

/*======================================================================================
* @Fn			-MCAL_EXTI_GPIO_init
* @brief		-This is used to initialize EXTI from specific GPIO PIN
* 				 and specify the Mask/Trigger condition and IRQ Callback
* @param[in]	-EXTI_config set by @ref EXTI_ define, EXTI_Trigger_define
* 				 and EXTI_IRQ define
* @retval		-None
* Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
*				 But LQFP48 Package has only GPIO A, B, PART of C/D exported
*				  as external PINS from the MCU
*				Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
======================================================================================*/
void MCAL_EXTI_GPIO_init(EXTI_PinConfig_t * EXTI_config){
	update_EXTI(EXTI_config);
}



/*======================================================================================
* @Fn			-MCAL_EXTI_GPIO_deinit
* @brief		-Resets EXTI registers and NVIC corresponding to The
* 				IRQ Mask
* @param[in]	-None
* @retval		-None
* Note			-None
======================================================================================*/
void MCAL_EXTI_GPIO_deinit(void){

	//Step 1: Reset all EXTI registers
	EXTI->IMR = 0x00000000;

	EXTI->EMR = 0x00000000;

	EXTI->RTSR = 0x00000000;

	EXTI->FTSR = 0x00000000;

	EXTI->SWIER = 0x00000000;

	//Cleared by writing a '1' into the bit.
	EXTI->PR = 0xFFFFFFFF;

	//Step 2: Disable IRQ from NVIC
	NVIC_IRQ6_EXTI0_DISABLE;
	NVIC_IRQ7_EXTI1_DISABLE;
	NVIC_IRQ8_EXTI2_DISABLE;
	NVIC_IRQ9_EXTI3_DISABLE;
	NVIC_IRQ10_EXTI4_DISABLE;
	NVIC_IRQ23_EXTI5_9_DISABLE;
	NVIC_IRQ40_EXTI10_15_DISABLE;


}


/*======================================================================================
* @Fn			-MCAL_EXTI_GPIO_update
* @brief		-This is used to update EXTI from specific GPIO PIN
* 				 and specify the Mask/Trigger condition and IRQ Callback
* @param[in]	-EXTI_config set by @ref EXTI_ define, EXTI_Trigger_define
* 				 and EXTI_IRQ define
* @retval		-None
* Note			-Stm32F103C6 MCU has GPIO A,B,C,D,E Modules
*				 But LQFP48 Package has only GPIO A, B, PART of C/D exported
*				  as external PINS from the MCU
*				Also Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
======================================================================================*/
void MCAL_EXTI_GPIO_update(EXTI_PinConfig_t * EXTI_config){
	update_EXTI(EXTI_config);
}

/*
 * ===========================================================================================
 * 									ISR Functions
 * ===========================================================================================
 * */

void EXTI0_IRQHandler(void){
	/*Clear pending request by writing '1' in the
	 * Pending register (EXTI_PR)*/
	EXTI->PR |= (1 << 0);

	//Call the IRQ callback
	GP_IRQ_Callback[EXTI0]();
}

void EXTI1_IRQHandler(void){
	/*Clear pending request by writing '1' in the
	 * Pending register (EXTI_PR)*/
	EXTI->PR |= (1 << 1);

	//Call the IRQ callback
	GP_IRQ_Callback[EXTI1]();
}

void EXTI2_IRQHandler(void){
	/*Clear pending request by writing '1' in the
	 * Pending register (EXTI_PR)*/
	EXTI->PR |= (1 << 2);

	//Call the IRQ callback
	GP_IRQ_Callback[EXTI2]();
}

void EXTI3_IRQHandler(void){
	/*Clear pending request by writing '1' in the
	 * Pending register (EXTI_PR)*/
	EXTI->PR |= (1 << 3);

	//Call the IRQ callback
	GP_IRQ_Callback[EXTI3]();
}

void EXTI4_IRQHandler(void){
	/*Clear pending request by writing '1' in the
	 * Pending register (EXTI_PR)*/
	EXTI->PR |= (1 << 4);

	//Call the IRQ callback
	GP_IRQ_Callback[EXTI4]();
}

void EXTI9_5_IRQHandler(void){
	if (EXTI->PR & (1 << 5)) {EXTI->PR |= (1 << 5); GP_IRQ_Callback[EXTI5]();}
	if (EXTI->PR & (1 << 6)) {EXTI->PR |= (1 << 6); GP_IRQ_Callback[EXTI6]();}
	if (EXTI->PR & (1 << 7)) {EXTI->PR |= (1 << 7); GP_IRQ_Callback[EXTI7]();}
	if (EXTI->PR & (1 << 8)) {EXTI->PR |= (1 << 8); GP_IRQ_Callback[EXTI8]();}
	if (EXTI->PR & (1 << 9)) {EXTI->PR |= (1 << 9); GP_IRQ_Callback[EXTI9]();}
}
void EXTI15_10_IRQHandler(void){
	if (EXTI->PR & (1 << 10)) {EXTI->PR |= (1 << 10); GP_IRQ_Callback[EXTI10]();}
	if (EXTI->PR & (1 << 11)) {EXTI->PR |= (1 << 11); GP_IRQ_Callback[EXTI11]();}
	if (EXTI->PR & (1 << 12)) {EXTI->PR |= (1 << 12); GP_IRQ_Callback[EXTI12]();}
	if (EXTI->PR & (1 << 13)) {EXTI->PR |= (1 << 13); GP_IRQ_Callback[EXTI13]();}
	if (EXTI->PR & (1 << 14)) {EXTI->PR |= (1 << 14); GP_IRQ_Callback[EXTI14]();}
	if (EXTI->PR & (1 << 15)) {EXTI->PR |= (1 << 15); GP_IRQ_Callback[EXTI15]();}

}

