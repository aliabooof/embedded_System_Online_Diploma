/*
 * STM32F103C6_SPI_Driver.C
 *
 *  Created on: Sep 2, 2023
 *      Author: aliab
 */


/*
 * =======================================================================================
 * 									Includes
 * =======================================================================================
 */
#include "../inc/STM32F103_SPI_DRIVER.h"



/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
#define SPI1_INDEX			0
#define SPI2_INDEX			1
#define SPI_SR_TXE  		((uint8_t)0x02)  //Transmit buffer empty
#define SPI_SR_RXNE         ((uint8_t)0x01)  // Receive buffer Not Empty


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */

SPI_config_t global_SPI_config[2];

/*
 *
 * =======================================================================================
 * 							APIs Implementations
 * =======================================================================================
 */
void MCAL_SPI_init(SPI_Typedef * SPIx,SPI_config_t * config){
	//temp variables for precaution
	uint16_t tempCR1 = 0, tempCR2 = 0;

	if(SPIx == SPI1){
		global_SPI_config[SPI1_INDEX] = *config;
		RCC_SPI1_CLK_EN();
	}else if(SPIx == SPI2){
		global_SPI_config[SPI2_INDEX] = *config;
		RCC_SPI2_CLK_EN();
	}

	//Enable SP1 CR1. bit 6 SPE: SPI enable
	tempCR1  = (uint16_t)(1<<6);

	//Master or Slave
	tempCR1 |= config->device_mode;

	//Communication mode
	tempCR1 |= config->communication_mode;

	//Frame format
	tempCR1 |= config->frame_format;

	//Data size
	tempCR1 |= config->data_size;

	//clock polarity
	tempCR1 |= config->CLK_polarity;

	//clock phase
	tempCR1 |= config->CLK_phase;

	//NSS
	if(config->NSS == SPI_NSS_HW_MASTER_SS_OUTPUT_ENABLE){
		tempCR2 |= config->NSS;
	}else if(config->NSS == SPI_NSS_HW_MASTER_SS_OUTPUT_DISABLE){
		tempCR2 &= config->NSS;
	}else{
		tempCR1 |= config->NSS;
	}

	//baud rate
	tempCR1 |= config->baud_rate_prescaler;

	//interrupt
	if(config->IRQ_enable != SPI_IRQ_ENABLE_NONE){
		tempCR2 |= config->IRQ_enable;

		if(SPIx == SPI1){
			NVIC_IRQ35_SPI1_ENABLE();
		}else if (SPIx == SPI2) {
			NVIC_IRQ36_SPI2_ENABLE();
		}


	}


	SPIx->SPI_CR1 = tempCR1;
	SPIx->SPI_CR2 = tempCR2;

}


void MCAL_SPI_deinit(SPI_Typedef * SPIx){

	if(SPIx == SPI1){
		NVIC_IRQ35_SPI1_DISABLE();
		RCC_SPI1_RESET();
	}else if (SPIx == SPI2) {
		NVIC_IRQ36_SPI2_DISABLE();
		RCC_SPI2_RESET();
	}
}

void MCAL_SPI_set_pins(SPI_Typedef * SPIx){

	GPIO_PIN_Config_t pinConfig;


	if (SPIx == SPI1) {
		//PA 4 : NSS
		//PA 5 : SCK
		//PA 6 : MISO
		//PA 7 : MOSI

		if(global_SPI_config[SPI1_INDEX].device_mode == SPI_DEVICE_MODE_MASTER){

			//PA 4 : NSS
			switch(global_SPI_config[SPI1_INDEX].NSS){
			case SPI_NSS_HW_MASTER_SS_OUTPUT_DISABLE:
				//Hardware Master - Input Floating
				pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
				pinConfig.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_Init(GPIOA, &pinConfig);
				break;

			case SPI_NSS_HW_MASTER_SS_OUTPUT_ENABLE:
				//Hardware Master - NSS output enabled Alternative function push-pull
				pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
				pinConfig.GPIO_PinNumber = GPIO_PIN_4;
				pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &pinConfig);
				break;
			}

			//===============================================================================

			/*PA 5 : SCK
			 *Master Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_5;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//===============================================================================

			/*PA 6 : MISO 	(supports only full duplex)
			 *Master Input Floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_6;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//===============================================================================

			/*PA 7 : MOSI
			 *Master Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_7;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);



		}else{ //slave
			//PA 4 : NSS
			if (global_SPI_config[SPI1_INDEX].device_mode == SPI_NSS_HW_SLAVE) {
				//Hardware Slave - Input Floating
				pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
				pinConfig.GPIO_PinNumber = GPIO_PIN_4;
				MCAL_GPIO_Init(GPIOA, &pinConfig);
			}

			//===============================================================================

			/*PA 5 : SCK
			 *Slave Input floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_5;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//===============================================================================

			/*PA 6 : MISO
			 *Slave (point-to-point) Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_6;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

			//===============================================================================

			/*PA 7 : MOSI
			 *Slave Input floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_7;
			MCAL_GPIO_Init(GPIOA, &pinConfig);

		}



	} else if(SPIx == SPI2) {
		//PB 12 : NSS
		//PB 13 : SCK
		//PB 14 : MIOS
		//PB 15 : MOSI

		if(global_SPI_config[SPI2_INDEX].device_mode == SPI_DEVICE_MODE_MASTER){

			//PB 12 : NSS
			switch(global_SPI_config[SPI1_INDEX].NSS){
			case SPI_NSS_HW_MASTER_SS_OUTPUT_DISABLE:
				//Hardware Master - Input Floating
				pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
				pinConfig.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_Init(GPIOB, &pinConfig);
				break;

			case SPI_NSS_HW_MASTER_SS_OUTPUT_ENABLE:
				//Hardware Master - NSS output enabled Alternative function push-pull
				pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
				pinConfig.GPIO_PinNumber = GPIO_PIN_12;
				pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &pinConfig);
				break;
			}

			//===============================================================================

			/*PB 13 : SCK
			 *Master Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_13;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

			//===============================================================================

			/*PB 14 : MISO 	(supports only full duplex)
			 *Master Input Floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_14;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

			//===============================================================================

			/*PB 15 : MOSI
			 *Master Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_15;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);



		}else{ //slave
			//PB 12 : NSS
			if (global_SPI_config[SPI2_INDEX].device_mode == SPI_NSS_HW_SLAVE) {
				//Hardware Slave - Input Floating
				pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
				pinConfig.GPIO_PinNumber = GPIO_PIN_12;
				MCAL_GPIO_Init(GPIOB, &pinConfig);
			}

			//===============================================================================

			/*PB 13 : SCK
			 *Slave Input floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_13;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

			//===============================================================================

			/*PB 14 : MISO
			 *Slave (point-to-point) Alternative function push-pull*/
			pinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT_AF_PP;
			pinConfig.GPIO_PinNumber = GPIO_PIN_14;
			pinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

			//===============================================================================

			/*PB 15 : MOSI
			 *Slave Input floating*/
			pinConfig.GPIO_PinMode = GPIO_MODE_INPUT_FLO;
			pinConfig.GPIO_PinNumber = GPIO_PIN_15;
			MCAL_GPIO_Init(GPIOB, &pinConfig);

		}
	}
}

void MCAL_SPI_send_date(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn){

	//Busy wait
	if (pollEn == pollingEnable) {
		while(!(SPIx->SPI_SR & SPI_SR_TXE));
	}

	//Send date
	SPIx->SPI_DR = *data;
}

void MCAL_SPI_receive_date(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn){

	//Busy wait
	if (pollEn == pollingEnable) {
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));
	}

	//Receive data
	*data = SPIx->SPI_DR;
}

void MCAL_SPI_TX_RX(SPI_Typedef * SPIx, uint16_t* data, pollingMechnism pollEn){
	MCAL_SPI_send_date(SPIx, data, pollEn);
	MCAL_SPI_receive_date(SPIx, data, pollEn);
}



void SPI1_IRQHandler(void){
	IRQ_SPI_src_t irq_src ;

	irq_src.TXE = ((SPI1->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI1->SPI_SR & (1<<0)) >> 0);
	irq_src.ERRI = ((SPI1->SPI_SR & (1<<4)) >> 4);

	global_SPI_config[SPI1_INDEX].p_IRQ_callback(irq_src);
}

void SPI2_IRQHandler (void){
	IRQ_SPI_src_t irq_src ;

	irq_src.TXE = ((SPI2->SPI_SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI2->SPI_SR & (1<<0)) >> 0);
	irq_src.ERRI = ((SPI2->SPI_SR & (1<<4)) >> 4);

	global_SPI_config[SPI2_INDEX].p_IRQ_callback(irq_src);
}
