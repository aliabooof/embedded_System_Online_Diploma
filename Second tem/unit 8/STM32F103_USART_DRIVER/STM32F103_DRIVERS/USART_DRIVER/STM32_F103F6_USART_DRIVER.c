	/*
 * STM32_F103C6_GPIO_Driver.c
 *
 *      Author: aliab
 */

#include "../inc/STM32_F103F6_USART_DRIVER.h"


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
USART_config_t * Global_UART_Config  = NULL;


/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
//BaudRate Calculation
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 =
// uint32((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV  )  * 100
//DIV_Mantissa = Integer Part (USARTDIV  )
//DIV_Fraction = (( USARTDIV_MUL100  - DIV_Mantissa_MUL100  ) * 16 ) / 100

#define USARTDIV(_PCLK_, _BAUD_)							(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)						(uint32_t) ( (25 * _PCLK_ ) / (4  * _BAUD_ ))
#define Mantissa_MUL100(_PCLK_, _BAUD_)						(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) )
#define DIV_Fraction(_PCLK_, _BAUD_)						(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) -  Mantissa_MUL100(_PCLK_, _BAUD_) ) * 16 ) / 100 )
#define UART_BRR_Register(_PCLK_, _BAUD_)					(( Mantissa (_PCLK_, _BAUD_) ) <<4 )|( (DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )




/*
 * =======
 * ================================================================================
 * 							APIs Implementations
 * =======================================================================================
 */

/**===========================================================================
 * @Fn				-MCAL_USART_init
 * @brief 			-Initializes USART
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @param [in] 		-config: the configured structure that will be used
 * @retval 			-none
 * Note				-(Supported feature ASYNCH. Only)!
 *============================================================================
 */
void MCAL_USART_init(USART_Typedef * USARTX,USART_config_t * config){
	Global_UART_Config = config;
	uint32_t pclk;

	//	enable Clock for the USART
	if(USART1 == USARTX){
		RCC_USART1_CLK_EN();
	}else if(USART2 == USARTX){
		RCC_USART2_CLK_EN();
	}else if(USART3 == USARTX){
		RCC_USART3_CLK_EN();
	}

	//Enable USART Module
	//USART_CR1  Bit 13 UE: USART enable
	USARTX->CR1 |= (1<<13);

	//Enable USART TX and RX according to the USART_Mode configuration item
	//USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver enable
	USARTX->CR1 |= config->USART_mode;

	//Data length
	USARTX->CR1 |= config->data_lenght;

	//Parity control
	USARTX->CR1 |= config->parity;

	//Stop bits
	USARTX->CR2 |= config->stop_bits;

	//Control flow
	USARTX->CR3 |= config->hwFlCt;

	if(USARTX == USART1){
		pclk = MCAL_RCC_getPCLK2Freq();
	}else{
		pclk = MCAL_RCC_getPCLK1Freq();
	}


	USARTX->BBR = UART_BRR_Register(pclk, config->baud_rate);


	if(config->IRQ_enable != USART_IRQ_ENABLE_NONE){
		USARTX->CR1 |= config->IRQ_enable;

		if(USART1 == USARTX){
			NVIC_IRQ37_USART1_ENABLE();
		}else if(USART2 == USARTX){
			NVIC_IRQ38_USART2_ENABLE();
		}else if(USART3 == USARTX){
			NVIC_IRQ39_USART3_ENABLE();
		}
	}

}

/**===========================================================================
 * @Fn				-MCAL_USART_deinit
 * @brief 			-DEinitializes USART  (Supported feature ASYNCH. Only)!
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-Reset the Model By RCC
 *============================================================================
 */
void MCAL_USART_deinit(USART_Typedef * USARTX){

	if(USART1 == USARTX){
		RCC_USART1_RESET(); 		//Disabling the clock
		NVIC_IRQ37_USART1_DISABLE(); //Disabling the interrupt
	}else if(USART2 == USARTX){
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE();
	}else if(USART3 == USARTX){
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE();
	}

}



/**===========================================================================
 * @Fn				-MCAL_USART_set_pins
 * @brief 			-Sets the pins according to the Blue pill board
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-(Supported feature ASYNCH. Only)!
 *============================================================================
 */
void MCAL_USART_set_pins(USART_Typedef * USARTX){
	GPIO_PIN_Config_t  pinConfig;

	if(USART1 == USARTX){
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		pinConfig.GPIO_PinNumber = GPIO_PIN_9;
		pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA10 RX
		pinConfig.GPIO_PinNumber = GPIO_PIN_10;
		pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA11 CTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_CTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_11;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

		//PA12 RTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_RTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_12;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

	}else if(USART2 == USARTX){
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		pinConfig.GPIO_PinNumber = GPIO_PIN_2;
		pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA3 RX
		pinConfig.GPIO_PinNumber = GPIO_PIN_3;
		pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOA, &pinConfig);

		//PA0 CTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_CTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_0;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

		//PA1 RTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_RTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_1;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);
		}

	}else if(USART3 == USARTX){

		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PB14 RTS

		//PA10 TX
		pinConfig.GPIO_PinNumber = GPIO_PIN_10;
		pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
		pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &pinConfig);

		//PA11 RX
		pinConfig.GPIO_PinNumber = GPIO_PIN_11;
		pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_AF;
		MCAL_GPIO_Init(GPIOB, &pinConfig);

		//PA12 CTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_CTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_12;
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}

		//PA13 RTS
		if(Global_UART_Config->hwFlCt == USART_HWFLCT_RTS || Global_UART_Config->hwFlCt == USART_HWFLCT_RTS_CTS){
			pinConfig.GPIO_PinNumber = GPIO_PIN_13;
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);
		}


	}


}

/**===========================================================================
 * @Fn				-MCAL_USART_send_data
 * @brief 			-Sends the data can be either 8 or 9 bits
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @param [in] 		-data: the data that will be sent
 * @param [in] 		-poll: enumeration that indicates whether using blocking or not
 * @retval 			-none
 * Note				-Parity if enabled takes space from data
 *============================================================================
 */
void MCAL_USART_send_data(USART_Typedef * USARTX, uint16_t* data, enum polling poll){

	// wait until TXE flag is set in the SR
	if(poll == enable){
		while(!(USARTX->SR & (1<<7)));
	}

	//Checking the data length
	if(Global_UART_Config->data_lenght == USART_DATA_LENGHT_9B){
		USARTX->DR = (*data & (uint32_t)(0x1FF));
	}else{
		USARTX->DR = (*data & (uint8_t)(0xFF));
	}


}


/**===========================================================================
 * @Fn				-MCAL_USART_send_data
 * @brief 			-Receives data can be either 8 or 9 bits
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @param [in] 		-data: variable that the data will be received in
 * @param [in] 		-poll: enumeration that indicates whether using blocking or not
 * @retval 			-none
 * Note				-Parity if enabled takes space from data
 *============================================================================
 */
void MCAL_USART_recive_data(USART_Typedef * USARTX, uint16_t* data, enum polling poll){

	//Wait until RXNE flag is set in the SR
	if(poll == enable){
		while(!(USARTX->SR & 1 << 5));
	}

	//Checking the data length
	if(Global_UART_Config->data_lenght == USART_DATA_LENGHT_9B){
		//No parity so all 9 bits are considered data
		if(Global_UART_Config->parity == USART_PARITY_NONE){
			*((uint16_t*)data) = USARTX->DR;
		}else{
			*((uint16_t*)data) = (USARTX->DR & (uint8_t)0xFF);
		}

	}else{
		//No parity so all 8 bits are considered data
		if(Global_UART_Config->parity == USART_PARITY_NONE){
			*((uint16_t*)data) = (USARTX->DR & (uint8_t)0xFF);
		}else{
			*((uint16_t*)data) = (USARTX->DR & (uint8_t)0x7F);
		}

	}

}


/**===========================================================================
 * @Fn				-MCAL_USART_TC_status
 * @brief 			-Checks if the transmission is complete or not
 * @param [in] 		-USARTx: where x can be (1..3 depending on device used)
 * @retval 			-none
 * Note				-none
 *============================================================================
 */
void MCAL_USART_TC_status(USART_Typedef * USARTX){
	//Waiting until transmission is complete
	while(!(USARTX->SR & 1 << 6));
}

//ISR
void USART1_IRQHandler (void){
	Global_UART_Config->p_IRQ_callback();
}

void USART2_IRQHandler (void){
	Global_UART_Config->p_IRQ_callback();
}

void USART3_IRQHandler (void){
	Global_UART_Config->p_IRQ_callback();
}
