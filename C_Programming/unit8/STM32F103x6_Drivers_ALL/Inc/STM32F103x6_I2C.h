/*
 * STM32F103C6_I2C.h
 *
 *  Created on: Jul 16, 2023
 *      Author: aliab
 */

#ifndef INC_STM32F103X6_I2C_H_
#define INC_STM32F103X6_I2C_H_

//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "STM32F103x6_GPIO.h"
#include "STM32F103x6_RCC.h"
#include "Math.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t 		Enable_Dual_ADD;// 1:Enable	, 0:Disable
	uint16_t		primary_slave_address;
	uint16_t		secondary_slave_address;
	uint32_t		I2C_Addressing_Slave_Mode; // @ref I2C_Addressing_Slave_Mode

}S_I2C_Slave_Device_Address_t;

typedef enum
{
	I2C_EV_STOP ,
	I2C_ERROR_AF ,
	I2C_EV_ADDR_Matched ,
	I2C_EV_DATA_REQ , //The APP Layer should send the data (I2C_Send_Data) in this state
	I2C_EV_DATA_RCV   //The APP Layer should Read the data (I2C_Receive_Data) in this state
}Slave_State;

//Configure structure
typedef struct
{
	uint32_t 								I2C_ClockSpeed; // Specifies Clock Frequency
															// This parameter set based on @ref I2C_SCLK

	uint32_t								StretchMode;	// Enable Or Disable Clock Stretch Mode
															// This parameter must be set based on @ref I2C_StretchMode

	uint32_t								I2C_Mode;		// Specifies The I2C Mode
															// This parameter must be set based on @ref I2C_Mode

	S_I2C_Slave_Device_Address_t			I2C_Slave_Address;

	uint32_t								I2C_ACK_Control;// Enable or Disable The Acknowledgement.
															// This parameter must be set based on @ref I2C_ACK_

	uint32_t 								General_Call_Address_Detection;//Enable or Disable The General call.
																			// This parameter must be set based on @ref I2C_ENGC_

	void (*P_Slave_Event_CallBack)(Slave_State state);  	// Set C Function() which will be called once the IRQ Happen .

}I2C_Config_t;

//-------------------------------
//Macros Configuration References
//-------------------------------

//@ref I2C_SCLK
//– Standard Speed (up to 100 kHz)
//– Fast Speed (up to 400 kHz)
//• to Confgure Clock before enable the peripheral
//--I2C_CR2.FREQ[5:0]: Peripheral clock frequency
//• Configure the clock control registers
//			Thigh = CCR * TPCLK1
//			SM or FM
//• Configure the rise time register I2C_TRISE
#define I2C_SCLK_SM_50K				(50000UL)
#define I2C_SCLK_SM_100K			(100000UL)
#define I2C_SCLK_FM_200K			(200000UL) // Fast Mode Not Supported yet
#define I2C_SCLK_FM_400K			(400000UL) // Fast Mode Not Supported yet


//@ref I2C_StretchMode
//I2C_CR1
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode)
//0: Clock stretching enabled
//1: Clock stretching disabled
#define I2C_StretchMode_Enable					(uint32_t)(0)
#define I2C_StretchMode_Disable					I2C_CR1_NOSTRETCH


//@ref I2C_Mode
//I2C_CR1
//Bit 1 SMBUS: SMBus mode
//0: I2C mode
//1: SMBus mode
#define I2C_Mode_I2C							(uint32_t)(0)
#define I2C_Mode_SMBus							I2C_CR1_SMBUS


// @ref I2C_Addressing_Slave_Mode
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
//0: 7-bit slave address (10-bit address not acknowledged)
//1: 10-bit slave address (7-bit address not acknowledged)
#define I2C_Addressing_Slave_Mode_7B			(uint16_t)(0)
#define I2C_Addressing_Slave_Mode_10B			(uint16_t)(1<<15)


//@ref I2C_ACK_
//I2C_CR1.ACK
//Bit 10 ACK: Acknowledge enable
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable							I2C_CR1_ACK
#define I2C_ACK_Disable							(uint16_t)(0)

//@ref I2C_ENGC_
//I2C_CR1.ENGC
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed
#define I2C_ENGC_Enable							I2C_CR1_ENGC
#define I2C_ENGC_Disable						(uint16_t)(0)

//===============================================================
typedef enum
{
	WithStop,
	WithoutStop
}Stop_Condition;

typedef enum
{
	Start,
	RepeatedStart
}Repeated_Start;

typedef enum
{ DISABLE = 0, ENABLE = 1 }Fuctional_State;

typedef enum
{ RESET = 0, SET = 1 }FlagSTATUS;

typedef enum
{
	I2C_BUS_BUSY=0,
	EV5	,	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6 ,	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV7 ,   //EV5: RxNE = 1 Cleared by Reading DR Register
	EV8 , 	//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1,	//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	EV8_2,  //EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080) /* TRA,BUSY ,MSL , TXE Flags */
}Status;

typedef enum
{
	I2C_Direction_Transmitter=0, // Write
	I2C_Direction_Receiver		 // Read
}I2C_Direction;
/*
 * ===============================================
 * APIs Supported by "MCAL I2C DRIVER"
 * ===============================================
 */

void MCAL_I2C_Init(I2C_TypeDef *I2Cx , I2C_Config_t *PinConfig);
void MCAL_I2C_DeInit(I2C_TypeDef *I2Cx);

void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef *I2Cx);


// Master Polling Mechanism

void MCAL_I2C_Master_TX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* pTxBuffer , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_TypeDef *I2Cx, uint16_t DevAddr ,uint8_t* pRxBuffer , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start);

// Slave Interrupt Mechanism

void MCAL_I2C_SlaveSendData(I2C_TypeDef *I2Cx , uint8_t data);
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef *I2Cx);





#endif /* INC_STM32F103X6_I2C_H_ */
