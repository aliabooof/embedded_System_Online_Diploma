
/*
 * STM32F103C6_SPI_Driver.h
 *
 *  Created on: Sep 2, 2023
 *      Author: aliab
 */

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_



//-----------------------------
//Includes
//-----------------------------
#include "STM32_F103X6.h"
#include "STM32_F103C6_GPIO_Driver.h"

//=========================================================================


//Configuration structure

typedef struct{
	uint8_t TXE:1; //TX buffer empty interrupt
	uint8_t RXNE:1;//RX buffer not empty interrupt
	uint8_t ERRI:1;//Error interrupt
	uint8_t reserved:5;
}IRQ_SPI_src_t;


typedef struct{
	uint16_t 		device_mode; 		//Specifies the SPI operating mode @ref SPI_device_mode
	uint16_t 		communication_mode; //Specifies the SPI bidirectional mode  sate @ref SPI_communication_mode
	uint16_t 		frame_format; 		//Specifies LSB or MSB @ref SPI_frame_format
	uint16_t 		data_size; 			//@ref SPI_data_size
	uint16_t 		CLK_polarity; 		//@ref SPI_CLK_polarity
	uint16_t 		CLK_phase; 			//@ref SPI_CLK_phase

	uint16_t 		NSS; /*Specifies whether the NSS signal is managed by hardware (NSS pin)
	 *or by software using the SSI bit enable @ref SPI_NSS*/

	uint16_t		baud_rate_prescaler; /*Specifies the baud rate prescaler value which will be
	 *used to configure the transmit and receive SCK clock. This parameter can be
	 *a value of @ref SPI_baud_rate_prescaler. NOTE the communication clock is derived
	 *from the master clock. The slave clock does not need to be set.
	 *Take care you have to configure RCC to enter the correct clock to APB2 >>> to SPI */

	uint16_t 		IRQ_enable; 		//@ref SPI_IRQ_enable
	void(* p_IRQ_callback)(IRQ_SPI_src_t irq_src); //The C Function() which will be called once the IRQ happen
}SPI_config_t;

typedef enum{
	pollingEnable,
	pollingDisable
}pollingMechnism;


//-------------------------------------------------------------------
//==================Macros Configuration References==================
//-------------------------------------------------------------------

//@ref SPI_device_mode
#define SPI_DEVICE_MODE_SLAVE										(uint16_t)(0)
#define SPI_DEVICE_MODE_MASTER										(uint16_t)(1<<2) // CR1. MSTR 1: Master configuration

//@ref SPI_communication_mode
#define SPI_DIRECTION_2LINES										(uint16_t)(0)
#define SPI_DIRECTION_2LINES_RX_ONLY								(uint16_t)(1<<10) //CR1. bit 10 RXONLY: receive only
#define SPI_DIRECTION_1LINE_RECIVE_ONLY								(uint16_t)(1<<15) //CR1. bit 15 BIDIMODE: bidirectional data mode enable
#define SPI_DIRECTION_1LINE_TRANSMIT_ONLY							(uint16_t)((1<<15) | (1<<14)) // CR1. bit 14 BIDOE: output enable in bidirectional mode

//@ref SPI_frame_format
#define SPI_DATA_SIZE_8BIT											(uint16_t)(0)
#define SPI_DATA_SIZE_16BIT											(uint16_t)(1<<11) //CR1. bit 11 DFF: data size format

////@ref SPI_data_size
#define SPI_FRAME_FORMAT_MSB										(uint16_t)(0)
#define SPI_FRAME_FORMAT_LSB										(uint16_t)(1<<7) //CR1. bit 7 LSBFIRST : sending LSB first

//@ref SPI_CLK_polarity
#define SPI_CLK_POLARITY_IDLE_LOW									(uint16_t)(0)
#define SPI_CLK_POLARITY_IDLE_HIGH									(uint16_t)(1<<1) //CR1. bit 1 CPOL: clock polarity

//@ref SPI_CLK_phase
#define SPI_CLK_PHASE_EDGE1_DATA_CAPTURE							(uint16_t)(0)
#define SPI_CLK_PHASE_EDGE2_DATA_CAPTURE							(uint16_t)(1<<0)

//@ref SPI_NSS
//=====================NSS=====================
//Hardware
#define SPI_NSS_HW_SLAVE											(uint16_t)(0)
#define	SPI_NSS_HW_MASTER_SS_OUTPUT_DISABLE							(uint16_t)(~(1<<2))//CR2. bit 2 SSOE: SS output disable
#define	SPI_NSS_HW_MASTER_SS_OUTPUT_ENABLE							(uint16_t)(1<<2)//CR2. bit 2 SSOE: SS output enable



//NSS is driven by Software (Master or Slave)
#define SPI_NSS_SW_NSS_INTERNAL_SOFT_RESET							(uint16_t)(1<<9)
#define SPI_NSS_SW_NSS_INTERNAL_SOFT_SET							(uint16_t)((1<<9) | (1<<8))
//============================================


//@ref SPI_baud_rate_prescaler
#define SPI_BAUD_RATE_PRESCALER_2									(uint16_t)(0)
#define SPI_BAUD_RATE_PRESCALER_4									(uint16_t)(0b001<<3)
#define SPI_BAUD_RATE_PRESCALER_8									(uint16_t)(0b010<<3)
#define SPI_BAUD_RATE_PRESCALER_16									(uint16_t)(0b011<<3)
#define SPI_BAUD_RATE_PRESCALER_32									(uint16_t)(0b100<<3)
#define SPI_BAUD_RATE_PRESCALER_64									(uint16_t)(0b101<<3)
#define SPI_BAUD_RATE_PRESCALER_128									(uint16_t)(0b110<<3)
#define SPI_BAUD_RATE_PRESCALER_256									(uint16_t)(0b11 1<<3)

//@ref SPI_IRQ_enable
#define SPI_IRQ_ENABLE_NONE											(uint16_t)(0)
#define SPI_IRQ_ENABLE_TXEIE										(uint16_t)(1<<7)//CR2
#define SPI_IRQ_ENABLE_RXNEIE										(uint16_t)(1<<6)//CR2
#define SPI_IRQ_ENABLE_ERRIE										(uint16_t)(1<<5)//CR2


//------------------------------------------------------------------------------------------
//								APIs supported by "MCAL SPI Driver"
//------------------------------------------------------------------------------------------
//Initializations APIs
void MCAL_SPI_init(SPI_Typedef * SPIx,SPI_config_t * config);
void MCAL_SPI_deinit(SPI_Typedef * SPIx);

//GPIO related functions
void MCAL_SPI_set_pins(SPI_Typedef * SPIx);

//Transmission functions
void MCAL_SPI_send_date(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn);
void MCAL_SPI_receive_date(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn);
//For transmitting and receiving at the same time
void MCAL_SPI_TX_RX(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn);





#endif /* SPI_DRIVER_H_ */
