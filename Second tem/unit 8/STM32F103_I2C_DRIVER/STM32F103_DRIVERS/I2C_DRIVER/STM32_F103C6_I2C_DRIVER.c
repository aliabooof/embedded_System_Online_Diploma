/*
 * STM32F103C6_I2C.c
 *
 *  Created on: Jul 16, 2023
 *      Author: aliab

 */


#include "../inc/STM32_F103C6_I2C_DRIVER.h"


//================================================================
//				Generic Variables
//================================================================

I2C_Config_t  G_I2C_PinConfig[2] = { 0,
									0};

//================================================================
//				Generic Macros
//================================================================
#define I2C1_INDEX				0
#define I2C2_INDEX				1

//================================================================
//				Generic Functions
//================================================================

FlagSTATUS I2C_GetFlagSTATUS(I2C_Typedef *I2Cx, Status Flag)
{
	volatile uint32_t dummyRead;
	uint32_t flag1 = 0 ,flag2 = 0;
	uint32_t lastevent = 0;
	FlagSTATUS bitstatus = RESET;

	switch(Flag)
	{
	case I2C_BUS_BUSY:
	{
		//		Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0).
		if((I2Cx->SR2) & (I2C_SR2_BUSY))
			bitstatus = SET ;
		else
			bitstatus = RESET;
		break;
	}
	case EV5:
	{
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if((I2Cx->SR1) & (I2C_SR1_SB))
			bitstatus = SET ;
		else
			bitstatus = RESET;
		break;
	}
	case EV6:
	{
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		// to perform the complete clearing sequence (READ SR1 then READ SR2) after ADDR is set.
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//		when PE=0.
		//		Address matched (Slave)
		//		0: Address mismatched or not received.
		//		1: Received address matched
		if( (I2Cx->SR1) & (I2C_SR1_ADDR))
			bitstatus = SET ;
		else
			bitstatus = RESET;
		break;
	}
	case MASTER_BYTE_TRANSMITTING:
	{
		// Read I2C Status Register
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		// Get the last event value from I2C Status Register
		lastevent = ((flag2 | flag1) & (uint32_t)0x00FFFFFF);
		//Check whether the last event contains the I2C_EVENT
		if( (lastevent & MASTER_BYTE_TRANSMITTING) == MASTER_BYTE_TRANSMITTING)
		{
			/* SUCCESS: last event is equal to I2C_EVENT */
			bitstatus = SET ;
		}
		else
		{
			/* ERROR: last event is different from I2C_EVENT */
			bitstatus = RESET;
		}
		break;
	}
	case EV8_1://EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8://EV8: TxE=1, shift register not empty, d. ata register empty, cleared by writing DR register
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		if(I2Cx->SR1 & (I2C_SR1_TXE))
		{
			bitstatus = SET ;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV8_2://EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		//----------------------------------------------
		//		Bit 2 BTF: Byte transfer finished
		//		0: Data byte transfer not done
		//		1: Data byte transfer succeeded
		if( (I2Cx->SR1 & (I2C_SR1_TXE))  &&  (I2Cx->SR1 & (I2C_SR1_BTF)))
		{
			bitstatus = SET ;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	case EV7://EV5: RxNE = 1 Cleared by Reading DR Register
	{
		//		Bit 6 RxNE: Data register not empty (receivers)
		//		0: Data register empty
		//		1: Data register not empty
		if(I2Cx->SR1 & (I2C_SR1_RXNE))
		{
			bitstatus = SET ;
		}
		else
		{
			bitstatus = RESET;
		}
		break;
	}
	}
	return bitstatus;
}

//supported only 7 bit mode
void I2C_AcknowledgeConfig(I2C_Typedef *I2Cx, Fuctional_State NewState)
{
	if(NewState == ENABLE)
	{
		/* Enable the Acknowledgment */
		I2Cx->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		/* Disable the Acknowledgment */
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}

void I2C_GenerateSTART(I2C_Typedef *I2Cx, Fuctional_State NewState, Repeated_Start Start)
{
	if(Start != RepeatedStart)
	{
		//Check if bus is idle
		while(I2C_GetFlagSTATUS(I2Cx, I2C_BUS_BUSY));
	}
	//	Bit 8 START: Start generation
	//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
	//	In Master Mode:
	//	0: No Start generation
	//	1: Repeated start generation
	//	In Slave mode:
	//	0: No Start generation
	//	1: Start generation when the bus is free
	if(NewState == ENABLE)
	{
		/*Generate a START Condition*/
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		/*Disable The START Condition Generation*/
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}

void I2C_GenerateSTOP(I2C_Typedef *I2Cx, Fuctional_State NewState)
{
	if(NewState == ENABLE)
	{
		/*Generate a START Condition*/
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		/*Disable The START Condition Generation*/
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

void I2C_SendAddress(I2C_Typedef *I2Cx, uint16_t Address, I2C_Direction Direction)
{
	Address = (Address << 1);

	if(Direction == I2C_Direction_Transmitter)
	{
		/*Reset the address bit0 for write*/
		Address &= ~(1<<0);
	}
	else  //I2C_Direction_Receiver
	{
		/*Set the address bit0 for Read*/
		Address |= (1<<0);
	}
	/*Send The Address*/
	I2Cx->DR = Address ;
}

void Slave_States(I2C_Typedef *I2Cx,Slave_State State)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX ;

	switch(State)
	{
	case I2C_ERROR_AF:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Slave shouldn't send anything else
		}
		break;

	case I2C_EV_STOP:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//Notify APP that the Stop Condition is Sent by the master
			G_I2C_PinConfig[index].P_Slave_Event_CallBack(I2C_EV_STOP);
		}
		break;

	case I2C_EV_ADDR_Matched:
		//Notify APP that The address is matched with The slave address
		G_I2C_PinConfig[index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
		break;

	case I2C_EV_DATA_REQ:
		//make sure that the slave is really in transmitter mode
		if(I2Cx->SR2 & (I2C_SR2_TRA))
		{
			//The APP Layer should send the data (MCAL_I2C_SlaveSendData)in this state
			G_I2C_PinConfig[index].P_Slave_Event_CallBack(I2C_EV_DATA_REQ);
		}

		break;

	case I2C_EV_DATA_RCV:
		//make sure that the slave is really in receiver mode
		if(!(I2Cx->SR2 & (I2C_SR2_TRA)) )
		{
			//The APP Layer should read the data (MCAL_I2C_SlaveReceiveData)in this state
			G_I2C_PinConfig[index].P_Slave_Event_CallBack(I2C_EV_DATA_RCV);
		}

		break;
	}
}
//================================================================
//				APIs Functions Definition
//================================================================

/* ================================================================
 * @Fn 				- MCAL_I2C_Init
 * @brief 			- Initializes I2Cx according to the specified parameters in I2C_Config
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- I2C_Config : a pointer to I2C_Config_t structure that contains the configuration information for the specified I2C Module
 * @retval 			- None
 * Note 			- Supported for I2C SM mode only
 * 					- Support only 7-bit address mode
 */
void MCAL_I2C_Init(I2C_Typedef *I2Cx , I2C_Config_t *PinConfig)
{
	uint16_t tmpreg=0 , freqrange=0 , result=0;
	uint32_t pclk1 = 8000000;
	//Enable RCC Clock
	if(I2Cx == I2C1)
	{
		G_I2C_PinConfig[I2C1_INDEX] = *PinConfig;
		RCC_I2C1_CLK_EN();
	}
	else if(I2Cx == I2C2)
	{
		G_I2C_PinConfig[I2C2_INDEX] =  *PinConfig;
		RCC_I2C2_CLK_EN();
	}

	if(PinConfig->I2C_Mode == I2C_Mode_I2C)
	{
		/*----------------- INIT Timing --------------------*/

		//--I2C_CR2.FREQ[5:0]: Peripheral clock frequency
		//get I2C_CR2 Register value
		tmpreg = I2Cx->CR2;
		// clear Frequency FREQ[5:0] bits
		tmpreg &= ~(I2C_CR2_FREQ_Msk);
		//get pclk1 frequency value
		pclk1 = MCAL_RCC_getPCLK1Freq();
		//set frequency bits depending on pclk1 value
		freqrange = (uint16_t)(pclk1/1000000);

		tmpreg |= freqrange ;
		//Write to I2Cx->CR2
		I2Cx->CR2 = tmpreg;

		//• Configure the clock control registers I2Cx->CCR

		// Disable the selected I2C peripheral to configure Time
		I2Cx->CR1 &= ~(I2C_CR1_PE);

		tmpreg =0;
		if( (PinConfig->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (PinConfig->I2C_ClockSpeed == I2C_SCLK_SM_100K) )
		{
			//Bit 15 F/S: I2C master mode selection
			//0: Sm mode I2C
			//1: Fm mode I2C
			//by default Bit 15 = 0 ->> SM Mode
			/*-------------------------------------*/

			//Standard Mode Speed Calculation
			// Thigh = CCR * TPCLK1
			// Thigh = Tclk /2
			// CCR = Tclk / (2 * TPCLK1)
			// CCR = Fpclk1 / (2 * I2C_Clock_Frequency)
			result = (pclk1 / (PinConfig->I2C_ClockSpeed << 1) );

			tmpreg |= result;

			//Write to I2Cx->CCR
			I2Cx->CCR = tmpreg;

			/*--------------I2C_TRISE Configuration--------------*/
			//For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			//If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//therefore the TRISE[5:0] bits must be programmed with 09h
			//(1000 ns / 125 ns = 8 + 1)
			I2Cx->TRISE = freqrange + 1 ;
		}
		else
		{
			//Fast Mode is Not Supported
		}

		//Get I2Cx->CR1 value
		tmpreg = I2Cx->CR1 ;

		tmpreg |= (uint16_t)(PinConfig->I2C_ACK_Control | PinConfig->StretchMode | PinConfig->General_Call_Address_Detection | PinConfig->I2C_Mode);

		//Write to I2Cx->CR2
		I2Cx->CR1 = tmpreg ;

		/*--------------I2C_OAR1 & I2C_OAR2 Configuration--------------*/
		tmpreg = 0;
		if(PinConfig->I2C_Slave_Address.Enable_Dual_ADD == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL ;
			tmpreg |= PinConfig->I2C_Slave_Address.secondary_slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tmpreg ;
		}
		tmpreg = 0;
		tmpreg |= PinConfig->I2C_Slave_Address.primary_slave_address << 1;
		tmpreg |= PinConfig->I2C_Slave_Address.I2C_Addressing_Slave_Mode ;
		I2Cx->OAR1 = tmpreg ;
	}
	else
	{
		//SMBUS is Not Supported
	}

	// Interrupt Mode (Slave Mode) //check callback pointer != NULL
	if( PinConfig->P_Slave_Event_CallBack != NULL) // that enable IRQ States Mode
	{
		//Enable IRQ
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_ENABLE();
			NVIC_IRQ32_I2C1_ER_ENABLE();
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_ENABLE();
			NVIC_IRQ33_I2C2_EV_ENABLE();
		}
		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}
	// Enable The selecte I2C Peripheral
	I2Cx->CR1 |= I2C_CR1_PE ;

}
/* ================================================================
 * @Fn 				- MCAL_I2C_DeInit
 * @brief 			- Resets Selected I2C Module and disable NVIC IRQs
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Reset The Module By RCC & Disable NVIC
 */
void MCAL_I2C_DeInit(I2C_Typedef *I2Cx)
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_ENABLE();
		NVIC_IRQ32_I2C1_ER_ENABLE();
		RCC_I2C1_RESET();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_ENABLE();
		NVIC_IRQ34_I2C2_ER_ENABLE();
		RCC_I2C2_RESET();
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_GPIO_Set_Pins
 * @brief 			- Initializes GPIO Pins to be connected with the selected I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- None
 * Note 			- Must open clock for AFIO & GPIO After GPIO Initialization
 * 					- Supported for I2C SM MODE only
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_Typedef *I2Cx)
{
	GPIO_PIN_Config_t Pincfg;

		Pincfg.GPIO_PinMode = GPIO_MODE_ANALOG_AF_OD;
		Pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;

		if(I2Cx == I2C1){
			//I2C1_SCL PB6
			Pincfg.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_Init(GPIOB,&Pincfg);

			//I2C1_SDA PB7
			Pincfg.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_Init(GPIOB,&Pincfg);

		}else if(I2Cx == I2C2){
			//I2C2_SCL PB10
			Pincfg.GPIO_PinNumber = GPIO_PIN_10;
			MCAL_GPIO_Init(GPIOB,&Pincfg);

			//I2C2_SDA PB11
			Pincfg.GPIO_PinNumber = GPIO_PIN_11;
			MCAL_GPIO_Init(GPIOB,&Pincfg);
		}
}
/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_TX
 * @brief 			- Master Send data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- DevAddr : slave address
 * @param [in] 		- pTxBuffer : a pointer to the data which will be send
 * @param [in] 		- datalen : number of data bytes to be Transmitted
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_TX(I2C_Typedef *I2Cx, uint16_t DevAddr ,uint8_t* pTxBuffer , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	int i = 0;
	//todo: support timeout(configure timer working for specific duration rise interrupt
	//timer_interrupt(){ flag = 1 }
	//so any code exist in while(check flag || any polling conditions)

	//1. Set The START bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, ENABLE, Start);

	//2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagSTATUS(I2Cx, EV5));

	//3. Send Address
	I2C_SendAddress(I2Cx, DevAddr, I2C_Direction_Transmitter);

	//4. Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagSTATUS(I2Cx, EV6));

	//5. /* TRA(Transmit/Receive) ,BUSY ,MSL(Master/Receive) , TXE Flags(Transmit is empty) */
	while(!I2C_GetFlagSTATUS(I2Cx, MASTER_BYTE_TRANSMITTING));

	for(i=0;i<datalen;i++)
	{
		/* Write on the Data Register the data to be sent */
		I2Cx->DR = pTxBuffer[i];
		//6. Wait for EV8
		//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
		while(!I2C_GetFlagSTATUS(I2Cx, EV8));
	}

	//7. Wait for EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	while(!I2C_GetFlagSTATUS(I2Cx, EV8_2));

	if(Stop == WithStop)
	{
		//8. Send Stop Condition
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

}

/* ================================================================
 * @Fn 				- MCAL_I2C_MASTER_RX
 * @brief 			- Master Receive data with I2C
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- DevAddr : slave address
 * @param [in] 		- pRxBuffer : a pointer to the data which will be send
 * @param [in] 		- datalen : number of data bytes to be Received
 * @param [in] 		- Stop : select send stop bit or not
 * @param [in] 		- Start : select send start or repeated start
 * @retval 			- None
 * Note 			- None
 */
void MCAL_I2C_Master_RX(I2C_Typedef *I2Cx, uint16_t DevAddr ,uint8_t* pRxBuffer , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	int i = 0;

	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX : I2C2_INDEX ;

	//1. Set The START bit in the I2C_CR1 register to generate a start condition
	I2C_GenerateSTART(I2Cx, ENABLE, Start);

	//2. Wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_GetFlagSTATUS(I2Cx, EV5));

	//3. Send Address
	I2C_SendAddress(I2Cx, DevAddr, I2C_Direction_Receiver);

	//4. Wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagSTATUS(I2Cx, EV6));

	I2C_AcknowledgeConfig(I2Cx , ENABLE);

	if(datalen)
	{
		//Read Until Data Length become Zero
		for(i = datalen ; i > 1 ; i--)
		{
			//5. Wait Until RxNE become 1
			//EV5: RxNE = 1 Cleared by Reading DR Register
			while(!I2C_GetFlagSTATUS(I2Cx, EV7));
			//read the data from data register
			*pRxBuffer = I2Cx->DR ;
			//increment the buffer address
			pRxBuffer++;
		}
		I2C_AcknowledgeConfig(I2Cx , DISABLE);
	}

	if(Stop == WithStop)
	{
		//6. Send Stop Condition
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

	//7. re-enable The Acknowledging
	if(G_I2C_PinConfig[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx , ENABLE);
	}
	else
	{
		I2C_AcknowledgeConfig(I2Cx , DISABLE);
	}
}

/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveSendData
 * @brief 			- Slave send data to master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @param [in] 		- data : slave data to be sent to master
 * @retval 			- None
 * Note 			- Support interrupt mechanism only
 */
void MCAL_I2C_SlaveSendData(I2C_Typedef *I2Cx , uint8_t data)
{
	I2Cx->DR = data;
}

/* ================================================================
 * @Fn 				- MCAL_I2C_SlaveReceiveData
 * @brief 			- Slave Receive data from master using interrupt mechanism
 * @param [in] 		- I2Cx : where x can be (1..2 depending on device used) to select I2C peripheral
 * @retval 			- Received data
 * Note 			- Support interrupt mechanism only
 *
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2C_Typedef *I2Cx)
{
	return ((uint8_t)I2Cx->DR);
}

//========================================================================
//======================= 	  ISR Functions     ==========================
//========================================================================

void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummyRead = 0;
	I2C_Typedef* I2Cx =I2C1 ;
	//Interrupt Handler for both master and slave mode of a device
	uint32_t temp1, temp2, temp3;

	temp1 = I2Cx->CR2 & (I2C_CR2_ITEVTEN);
	temp2 = I2Cx->CR2 & (I2C_CR2_ITBUFEN);

	temp3 = I2Cx->SR1 & (I2C_SR1_STOPF);

	//Handle For Interrupt generated by STOPF event
	//Note : Stop detection flag is applicable only slave mode
	if(temp1 && temp3)
	{
		// STOP Flag is Set
		// Clear the STOPF by reading SR1 register followed by writing to CR1 register
		dummyRead = I2Cx->SR1;
		I2Cx->CR1 = 0x0000;
		Slave_States(I2Cx,I2C_EV_STOP);
	}

	/*---------------------------------------------------*/
	temp3 = I2Cx->SR1 & (I2C_SR1_ADDR);

	//Handle For Interrupt generated by ADDR event
	//Note :When master mode : Address is sent
	//		When slave mode  : Address is matched with own address
	if(temp1 && temp3)
	{
		// Interrupt is generated because of ADDR event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			//Clear the ADDR flag (Read SR1 , Read SR2)
			dummyRead = I2Cx->SR1;
			dummyRead = I2Cx->SR2;
			Slave_States(I2Cx,I2C_EV_ADDR_Matched);
		}
	}

	/*---------------------------------------------------*/
	temp3 = I2Cx->SR1 & (I2C_SR1_TXE);

	//Handle For Interrupt generated by TXE event
	if(temp1 && temp3)
	{
		// Interrupt is generated because of TXE event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			Slave_States(I2Cx,I2C_EV_DATA_REQ);
		}
	}
	/*---------------------------------------------------*/
	temp3 = I2Cx->SR1 & (I2C_SR1_RXNE);

	//Handle For Interrupt generated by RXNE event
	if(temp1 && temp3)
	{
		// Interrupt is generated because of RXNE event
		// check for device mode
		if(I2Cx->SR2 & (I2C_SR2_MSL))
		{
			//Master mode
		}
		else
		{
			//Slave mode
			Slave_States(I2Cx,I2C_EV_DATA_RCV);
		}
	}
}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}

