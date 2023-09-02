/*
 * STM32F103C6_GPIO.c
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */
#include "STM32F103x6_SPI.h"


//================================================================
//				Generic Variables
//================================================================

SPI_Config_t *G_SPI_PinConfig[2] = {NULL,NULL};
SPI_Config_t G_SPI_PinConfig1;
SPI_Config_t G_SPI_PinConfig2;
//================================================================
//				Generic Macros
//================================================================

#define SPI1_INDEX				0
#define SPI2_INDEX				1

#define SPI_SR_TXE				((uint8_t)(0x2)) // Transmit Register is empty
#define SPI_SR_RXNE				((uint8_t)(0x1)) // Receive Register is not empty

//================================================================
//				APIs Functions Definition
//================================================================

/**================================================================
 * @Fn			 -MCAL_SPI_Init
 * @brief 		 -Initialize SPI according to the specified parameters in SPI_Config
 * @param [in]   -SPIX :  were x can be (1,2 depending on device used)to select the SPI Peripheral
 * @param [in]   -PinConfig : pointer to SPI_Config Structure that Contains
 * 						      the configuration information for All SPI.
 * @retval		 -none
 * Note			 -Support for SPI Full Duplex Master/Slave & NSS HW/SW
 * 				 -In Case of Master you have to Configure pin and drive it.
 */
void MCAL_SPI_Init(SPI_TypeDef *SPIx , SPI_Config_t *PinConfig)
{
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;

	if(SPIx == SPI1)
	{
		G_SPI_PinConfig1 = *PinConfig;
		G_SPI_PinConfig[SPI1_INDEX] = &G_SPI_PinConfig1;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		G_SPI_PinConfig2 = *PinConfig;
		G_SPI_PinConfig[SPI2_INDEX] = &G_SPI_PinConfig2;
		RCC_SPI2_CLK_EN();
	}

	//SPI_CR1. Bit 6 SPE: SPI enable
	tmpreg_CR1 = (1<<6);

	// Master or Slave
	tmpreg_CR1 |= PinConfig->Device_Mode ;

	//SPI_Communication_Mode
	tmpreg_CR1 |= PinConfig->Communication_Mode ;

	//SPI_Frame_Format
	tmpreg_CR1 |= PinConfig->Frame_Format ;

	//SPI_Data_Size
	tmpreg_CR1 |= PinConfig->DataSize ;

	//SPI_Clock_Polarity
	tmpreg_CR1 |= PinConfig->CLKPolarity ;

	//SPI_Clock_Phase
	tmpreg_CR1 |= PinConfig->CLKPhase ;

	//=======================NSS=====================
	//SPI_NSS SPI Slave Select Management
	if(PinConfig->NSS == SPI_NSS_Hard_Master_SS_Output_Enable)
	{
		tmpreg_CR2 |= PinConfig->NSS ;
	}
	else if(PinConfig->NSS == SPI_NSS_Hard_Master_SS_Output_Disable)
	{
		tmpreg_CR2 &= PinConfig->NSS ;
	}
	else
	{
		tmpreg_CR1 |= PinConfig->NSS ;
	}
	//===============================================
	//SPI_BaudRatePrescaler
	tmpreg_CR1 |= PinConfig->SPI_BaudRatePrescaler ;

	if(PinConfig->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		//SPI_IRQ_Enable_Define
		tmpreg_CR2 |= PinConfig->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IQR35_SPI1_Enable;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IQR36_SPI2_Enable;
		}
	}

	SPIx->CR1 = tmpreg_CR1 ;
	SPIx->CR2 = tmpreg_CR2 ;
}

/**================================================================
 * @Fn			 -MCAL_SPI_DeInit
 * @brief 		 -Reset SPI Registers and NVIC corresponding to IRQ Mask
 * @param [in]   -none
 * @retval		 -none
 * Note			 -none
 */
void MCAL_SPI_DeInit(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IQR35_SPI1_Disable ;
		RCC_SPI1_RESET() ;
	}
	else if(SPIx == SPI2)
	{
		NVIC_IQR36_SPI2_Disable ;
		RCC_SPI2_RESET() ;
	}
}

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t* pTxBuffer , enum PollingMechanism PollingEn)
{
	if(PollingEn == PollingEnable)
		while(!( (SPIx->SR) & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer ;// Transmit Data
}
void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t* pRxBuffer , enum PollingMechanism PollingEn)
{
	if(PollingEn == PollingEnable)
		while(!( (SPIx->SR) & SPI_SR_RXNE));
	*pRxBuffer = SPIx->DR ;// Receive Data
}
void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx, uint16_t* pTxBuffer , enum PollingMechanism PollingEn)
{
	if(PollingEn == PollingEnable)
		while(!( (SPIx->SR) & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer ; // Transmit Data

	if(PollingEn == PollingEnable)
		while(!( (SPIx->SR) & SPI_SR_RXNE));
	*pTxBuffer = SPIx->DR ; // Receive Data
}

void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef *SPIx)
{
	if(SPIx == SPI1)
	{
		//PA4 >> SPI1_NSS
		//PA5 >> SPI1_SCK
		//PA6 >> SPI1_MISO
		//PA7 >> SPI1_MOSI

		//PA4 >> SPI1_NSS
		if(G_SPI_PinConfig[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER) // Master
		{
			switch (G_SPI_PinConfig[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_Output_Disable :
				MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_MODE_Input_FLO, 0);
				break;
			case SPI_NSS_Hard_Master_SS_Output_Enable :
				MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
				break;
			}
			//PA5 >> SPI1_SCK
			//Master Alternate function push-pull
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_5, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);

			//PA6 >> SPI1_MISO
			//Full duplex / master Input floating
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_6, GPIO_MODE_Input_FLO, 0);

			//todo to support half duplex and simplex

			//PA7 >> SPI1_MOSI
			//Full duplex / master Alternate function push-pull
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_7, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		}
		else // Slave
		{
			//PA4 >> SPI1_NSS
			if(G_SPI_PinConfig[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware slave Input floating
				MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_4, GPIO_MODE_Input_FLO, 0);
			}
			//PA5 >> SPI1_SCK
			//Slave Input floating
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_5, GPIO_MODE_Input_FLO, 0);

			//PA6 >> SPI1_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			//todo Full duplex / slave (multi-slave) Alternate function open drain
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_6, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);

			//todo to support half duplex and simplex

			//PA7 >> SPI1_MOSI
			//Full duplex / slave Input floating
			MCAL_GPIO_SET_Pin(GPIOA, GPIO_PIN_7, GPIO_MODE_Input_FLO, 0);
		}
	}
	else if(SPIx == SPI2)
	{
		//PB12 >> SPI2_NSS
		//PB13 >> SPI2_SCK
		//PB14 >> SPI2_MISO
		//PB15 >> SPI2_MOSI

		///PB12 >> SPI2_NSS
		if(G_SPI_PinConfig[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER) // Master
		{
			switch (G_SPI_PinConfig[SPI2_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_Output_Disable :
				MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_MODE_Input_FLO, 0);
				break;
			case SPI_NSS_Hard_Master_SS_Output_Enable :
				MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
				break;
			}
			//PB13 >> SPI2_SCK
			//Master Alternate function push-pull
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);

			//PB14 >> SPI2_MISO
			//Full duplex / master Input floating
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_MODE_Input_FLO, 0);

			//todo to support half duplex and simplex

			//PB15 >> SPI2_MOSI
			//Full duplex / master Alternate function push-pull
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_15, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);
		}
		else // Slave
		{
			//PB12 >> SPI2_NSS
			if(G_SPI_PinConfig[SPI2_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware slave Input floating
				MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_12, GPIO_MODE_Input_FLO, 0);
			}
			//PB13 >> SPI2_SCKK
			//Slave Input floating
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_13, GPIO_MODE_Input_FLO, 0);

			//PB14 >> SPI2_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			//todo Full duplex / slave (multi-slave) Alternate function open drain
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_14, GPIO_MODE_Output_AF_PP, GPIO_MAX_Speed_10M);

			//todo to support half duplex and simplex

			//PB15 >> SPI2_MOSI
			//Full duplex / slave Input floating
			MCAL_GPIO_SET_Pin(GPIOB, GPIO_PIN_15, GPIO_MODE_Input_FLO, 0);
		}

	}
}

//========================================================================
//======================= 	  ISR Functions     ==========================
//========================================================================


void SPI1_IRQHandler(void)
{
	IRQ_SRC_t irq_src;

	irq_src.TXE  = ( ((SPI1->SR)>>1) & 1 ) ;
	irq_src.RXNE = ( ((SPI1->SR)>>0) & 1 ) ;
	irq_src.ERRI = ( ((SPI1->SR)>>4) & 1 ) ;

	G_SPI_PinConfig[SPI1_INDEX]->P_IRQ_Handler(irq_src);
}

void SPI2_IRQHandler(void)
{
	IRQ_SRC_t irq_src;

	irq_src.TXE  = ( ((SPI1->SR)>>1) & 1 ) ;
	irq_src.RXNE = ( ((SPI1->SR)>>0) & 1 ) ;
	irq_src.ERRI = ( ((SPI1->SR)>>4) & 1 ) ;

	G_SPI_PinConfig[SPI2_INDEX]->P_IRQ_Handler(irq_src);
}














