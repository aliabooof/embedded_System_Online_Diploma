/*
 * usart
 *
 *      Author: Aliab
 */

#ifndef INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_
#define INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_

#include "stm32f103x6.h"
#include "stm32_f103c6_gpio_drivers.h"
#include "stm32_f103c6_RCC_driver.h"


//Configuration Structure
typedef struct{
	uint8_t 		USART_mode; // Specifies the TX/RX mode.
			//This parameter must be set based on @ref USART_mode_define

	uint32_t 		baud_rate; // This configures the USART  baud rate
	//This parameter must be set based on @ref USART_baud_rate_define

	uint8_t 		data_lenght; // Specifies the number of data bits transmitted
								//or received in a frame.
	//This parameter must be set based on @ref USART_data_Length_define

	uint8_t 		parity;	//Specifies the parity mode.
		//This parameter must be set based on @ref USART_Parity_define

	uint8_t 		stop_bits; //Specifies the number of stop bits transmitted
	//This parameter must be set based on @ref USART_Stop_Bits_define

	uint8_t			hwFlCt;	 /* this is hwFlCt = hardware flow control
	Specifies whether the hardware flow control mode is enabled or disabled
	This parameter must be set based on @ref USART_HwFlCt_define*/

	uint8_t 		IRQ_enable;//Enable or disable UART IRQ TX/RX
	//This parameter must be set based on @ref USART_IRQ_Enable_define

	void(* p_IRQ_callback)(void); //The C Function() which will be called once the IRQ happen

}USART_config_t;



//-------------------------------------------------------------------
//==================Macros Configuration References==================
//-------------------------------------------------------------------

//@ref USART_mode
#define USART_MODE_RX						(uint32_t)(1<<2) //Bit 2 RE: Receiver enable
#define USART_MODE_TX						(uint32_t)(1<<3) //Bit 3 TE: Transmitter enable
#define USART_MODE_TX_RX					(uint32_t)(1<<3 | 1<<2) //For enabling both at the same time


//@ref USART_baud_rate
#define USART_BAUD_RATE_2400                   2400
#define USART_BAUD_RATE_9600                   9600
#define USART_BAUD_RATE_19200                  19200
#define USART_BAUD_RATE_57600                  57600
#define USART_BAUD_RATE_115200                 115200
#define USART_BAUD_RATE_230400                 230400
#define USART_BAUD_RATE_460800                 460800
#define USART_BAUD_RATE_921600                 921600
#define USART_BAUD_RATE_2250000                2250000
#define USART_BAUD_RATE_4500000                4500000


//@ref USART_data_Length
#define USART_DATA_LENGHT_8B				(uint32_t)(0) //0: 1 Start bit, 8 Data bits, n Stop bit
#define USART_DATA_LENGHT_9B				(uint32_t)(1<<12) //1: 1 Start bit, 9 Data bits, n Stop bit


//@ref USART_Parity
#define USART_PARITY_NONE            	    (uint32_t)(0)
#define USART_PARITY_EVEN              	((uint32_t)1<<10)
#define USART_PARITY_ODD               	((uint32_t)(1<<10 | 1<<9))


//@ref USART_Stop_Bits
/*Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit*/
#define USART_STOP_BITS_half        	    (uint32_t)(1<<12)
#define USART_STOP_BITS_1        	        (uint32_t)(0)
#define USART_STOP_BITS_1_half          	(uint32_t)(3<<12)
#define USART_STOP_BITS_2           	    (uint32_t)(2<<12)


//@ref USART_HwFlCt
#define	USART_HWFLCT_NONE					(uint32_t)(0)
#define	USART_HWFLCT_RTS					(uint32_t)(1<<8)
#define	USART_HWFLCT_CTS					(uint32_t)(1<<9)
#define	USART_HWFLCT_RTS_CTS				(uint32_t)(1<<9 | 1<<8)

//@ref UART_IRQ_Enable
//You can select two or three parameters EX.USART_IRQ_Enable_TXE |USART_IRQ_Enable_TC
#define USART_IRQ_ENABLE_NONE                (uint32_t)(0)
#define USART_IRQ_ENABLE_TXE                 (uint32_t)(1<<7) //Transmit data register empty
#define USART_IRQ_ENABLE_TC                  (uint32_t)(1<<6) //Transmission complete
#define USART_IRQ_ENABLE_RXNEIE              (uint32_t)(1<<5) //Received data ready to be read & Overrun error detected
#define USART_IRQ_ENABLE_PE                  (uint32_t)(1<<8) //Parity error



enum polling{
	enable,
	disable
};



//------------------------------------------------------------------------------------------
//								APIs supported by "MCAL USART Driver"
//------------------------------------------------------------------------------------------

//Initializations APIs
void MCAL_USART_init(USART_Typedef * USARTX,USART_config_t * config);
void MCAL_USART_deinit(USART_Typedef * USARTX);

//GPIO related functions
void MCAL_USART_set_pins(USART_Typedef * USARTX);

//Transmission functions
void MCAL_USART_send_data(USART_Typedef * USARTX, uint16_t* data, enum polling poll);
void MCAL_USART_recive_data(USART_Typedef * USARTX, uint16_t* data, enum polling poll);

void MCAL_USART_TC_status(USART_Typedef * USARTX); //Checks if the transmission has completed or not







#endif /* INCLUDE_FOLDER_STM32_F103C6_USART_DRIVER_H_ */
