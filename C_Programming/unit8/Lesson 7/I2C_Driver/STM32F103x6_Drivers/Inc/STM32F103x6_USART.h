/*
 * STM32F103C6_GPIO.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */

#ifndef INC_STM32F103X6_USART_H_
#define INC_STM32F103X6_USART_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103x6_GPIO.h"
#include "STM32F103x6_RCC.h"

//Configure structure
typedef struct
{
	uint8_t 		USART_Mode; 	// Specifies TX/RX Enable or Disable
									// This parameter set based on @ref UART_Mode_Define

	uint32_t		BaudRate;		// This Member Configure UART Communication Baud Rate
									// This parameter must be set based on @ref UART_Baud_Rate_Define

	uint8_t			Payload_Length; // Specifies the number of data Transmit/Receive in a frame
									// This parameter must be set based on @ref UART_Payload_Length_Define

	uint8_t			Parity_Mode;	// Specifies Parity Mode
									// This parameter must be set based on @ref UART_Parity_Define

	uint8_t			StopBits;		// Specifies the number of stop bits Transmitted
									// This parameter must be set based on @ref UART_StopBits_Define

	uint8_t			HwFlowCtl;		// Specifies Flow Control Mode
									// This parameter must be set based on @ref UART_FlowControl_Define

	uint8_t			IQR_Enable;		// Specifies Interrupt Enable or Disable
									// This parameter must be set based on @ref UART_IRQ_Enable_Define
	void (*P_IRQ_Handler)(void);  	// Set C Function() which will be called once the IRQ Happen .

}UART_Config;




//--------------------------------------
//===========Reference Macros===========
//--------------------------------------

//@ref UART_Mode_define
#define UART_MODE_TX					(uint32_t)(1<<3)//Bit 3 TE: Transmitter enable
#define UART_MODE_RX	 				(uint32_t)(1<<2)//Bit 2 RE: Receiver enable
#define UART_MODE_TX_RX					(uint32_t)(1<<3 | 1<<2)

//@ref UART_Baud_Rate_Define
#define UART_BAUD_RATE_2400				2400
#define UART_BAUD_RATE_9600				9600
#define UART_BAUD_RATE_19200			19200
#define UART_BAUD_RATE_57600			57600
#define UART_BAUD_RATE_115200			115200
#define UART_BAUD_RATE_230400			230400
#define UART_BAUD_RATE_460800			460800
#define UART_BAUD_RATE_921600			921600
#define UART_BAUD_RATE_2250000			2250000
#define UART_BAUD_RATE_4500000			4500000

//@ref UART_Payload_Length_Define
#define UART_PayLoad_Length_8B			(uint32_t)(0)
#define UART_PayLoad_Length_9B			(uint32_t)(1<<12)

//@ref UART_Parity_Define
#define UART_Parity_Mode_NONE			(uint32_t)(0)
#define UART_Parity_Mode_EVEN			(uint32_t)(1<<10)    		//(2<<9)// Enable  Even Parity
#define UART_Parity_Mode_ODD			(uint32_t)(1<<10 | 1<<9)    //(3<<9)// Enable  Odd Parity

//@ref UART_StopBits_Define
#define UART_StopBits__Half				(uint32_t)(1<<12)
#define UART_StopBits__1				(uint32_t)(0)
#define UART_StopBits__1_Half			(uint32_t)(3<<12)
#define UART_StopBits__2				(uint32_t)(2<<12)

//@ref UART_FlowControl_Define
#define UART_HwFlowCtl_NONE				(uint32_t)(0)
#define UART_HwFlowCtl_RTS				(uint32_t)(1<<8)
#define UART_HwFlowCtl_CTS				(uint32_t)(1<<9)
#define UART_HwFlowCtl_RTS_CTS			(uint32_t)(1<<9 | 1<<8)

//@ref UART_IRQ_Enable_Define
#define UART_IRQ_Enable_NONE			(uint32_t)(0)
#define UART_IRQ_Enable_TXE				(uint32_t)(1<<7)//Enable  Transmit data register empty
#define UART_IRQ_Enable_RXNE			(uint32_t)(1<<5)//Enable  Received data ready to be read
#define UART_IRQ_Enable_TC				(uint32_t)(1<<6)//Enable  Transmission complete
#define UART_IRQ_Enable_PE				(uint32_t)(1<<8)//Enable  Parity Error

enum Polling_Mechanism
{
	enable ,
	disable
};

// Calculate BAUD_RATE
//USARTDIV = fclk / (16 * Baudrate)
//USARTDIV_MUL100 = (uint32)((100 *fclk ) / (16 * Baudrate) == (25 *fclk ) / (4* Baudrate) )
//DIV_Mantissa_MUL100 = Integer Part (USARTDIV ) * 100
//DIV_Mantissa = Integer Part (USARTDIV )
//DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16 ) / 100
#define USARTDIV(_CLCK_ , _BAUDRate_)				(uint32_t)((_CLCK_ )/(_BAUDRate_ * 16))
#define DIV_MANTISSA(_CLCK_ , _BAUDRate_)			(uint32_t)USARTDIV(_CLCK_ , _BAUDRate_)
#define USARTDIV_MUL100(_CLCK_ , _BAUDRate_)		(uint32_t)((_CLCK_ * 25)/(_BAUDRate_ * 4))
#define MANTISSA_MUL100(_CLCK_ , _BAUDRate_)		(uint32_t)(DIV_MANTISSA(_CLCK_ , _BAUDRate_) * 100)
#define	DIV_FRACTION(_CLCK_ , _BAUDRate_)			(uint32_t)(((USARTDIV_MUL100(_CLCK_ , _BAUDRate_) - MANTISSA_MUL100(_CLCK_ , _BAUDRate_))*16)/100)
#define USART_BRR_Register(_CLCK_ , _BAUDRate_)		((DIV_MANTISSA(_CLCK_ , _BAUDRate_) << 4 ) | ((DIV_FRACTION(_CLCK_ , _BAUDRate_)) & 0xF))



/*
 * ===============================================
 * APIs Supported by "MCAL USART DRIVER"
 * ===============================================
 */

// initialization/de_initialization of USART Peripheral
void MCAL_UART_Init(USART_TypeDef * USARTx , UART_Config * UART_Config);
void MCAL_UART_DeInit(USART_TypeDef * USARTx);

void MCAL_UART_GPIO_Set_Pins(USART_TypeDef * USARTx);

void MCAL_UART_SendData(USART_TypeDef * USARTx, uint16_t* pTxBuffer , enum Polling_Mechanism PollingEn);
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx, uint16_t* pRxBuffer , enum Polling_Mechanism PollingEn);


void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx);
//void MCAL_USART_Handling_Init(USART_TypeDef * USARTx,uint32_t BaudRate , uint8_t HwFlowCtl,uint8_t Parity_Mode,uint8_t IQR_Enable ,uint8_t Payload_Length,uint8_t StopBits,uint8_t USART_Mode,void (*Ptr_IRQ_Handler)(void));

//todo MCAL_USART_LIN_Init() 		//LIN
//todo MCAL_USART_Init() 			//Synchronous
//todo MCAL_USART_DMA_Init() 		//MultiBuffer Communication


#endif /* INC_STM32F103X6_USART_H_ */
