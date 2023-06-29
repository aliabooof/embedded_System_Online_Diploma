/*
 * usart
 *
 *      Author: Aliab
 */

#ifndef INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_
#define INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_

/* ========================================== Includes ================================================= */
#include "stm32_f103x6.h"
#include "STM32_F103C6_USART_Driver.h"
#include "Stm32_f103c6_Drivers_Gpio.h"


/* ========================================== Macros ================================================= */


/* ========================================== Configuration Structure ================================================= */
typedef struct
{
	uint8_t					USART_Mode;				// Specifies Tx/Rx Enable or Disable
													// This parameter must be set based on @ref UART_Mode_define

	uint32_t				BaudRate;				// This member configures the UART communication baud rate
													// This parameter must be set based on @ref UART_BaudRate_define

	uint8_t					Payload_Length;			// Specifies the number of data bits transmitted or received in a frame
													// This parameter must be set based on @ref UART_Payload_Length_define

	uint8_t 				Parity;					// Specifies the parity mode
													// @ref UART_Parity_define

	uint8_t					StopBits;				// Specifies the number of stop bits transmitted
													// @ref UART_StopBits_define

	uint8_t					HardwareFlowControl;	// Specifies whether the hardware flow control mode is enabled or disabled
													// @ref UART_HardwareFlowControl_define

	uint8_t					IRQ_Enable;				// Enable or Disable UART IRQ Tx/Rx
													// @ref UART_IRQ_Enable_define , you can select two or three parameters

	void(* P_IRQ_CallBack)(void);					// Set the C function() which will be called once the IRQ happens
}USART_TypeDef;

/* ========================================== Reference Macros ================================================= */

//@ref UART_Mode_define
#define UART_Mode_Rx				(uint32_t)(1<<2)			// Bit 2 RE: Receiver enable
#define UART_Mode_Tx				(uint32_t)(1<<3)			// Bit 3 TE: Transmitter enable
#define UART_Mode_Tx_Rx				(uint32_t)(1<<2 | 1<<3)

//@ref UART_BaudRate_define
#define UART_BaudRate_2400				2400
#define UART_BaudRate_9600				9600
#define UART_BaudRate_19200				19200
#define UART_BaudRate_57600				57600
#define UART_BaudRate_115200			115200
#define UART_BaudRate_230400			230400
#define UART_BaudRate_460800			460800
#define UART_BaudRate_921600			921600
#define UART_BaudRate_2250000			2250000
#define UART_BaudRate_4500000			4500000

//@ref UART_Payload_Length_define
#define UART_Payload_Length_8B			(uint32_t)(0)
#define UART_Payload_Length_9B			(uint32_t)(1<<12)

//@ref UART_Parity_define
#define UART_Parity_NONE				(uint32_t)(0)
#define UART_Parity_EVEN				((uint32_t)1<<10)
#define UART_Parity_ODD					((uint32_t)(1<<10 | 1<<9))

//@ref UART_StopBits_define
#define UART_StopBits_half				(uint32_t)(1<<12)
#define UART_StopBits__1				(uint32_t)(0)
#define UART_StopBits__1_half			(uint32_t)(3<<12)
#define UART_StopBits__2				(uint32_t)(2<<12)

//@ref UART_HardwareFlowControl_define
#define UART_HardwareFlowControl_NONE			(uint32_t)(0)
#define UART_HardwareFlowControl_RTS			((uint32_t)1<<8)
#define UART_HardwareFlowControl_CTS			((uint32_t)1<<9)
#define UART_HardwareFlowControl_RTS_CTS		((uint32_t)(1<<8 | 1<<9))

//@ref UART_IRQ_Enable_define
#define UART_IRQ_Enable_NONE					(uint32_t)(0)
#define UART_IRQ_Enable_TXE						(uint32_t)(1<<7)	// Transmit data register empty
#define UART_IRQ_Enable_TC						(uint32_t)(1<<6)	// Transmission complete
#define UART_IRQ_Enable_RXNEIE					(uint32_t)(1<<5)	// Received data ready to be read
#define UART_IRQ_Enable_PE						(uint32_t)(1<<8)	// Parity Error



enum Polling_Mechanism{
	enable,
	disable
};

// BaudRate Calculation
// USARTDIV = fclk / (16 * BaudRate)
// USARTDIV_MUL100 =
//  uint32_t((100 * fclk) / (16 * BaudRate) == (25 * fclk) / (4 * BaudRate))
// DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
// DIV_Mantissa = Integer Part (USARTDIV)
// DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) * 16) / 100

#define USARTDIV(_PCLK_, _BAUD_)								(uint32_t) (_PCLK_ / (16 * _BAUD_))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)							(uint32_t) ((25 * _PCLK_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)							(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)								(uint32_t) (USARTDIV(_PCLK_, _BAUD_))
#define DIV_Fraction(_PCLK_, _BAUD_)							(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) - Mantissa_MUL100(_PCLK_, _BAUD_)) * 16) / 100)
#define UART_BRR_Register(_PCLK_, _BAUD_)						(uint32_t) ((Mantissa(_PCLK_, _BAUD_)) << 4) | ((DIV_Fraction(_PCLK_, _BAUD_)) & 0xF)




/* ========================================== APIs Prototype ================================================= */

// -------------------------------------------------------------
// ----- Initialization / DeInitialization Functions -----------
// -------------------------------------------------------------
void MCAL_UART_Init (USART_TypeDef* USARTx, UART_Config* UART_Config);
void MCAL_UART_DeInit (USART_TypeDef* USARTx);

// -------------------------------------------------
// ----- Set Pin Function --------------------------
// -------------------------------------------------
void MCAL_UART_GPIO_Set_Pins (USART_TypeDef *USARTx);

// -------------------------------------------------
// ----- Send and Receive Functions ----------------
// -------------------------------------------------
void MCAL_UART_SendData (USART_TypeDef* USARTx, uint16_t* pTxBuffer, enum Polling_Mechanism Polling_Enable);
void MCAL_UART_ReceiveData (USART_TypeDef *USARTx, uint16_t *pTxBuffer, enum Polling_Mechanism Polling_Enable);

// -------------------------------------------------
// ----- Wait Transmit Completed Function ----------
// -------------------------------------------------
void MCAL_UART_Wait_TC (USART_TypeDef *USARTx);


// -------------------------------------------------
// ----- ToDo In Future Functions ------------------
// -------------------------------------------------
// MCAL_USART_LIN_Init()			// LIN
// MCAL_USART_Init()				// Synchronous
// MCAL_USART_DMA_Init()			// Multi-Buffer Communication














#endif /* INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_ */
