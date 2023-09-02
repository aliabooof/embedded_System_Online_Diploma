/*
 * STM32F103C6_GPIO.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */
#include "STM32F103x6_USART.h"

//================================================================
//				Generic Variables
//================================================================

UART_Config *G_UART_Config = NULL;

UART_Config *G_UART1_Config = NULL;
UART_Config *G_UART2_Config = NULL;
UART_Config *G_UART3_Config = NULL;
//================================================================
//				APIs Functions Definition
//================================================================

/**================================================================
 * @Fn			 -MCAL_UART_Init
 * @brief 		 -Initializes UARTx (Support Features ASYNCH. Only)
 * @param [in]   -USARTx : were x can be (1...3 depending on device used)to select the USART Peripheral
 * @param [in]   -UART_Config : pointer to UART_Config Structure that Contains
 * 						        the configuration information for All UART.
 * @retval		 -none
 * Note			 -Support for now ASYNCH. Mode & Clock 8 MHz
 */
void MCAL_UART_Init(USART_TypeDef * USARTx , UART_Config * UART_Config)
{
	G_UART_Config = UART_Config;
	uint32_t pclk , BRR;
	// Enable  The Clock for USART Peripheral
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_EN();
		G_UART1_Config = UART_Config;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_EN();
		G_UART2_Config = UART_Config;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_EN();
		G_UART3_Config = UART_Config;
	}

	// Enable USART Module
	//Bit 13 UE: USART enable
	USARTx->CR1 |= 1<<13;

	// Enable USART Tx and Rx according to The USART_Mode Configuration item
	// USART_CR1  Bit 3 TE: Transmitter enable  ,Bit 2 RE: Receiver enable
	USARTx->CR1 |= UART_Config->USART_Mode;

	// Configure The Parity Control bit field
	// USARTx->CR1  Bit 10 PCE: Parity control enable , Bit 8 PEIE: PE interrupt enable
	USARTx->CR1 |= UART_Config->Parity_Mode;

	//Configure The Number of Stop Bit
	//USARTx->CR2 Bits (13:12) STOP: STOP bits
	USARTx->CR2 |= UART_Config->StopBits;

	//USART hardware Flow Control
	//USARTx->CR3  Bit 9 CTSE: CTS enable  , Bit 9 CTSE: CTS enable
	USARTx->CR3 |= UART_Config->HwFlowCtl;

	//PayLoad Length
	//USARTx->CR1 Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Configuration of BRR(Baud Rate Register)
	//PCLK2 For USART 1
	//PCLK1 For USART 2,3
	if(USARTx == USART1)
	{
		pclk = MCAL_RCC_Get_PCLK2Freq();
	}
	else
	{
		pclk = MCAL_RCC_Get_PCLK1Freq();
	}

	BRR = USART_BRR_Register(pclk , UART_Config->BaudRate);
	USARTx->BRR = BRR;

	//Enable/Disable Interrupt
	//USARTx->CR1
	if(UART_Config->IQR_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_Config->IQR_Enable;

		// Enable NVIC For USARTx IRQ
		if(USARTx == USART1)
		{
			NVIC_IQR37_USART1_Enable;
		}
		else if(USARTx == USART2)
		{
			NVIC_IQR38_USART2_Enable;
		}
		else if(USARTx == USART3)
		{
			NVIC_IQR39_USART3_Enable;
		}
	}
}

/**================================================================
 * @Fn			 -MCAL_UART_DeInit
 * @brief 		 -DeInitializes UARTx (Support Features ASYNCH. Only)
 * @param [in]   -USARTx : were x can be (1...3 depending on device used)to select the GPIO Peripheral
 * @retval		 -none
 * Note			 -Reset The Model By RCC
 */
void MCAL_UART_DeInit(USART_TypeDef * USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_RESET();
		NVIC_IQR37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IQR38_USART2_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_RESET();
		NVIC_IQR39_USART3_Disable;
	}
}

/**================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief 			- Sends the data
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer: Data to be sent
 * @param [in] 		- PollingEn: Enables or disables the polling mechanism
 * @retval 			- none
 * @Note              - Should initialize UART First
 */
void MCAL_UART_SendData(USART_TypeDef * USARTx, uint16_t* pTxBuffer , enum Polling_Mechanism PollingEn)
{
	//wait until TXE flag set in SR Register
	//Bit 7 TXE: Transmit data register empty
	if(PollingEn == enable)
		while(!(USARTx->SR & 1<<7));

	//Check The USART_Word_Length item for 9BIT or 8BIT in a frame

	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit
	if(G_UART_Config->Payload_Length == UART_PayLoad_Length_8B)
	{
		USARTx->DR = *pTxBuffer & (uint8_t)0xFF;// 8 Bits
	}
	else if(G_UART_Config->Payload_Length == UART_PayLoad_Length_9B)
	{
		USARTx->DR = *pTxBuffer & (uint16_t)0x1FF;// 9 Bits
	}
}

/**================================================================
 * @Fn				-USART_Wait_TC
 * @brief 			- Wait until The TC(Transmission complete) flag is Set
 * @param [in] 		- USARTX: where x can be (1..3 depending on device used)
 * @retval 			-none
 */
void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx)
{
	//wait until TC flag set in SR Register
	//Bit 6 TC: Transmission complete
	while(USARTx->SR & 1<<6);
}

/**================================================================
 * @Fn				- MCAL_UART_ReceiveData
 * @brief 			- Recieves the data
 * @param [in] 		- USARTx: where x can be (1..3 depending on device used)
 * @param [in] 		- pRxBuffer:
 * @param [in] 		- PollingEn: Enables or disables the polling mechanism
 * @re
 */
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx, uint16_t* pRxBuffer , enum Polling_Mechanism PollingEn)
{
	//wait until RXNE flag set in SR Register
	//Bit 5 RXNE: Read data register not empty
	if(PollingEn == enable)
		while(!(USARTx->SR & 1<<7));

	if(G_UART_Config->Payload_Length == UART_PayLoad_Length_8B)
	{
		if(G_UART_Config->Parity_Mode == UART_Parity_Mode_NONE)
		{
			*((uint16_t*) pRxBuffer) = (USARTx->DR & (uint8_t)0xFF);// 8 Bits
		}
		else
		{
			// Parity is used , so,7 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR  & (uint8_t)0x7F);// 7 Bits
		}
	}
	else //if(G_UART_Config->Payload_Length == UART_PayLoad_Length_9B)
	{
		if(G_UART_Config->Parity_Mode == UART_Parity_Mode_NONE)
		{
			*((uint16_t*) pRxBuffer) = USARTx->DR ;// 9 Bits
		}
		else
		{
			// Parity is used , so,8 bits will be of user data and 1 bit is parity
			*((uint16_t*) pRxBuffer) = (USARTx->DR  & (uint8_t)0xFF);// 8 Bits
		}
	}
}

/**================================================================
 * @Fn				-MCAL_UART_GPIO_Set_Pins
 * @brief 			-initialize GPIO Pins
 * @param [in] 		-USARTX: where x can be (1..3 depending on device used)
 * @retval 			-none
 * @Note			-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after USART_Init()
 */
void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx)
{

	if(USARTx == USART1)
	{
		//PA9 -> TX
		//PA10 -> RX
		//PA11 -> CTS
		//PA12 -> RTS


		//PA9 -> TX
		MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_9, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		//PA10 -> RX
		MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_10, GPIO_MODE_Input_FLO,0);

		if(G_UART1_Config->HwFlowCtl == UART_HwFlowCtl_CTS || G_UART1_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PA11 -> CTS
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_11, GPIO_MODE_Input_FLO,0);
		}
		if(G_UART1_Config->HwFlowCtl == UART_HwFlowCtl_RTS || G_UART1_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PA12 -> RTS
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_12, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		}

	}
	else if(USARTx == USART2)
	{
		//PB2 -> TX
		//PB3 -> RX
		//PB0 -> CTS
		//PB1 -> RTS


		//PB2 -> TX
		MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_2, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		//PB3 -> RX
		MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_3, GPIO_MODE_Input_FLO,0);

		if(G_UART2_Config->HwFlowCtl == UART_HwFlowCtl_CTS || G_UART2_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PB0 -> CTS
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_0, GPIO_MODE_Input_FLO,0);
		}
		if(G_UART2_Config->HwFlowCtl == UART_HwFlowCtl_RTS || G_UART2_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PB1 -> RTS
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_1, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		}
	}
	else if(USARTx == USART3)
	{
		//PB10 -> TX
		//PB11 -> RX
		//PB13 -> CTS
		//PB14 -> RTS


		//PB10 -> TX
		MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_10, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		//PB11 -> RX
		MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_11, GPIO_MODE_Input_FLO,0);

		if(G_UART3_Config->HwFlowCtl == UART_HwFlowCtl_CTS || G_UART3_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PB13 -> CTS
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_MODE_Input_FLO,0);
		}
		if(G_UART3_Config->HwFlowCtl == UART_HwFlowCtl_RTS || G_UART3_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS )
		{
			//PB14 -> RTS
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		}
	}
}

//========================================================================
//======================= 	  ISR Functions     ==========================
//========================================================================

void USART1_IRQHandler(void)
{
	G_UART1_Config->P_IRQ_Handler();
}
void USART2_IRQHandler(void)
{
	G_UART2_Config->P_IRQ_Handler();
}
void USART3_IRQHandler(void)
{
	G_UART3_Config->P_IRQ_Handler();
}


