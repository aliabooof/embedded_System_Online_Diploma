/*
 * STM32_F103C6_GPIO_Driver.c
 *
 *      Author: aliab
 */

/* ================================================== Includes =============================================================*/
#include "STM32_F103C6_USART_Driver.h"


/* ================================================== Generic Variables  =============================================================*/
UART_Config* Global_UART_Config = NULL;

/* ================================================== Generic Functions  =============================================================*/




/* ================================================== APIs Implementation  =============================================================*/

/**================================================================
 * @Fn				- MCAL_UART_Init
 * @brief			- Initializes UART (Supported features ASYNCH. Only)
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @param[in]		- UART_Config: All UART Configuration EXTI_PinConfig_t
 * @retval 			- None
 * @Notes			- Support for new Asynchronous mode & Clock 8 MHz
 */
void MCAL_UART_Init(USART_TypeDef *USARTx, UART_Config* UART_Config)
{
	uint32_t pclk, BRR;

	Global_UART_Config = UART_Config;

	// Enable the Clock for given UART Peripheral
	if (USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
	}

	// Enable USART Module
	// Bit 13 UE: USART Enable
	USARTx->CR1 |= 1<<13;

	// Enable USART Tx and Rx engines according to the USART_Mode_configuration item
	// USART_CR1 Bit 3 TE: Transmitter enable & Bit 2 RE: Receiver Enable
	USARTx->CR1 |= UART_Config->USART_Mode;

	// PAYLOAD Width
	// USARTx->CR1 Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	// Configuration of parity control bit fields
	// USARTx->CR1 Bit 10 PCE: Parity control enable 		Bit 9 PS: Parity selection
	USARTx->CR1 |= UART_Config->Parity;

	// Configure the number of stop bits
	// USART_CR2 Bits 13:12 STOP:	STOP bits
	USARTx->CR2 |= UART_Config->StopBits;

	// USART Hardware Flow Control
	// USART_CR3 Bit 9 CISE: CTS enable 	Bit 8 RTSE: RTS enable
	USARTx->CR3 |= UART_Config->HardwareFlowControl;

	// Configuration of BRR(BaudRate register)
	// PCLK1 for USART2, 3
	// PCLK2 for USART1
	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GetPCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_GetPCLK1Freq();
	}

	// BuadRate Calculation
	BRR = UART_BRR_Register(pclk, UART_Config->BaudRate);
	USARTx->BRR = BRR;

	// Enable/Disable Interrupt
	// USART_CR1
	if (UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		// Enable NVIC For USARTx IRQ
		if (USARTx == USART1)
		{
			NVIC_IRQ37_USART1_Enable;
		}
		else if (USARTx == USART2)
		{
			NVIC_IRQ38_USART2_Enable;
		}
		else if (USARTx == USART3)
		{
			NVIC_IRQ39_USART3_Enable;
		}

	}
}

/**================================================================
 * @Fn				- MCAL_UART_DeInit
 * @brief			- DeInitializes UART (Supported features ASYNCH. Only)
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- None
 * @Notes			- Reset the model by RCC
 */
void MCAL_UART_DeInit (USART_TypeDef *USARTx)
{
	if (USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if (USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_Disable;
	}
	else if (USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_Disable;
	}
}

/**================================================================
 * @Fn				- MCAL_UART_SendData
 *
 * @brief			- Send Buffer on UART
 *
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @param[in]		- pTxBuffer Buffer
 * @param[in]		- PollingEnable		Enable Polling or Disable it
 *
 * @retval 			- None
 *
 * @Notes			- We should initialize USART First
 */
void MCAL_UART_SendData (USART_TypeDef *USARTx, uint16_t *pTxBuffer, enum Polling_Mechanism PollingEnable)
{
	// Wait until TXE flag is set in the SR
	if (PollingEnable == enable)
	{
		while (!(USARTx->SR & 1<<7));
	}

	// Check the USART_WordLength item for 9BIT or 8BIT in a frame

	//When Transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//because it is replaced by the parity.
	//When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.

	if (Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		// This is 8bit data transfer
		USARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
	}
}

void MCAL_UART_WAIT_TC (USART_TypeDef *USARTx)
{
	// Wait till TC flag is set in the SR
	while(!(USARTx->SR & 1<<6));
}

void MCAL_UART_ReceiveData (USART_TypeDef *USARTx, uint16_t *pRxBuffer, enum Polling_Mechanism PollingEnable)
{
	// Wait until RXNE flag is set in the SR
	if (PollingEnable == enable)
	{
		while (!(USARTx->SR & 1<<5));
	}

	// Check the USART_WordLength item for 9BIT or 8BIT in a frame
	if (Global_UART_Config->Payload_Length == UART_Payload_Length_9B)
	{
		if (Global_UART_Config->Parity == UART_Parity_NONE)
		{
			// No Parity means that all 9 bits are data
			*((uint16_t*) pRxBuffer) = USARTx->DR;

		}
		else
		{
			// If Parity is used, 8 bits will be user data and 1 bit will be parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);

		}
	}
	else
	{
		if (Global_UART_Config->Parity == UART_Parity_NONE)
		{
			// No Parity means that all 8 bits are data
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);

		}
		else
		{
			// If Parity is used, 7 bits will be user data and 1 bit will be parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0x7F);

		}

	}
}

/**================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief			- Initializes GPIO Pins
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- None
 * @Notes			- Should enable the corresponding ALT & GPIO in RCC clock . Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef *USARTx)
{
	GPIO_PinConfig_t PinCfg;

	if (USARTx == USART1)
	{
		// PA9 Tx
		// PA10 Rx
		// PA11 CTS
		// PA12 RTS

		// PA9 Tx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);

		// PA10 Rx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);

		if (Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_CTS || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS_CTS)
		{
			// PA11 CTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);
		}

		if (Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS_CTS)
		{
			// PA12 RTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);
		}

	}
	else if (USARTx == USART2)
	{
		// PA2 Tx
		// PA3 Rx
		// PA0 CTS
		// PA1 RTS

		// PA2 Tx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);

		// PA3 Rx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);

		if (Global_UART_Config->HardwareFlowControl || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_CTS)
		{
			// PA0 CTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);
		}



		if (Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS_CTS)
		{
			// PA1 RTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);
		}

	}
	else if (USARTx == USART3)
	{
		// PB10 Tx
		// PB11 Rx
		// PA13 CTS
		// PA14 RTS

		// PB10 Tx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIO_PORTB, &PinCfg);

		// PB11 Rx
		PinCfg.GPIO_Pin_Number = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIO_PORTB, &PinCfg);

		if (Global_UART_Config->HardwareFlowControl || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_CTS)
		{
			// PA11 CTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIO_PORTB, &PinCfg);
		}



		if (Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS || Global_UART_Config->HardwareFlowControl == UART_HardwareFlowControl_RTS_CTS)
		{
			// PA12 RTS
			PinCfg.GPIO_Pin_Number = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIO_PORTA, &PinCfg);
		}


	}


}


// --------------------------------ISR

void USART1_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}

void USART2_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}

void USART3_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CallBack();
}

























