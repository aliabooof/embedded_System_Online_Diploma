/*
 * STM32F103x6.h
 *
 *  Created on: Jul 16, 2023
 *      Author: Amir
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
//Includes
//-----------------------------

#include "stdlib.h"
#include "stdint.h"

//-----------------------------
//Base Addresses For Memory
//-----------------------------

#define FLASH_Memory_BASE							0X08000000UL
#define System_Memory_BASE							0X1FFFF000UL
#define SRAM_Memory_BASE							0X20000000UL

#define Peripherals_BASE							0X40000000UL

#define Cortex_M3_Internal_Peripherals_BASE	    	0XE00000000UL
//NVIC register map
#define NVIC_BASE						0xE000E100UL
#define NVIC_ISER0					*(volatile uint32_t *)(NVIC_BASE + 0x000)
#define NVIC_ISER1					*(volatile uint32_t *)(NVIC_BASE + 0x004)
#define NVIC_ISER2					*(volatile uint32_t *)(NVIC_BASE + 0x008)
#define NVIC_ICER0					*(volatile uint32_t *)(NVIC_BASE + 0x080)
#define NVIC_ICER1					*(volatile uint32_t *)(NVIC_BASE + 0x084)
#define NVIC_ICER2					*(volatile uint32_t *)(NVIC_BASE + 0x088)


//===================================
//Base Addresses For Peripherals
//===================================

//-----------------------------------
//Base Addresses For APB2 Peripherals
//-----------------------------------

// GPIO
// A,B fully included in LQFP48 Package
#define GPIOA_BASE					0x40010800UL
#define GPIOB_BASE					0x40010C00UL
// C,D Partially included in LQFP48 Package
#define GPIOC_BASE					0x40011000UL
#define GPIOD_BASE					0x40011400UL
// E,F,G is not included in LQFP48 Package
#define GPIOE_BASE					0x40011800UL

//----------

// EXTI
#define EXTI_BASE					0x40010400UL
// AFIO
#define AFIO_BASE					0x40010000UL

// UART
#define USART1_BASE					0x40013800UL

//SPI
#define SPI1_BASE					0x40013000UL


//-----------------------------------
//Base Addresses For APB1 Peripherals
//-----------------------------------

// UART
#define USART2_BASE					0x40004400UL
#define USART3_BASE					0x40004800UL

//SPI
#define SPI2_BASE					0x40003800UL

//I2C
#define I2C1_BASE					0x40005400UL
#define I2C2_BASE					0x40005800UL
//-----------------------------------
//Base Addresses For AHB Peripherals
//-----------------------------------

// RCC
#define RCC_BASE					0x40021000UL

//===================================
//Peripheral registers
//===================================


//--------------------------
//Peripheral register: GPIO
//--------------------------
typedef struct
{
	// Offset Addresses of The GPIO Registers
	volatile uint32_t CRL; // 0X00
	volatile uint32_t CRH; // 0X04
	volatile uint32_t IDR; // 0X08
	volatile uint32_t ODR; // 0X0C
	volatile uint32_t BSRR;// 0X10
	volatile uint32_t BRR; // 0X14
	volatile uint32_t LCKR;// 0X18
}GPIO_TypeDef;


//--------------------------
//Peripheral register: EXTI
//--------------------------

typedef struct
{
	// Offset Addresses of The EXTI Registers
	volatile uint32_t IMR;  // 0X00
	volatile uint32_t EMR;  // 0X04
	volatile uint32_t RTSR; // 0X08
	volatile uint32_t FTSR; // 0X0C
	volatile uint32_t SWIER;// 0X10
	volatile uint32_t PR;   // 0X14

}EXTI_TypeDef;

//--------------------------
//Peripheral register: AFIO
//--------------------------
typedef struct
{
	// Offset Addresses of The AFIO Registers
	volatile uint32_t EVCR;    	// 0X00
	volatile uint32_t MAPR;    	// 0X04
	volatile uint32_t EXTICR[4];// [0X08 ,0X0C ,0X10 ,0X14]
	uint32_t 		  RESERVED0;// 0X18
	volatile uint32_t MAPR2;	// 0X1C
}AFIO_TypeDef;

//--------------------------
//Peripheral register: RCC
//--------------------------
typedef struct
{
	// Offset Addresses of The AFIO Registers
	volatile uint32_t CR;      // 0X00
	volatile uint32_t CFGR;    // 0X04
	volatile uint32_t CIR;	   // 0X08
	volatile uint32_t APB2RSTR;// 0X0C
	volatile uint32_t APB1RSTR;// 0X10
	volatile uint32_t AHBENR;  // 0X14
	volatile uint32_t APB2ENR; // 0X18
	volatile uint32_t APB1ENR; // 0X1C
	volatile uint32_t BDCR;    // 0X20
	volatile uint32_t CSR;	   // 0X24
}RCC_TypeDef;


//--------------------------
//Peripheral register: USART
//--------------------------
typedef struct
{
	// Offset Addresses of The USART Registers
	volatile uint32_t SR;      // 0X00
	volatile uint32_t DR;      // 0X04
	volatile uint32_t BRR;	   // 0X08
	volatile uint32_t CR1;	   // 0X0C
	volatile uint32_t CR2;     // 0X10
	volatile uint32_t CR3; 	   // 0X14
	volatile uint32_t GTPR;    // 0X18
}USART_TypeDef;

//--------------------------
//Peripheral register: SPI
//--------------------------
typedef struct
{
	// Offset Addresses of The SPI Registers
	volatile uint32_t CR1;      // 0X00
	volatile uint32_t CR2;      // 0X04
	volatile uint32_t SR;	    // 0X08
	volatile uint32_t DR;	    // 0X0C
	volatile uint32_t CRCPR;    // 0X10
	volatile uint32_t RXCRCR; 	// 0X14
	volatile uint32_t TXCRCR;   // 0X18
	volatile uint32_t I2SCFGR;  // 0X1C
	volatile uint32_t I2SPR;    // 0X20
}SPI_TypeDef;


//--------------------------
//Peripheral register: I2C
//--------------------------
typedef struct
{
	// Offset Addresses of The I2C Registers
	volatile uint32_t CR1;   // 0X00
	volatile uint32_t CR2;   // 0X04
	volatile uint32_t OAR1;  // 0X08
	volatile uint32_t OAR2;  // 0X0C
	volatile uint32_t DR;	 // 0X10
	volatile uint32_t SR1; 	 // 0X14
	volatile uint32_t SR2;   // 0X18
	volatile uint32_t CCR;   // 0X1C
	volatile uint32_t TRISE; // 0X20
}I2C_TypeDef;
//==============================
//Peripheral Instances
//==============================

#define GPIOA			((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB			((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC			((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD			((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE			((GPIO_TypeDef *)GPIOE_BASE)


#define RCC 			((RCC_TypeDef *)RCC_BASE)

#define EXTI 			((EXTI_TypeDef *)EXTI_BASE)

#define AFIO 			((AFIO_TypeDef *)AFIO_BASE)

#define USART1			((USART_TypeDef *)USART1_BASE)
#define USART2			((USART_TypeDef *)USART2_BASE)
#define USART3			((USART_TypeDef *)USART3_BASE)

#define SPI1			((SPI_TypeDef *)SPI1_BASE)
#define SPI2			((SPI_TypeDef *)SPI2_BASE)

#define I2C1			((I2C_TypeDef *)I2C1_BASE)
#define I2C2			((I2C_TypeDef *)I2C2_BASE)
//======================================================================

//--------------------------------
//RCC Enable Peripherals Macros
//---------------------------------

//Clock Enable GPIO
#define RCC_GPIOA_CLK_EN()			((RCC->APB2ENR) |= 1<<2)
#define RCC_GPIOB_CLK_EN()			((RCC->APB2ENR) |= 1<<3)
#define RCC_GPIOC_CLK_EN()			((RCC->APB2ENR) |= 1<<4)
#define RCC_GPIOD_CLK_EN()			((RCC->APB2ENR) |= 1<<5)
#define RCC_GPIOE_CLK_EN()			((RCC->APB2ENR) |= 1<<6)
//------------------------------

//Clock Enable AFIO
#define RCC_AFIO_CLK_EN()			((RCC->APB2ENR) |= 1<<0)
//------------------------------

//Clock Enable USART
#define RCC_USART1_CLK_EN()			((RCC->APB2ENR) |= 1<<14)
#define RCC_USART2_CLK_EN()			((RCC->APB1ENR) |= 1<<17)
#define RCC_USART3_CLK_EN()			((RCC->APB1ENR) |= 1<<18)
//------------------------------

//Clock Enable SPI
#define RCC_SPI1_CLK_EN()			((RCC->APB2ENR) |= 1<<12)
#define RCC_SPI2_CLK_EN()			((RCC->APB1ENR) |= 1<<14)
//------------------------------

//Clock Enable I2C
#define RCC_I2C1_CLK_EN()			((RCC->APB1ENR) |= 1<<21)
#define RCC_I2C2_CLK_EN()			((RCC->APB1ENR) |= 1<<22)

//--------------------------------
//RCC Reset Peripherals Macros
//---------------------------------

//USART
#define RCC_USART1_RESET()			((RCC->APB2RSTR) |= 1<<14)
#define RCC_USART2_RESET()			((RCC->APB1RSTR) |= 1<<17)
#define RCC_USART3_RESET()			((RCC->APB1RSTR) |= 1<<18)
//------------------------------

//SPI
#define RCC_SPI1_RESET()			((RCC->APB2RSTR) |= 1<<12)
#define RCC_SPI2_RESET()			((RCC->APB1RSTR) |= 1<<14)
//------------------------------

//I2C
#define RCC_I2C1_RESET()			((RCC->APB1RSTR) |= 1<<21)
#define RCC_I2C2_RESET()			((RCC->APB1RSTR) |= 1<<22)

//-----------------------------------------------------------
//=====================IRQ NUMBERS in NVIC===================
//-----------------------------------------------------------

//EXTI
#define EXTI0_IRQ			6
#define EXTI1_IRQ			7
#define EXTI2_IRQ			8
#define EXTI3_IRQ			9
#define EXTI4_IRQ			10
#define EXTI5_IRQ			23
#define EXTI6_IRQ			23
#define EXTI7_IRQ			23
#define EXTI8_IRQ			23
#define EXTI9_IRQ			23
#define EXTI10_IRQ 			40
#define EXTI11_IRQ 			40
#define EXTI12_IRQ 			40
#define EXTI13_IRQ 			40
#define EXTI14_IRQ 			40
#define EXTI15_IRQ 			40
//---------------------------------

//USART
#define USART1_IRQ 			37
#define USART2_IRQ 			38
#define USART3_IRQ 			39
//------------------------------

//SPI
#define SPI1_IRQ 			35
#define SPI2_IRQ 			36
//------------------------------

//I2C
#define I2C1_EV_IRQ 		31
#define I2C1_ER_IRQ 		32
#define I2C2_EV_IRQ 		33
#define I2C2_ER_IRQ 		34

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//NVIC Enable/Disable Macros
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

// EXTI
#define NVIC_IQR6_EXTI0_Enable				(NVIC_ISER0 |= (1<<6))
#define NVIC_IQR7_EXTI1_Enable				(NVIC_ISER0 |= (1<<7))
#define NVIC_IQR8_EXTI2_Enable				(NVIC_ISER0 |= (1<<8))
#define NVIC_IQR9_EXTI3_Enable				(NVIC_ISER0 |= (1<<9))
#define NVIC_IQR10_EXTI4_Enable				(NVIC_ISER0 |= (1<<10))
#define NVIC_IQR23_EXTI5_9_Enable			(NVIC_ISER0 |= (1<<23))
#define NVIC_IQR40_EXTI10_15_Enable			(NVIC_ISER1 |= (1<<8)) //40 - 32 = 8

#define NVIC_IQR6_EXTI0_Disable				(NVIC_ICER0 |= (1<<6))
#define NVIC_IQR7_EXTI1_Disable				(NVIC_ICER0 |= (1<<7))
#define NVIC_IQR8_EXTI2_Disable				(NVIC_ICER0 |= (1<<8))
#define NVIC_IQR9_EXTI3_Disable				(NVIC_ICER0 |= (1<<9))
#define NVIC_IQR10_EXTI4_Disable			(NVIC_ICER0 |= (1<<10))
#define NVIC_IQR23_EXTI5_9_Disable			(NVIC_ICER0 |= (1<<23))
#define NVIC_IQR40_EXTI10_15_Disable		(NVIC_ICER1 |= (1<<8)) //40 - 32 = 8

// USART
#define NVIC_IQR37_USART1_Enable			(NVIC_ISER1 |= (1<<(USART1_IRQ - 32)))
#define NVIC_IQR38_USART2_Enable			(NVIC_ISER1 |= (1<<(USART2_IRQ - 32)))
#define NVIC_IQR39_USART3_Enable			(NVIC_ISER1 |= (1<<(USART3_IRQ - 32)))

#define NVIC_IQR37_USART1_Disable			(NVIC_ICER1 |= (1<<(USART1_IRQ - 32)))
#define NVIC_IQR38_USART2_Disable			(NVIC_ICER1 |= (1<<(USART2_IRQ - 32)))
#define NVIC_IQR39_USART3_Disable			(NVIC_ICER1 |= (1<<(USART3_IRQ - 32)))

// SPI
#define NVIC_IQR35_SPI1_Enable				(NVIC_ISER1 |= (1<<(SPI1_IRQ - 32)))
#define NVIC_IQR36_SPI2_Enable				(NVIC_ISER1 |= (1<<(SPI2_IRQ - 32)))

#define NVIC_IQR35_SPI1_Disable				(NVIC_ICER1 |= (1<<(SPI1_IRQ - 32)))
#define NVIC_IQR36_SPI2_Disable				(NVIC_ICER1 |= (1<<(SPI2_IRQ - 32)))

//I2C
#define NVIC_IQR31_I2C1_EV_Enable			(NVIC_ISER0 |= (1<<I2C1_EV_IRQ))
#define NVIC_IQR32_I2C1_ER_Enable			(NVIC_ISER1 |= (1<<(I2C1_ER_IRQ - 32)))
#define NVIC_IQR33_I2C2_EV_Enable			(NVIC_ISER1 |= (1<<(I2C2_EV_IRQ - 32)))
#define NVIC_IQR34_I2C2_ER_Enable			(NVIC_ISER1 |= (1<<(I2C2_ER_IRQ - 32)))

#define NVIC_IQR31_I2C1_EV_Disable			(NVIC_ICER0 |= (1<<I2C1_EV_IRQ)) // Bit >> 31
#define NVIC_IQR32_I2C1_ER_Disable			(NVIC_ICER1 |= (1<<(I2C1_ER_IRQ - 32))) // 32 - 32 = 0
#define NVIC_IQR33_I2C2_EV_Disable			(NVIC_ICER1 |= (1<<(I2C2_EV_IRQ - 32))) // 33 - 32 = 1
#define NVIC_IQR34_I2C2_ER_Disable			(NVIC_ICER1 |= (1<<(I2C2_ER_IRQ - 32))) // 34 - 32 = 2

/********************************************************/
/********************************************************/
/********************************************************/
/*******************  Bit definition  ********************/
/********************************************************/
/********************************************************/



/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE_Pos                      (0U)
#define I2C_CR1_PE_Msk                      (0x1UL << I2C_CR1_PE_Pos)           /*!< 0x00000001 */
#define I2C_CR1_PE                          I2C_CR1_PE_Msk                     /*!< Peripheral Enable */
#define I2C_CR1_SMBUS_Pos                   (1U)
#define I2C_CR1_SMBUS_Msk                   (0x1UL << I2C_CR1_SMBUS_Pos)        /*!< 0x00000002 */
#define I2C_CR1_SMBUS                       I2C_CR1_SMBUS_Msk                  /*!< SMBus Mode */
#define I2C_CR1_SMBTYPE_Pos                 (3U)
#define I2C_CR1_SMBTYPE_Msk                 (0x1UL << I2C_CR1_SMBTYPE_Pos)      /*!< 0x00000008 */
#define I2C_CR1_SMBTYPE                     I2C_CR1_SMBTYPE_Msk                /*!< SMBus Type */
#define I2C_CR1_ENARP_Pos                   (4U)
#define I2C_CR1_ENARP_Msk                   (0x1UL << I2C_CR1_ENARP_Pos)        /*!< 0x00000010 */
#define I2C_CR1_ENARP                       I2C_CR1_ENARP_Msk                  /*!< ARP Enable */
#define I2C_CR1_ENPEC_Pos                   (5U)
#define I2C_CR1_ENPEC_Msk                   (0x1UL << I2C_CR1_ENPEC_Pos)        /*!< 0x00000020 */
#define I2C_CR1_ENPEC                       I2C_CR1_ENPEC_Msk                  /*!< PEC Enable */
#define I2C_CR1_ENGC_Pos                    (6U)
#define I2C_CR1_ENGC_Msk                    (0x1UL << I2C_CR1_ENGC_Pos)         /*!< 0x00000040 */
#define I2C_CR1_ENGC                        I2C_CR1_ENGC_Msk                   /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH_Pos               (7U)
#define I2C_CR1_NOSTRETCH_Msk               (0x1UL << I2C_CR1_NOSTRETCH_Pos)    /*!< 0x00000080 */
#define I2C_CR1_NOSTRETCH                   I2C_CR1_NOSTRETCH_Msk              /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START_Pos                   (8U)
#define I2C_CR1_START_Msk                   (0x1UL << I2C_CR1_START_Pos)        /*!< 0x00000100 */
#define I2C_CR1_START                       I2C_CR1_START_Msk                  /*!< Start Generation */
#define I2C_CR1_STOP_Pos                    (9U)
#define I2C_CR1_STOP_Msk                    (0x1UL << I2C_CR1_STOP_Pos)         /*!< 0x00000200 */
#define I2C_CR1_STOP                        I2C_CR1_STOP_Msk                   /*!< Stop Generation */
#define I2C_CR1_ACK_Pos                     (10U)
#define I2C_CR1_ACK_Msk                     (0x1UL << I2C_CR1_ACK_Pos)          /*!< 0x00000400 */
#define I2C_CR1_ACK                         I2C_CR1_ACK_Msk                    /*!< Acknowledge Enable */
#define I2C_CR1_POS_Pos                     (11U)
#define I2C_CR1_POS_Msk                     (0x1UL << I2C_CR1_POS_Pos)          /*!< 0x00000800 */
#define I2C_CR1_POS                         I2C_CR1_POS_Msk                    /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_PEC_Pos                     (12U)
#define I2C_CR1_PEC_Msk                     (0x1UL << I2C_CR1_PEC_Pos)          /*!< 0x00001000 */
#define I2C_CR1_PEC                         I2C_CR1_PEC_Msk                    /*!< Packet Error Checking */
#define I2C_CR1_ALERT_Pos                   (13U)
#define I2C_CR1_ALERT_Msk                   (0x1UL << I2C_CR1_ALERT_Pos)        /*!< 0x00002000 */
#define I2C_CR1_ALERT                       I2C_CR1_ALERT_Msk                  /*!< SMBus Alert */
#define I2C_CR1_SWRST_Pos                   (15U)
#define I2C_CR1_SWRST_Msk                   (0x1UL << I2C_CR1_SWRST_Pos)        /*!< 0x00008000 */
#define I2C_CR1_SWRST                       I2C_CR1_SWRST_Msk                  /*!< Software Reset */
/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ_Pos                    (0U)
#define I2C_CR2_FREQ_Msk                    (0x3FUL << I2C_CR2_FREQ_Pos)        /*!< 0x0000003F */
#define I2C_CR2_FREQ                        I2C_CR2_FREQ_Msk                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_ITERREN_Pos                 (8U)
#define I2C_CR2_ITERREN_Msk                 (0x1UL << I2C_CR2_ITERREN_Pos)      /*!< 0x00000100 */
#define I2C_CR2_ITERREN                     I2C_CR2_ITERREN_Msk                /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN_Pos                 (9U)
#define I2C_CR2_ITEVTEN_Msk                 (0x1UL << I2C_CR2_ITEVTEN_Pos)      /*!< 0x00000200 */
#define I2C_CR2_ITEVTEN                     I2C_CR2_ITEVTEN_Msk                /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN_Pos                 (10U)
#define I2C_CR2_ITBUFEN_Msk                 (0x1UL << I2C_CR2_ITBUFEN_Pos)      /*!< 0x00000400 */
#define I2C_CR2_ITBUFEN                     I2C_CR2_ITBUFEN_Msk                /*!< Buffer Interrupt Enable */
#define I2C_CR2_DMAEN_Pos                   (11U)
#define I2C_CR2_DMAEN_Msk                   (0x1UL << I2C_CR2_DMAEN_Pos)        /*!< 0x00000800 */
#define I2C_CR2_DMAEN                       I2C_CR2_DMAEN_Msk                  /*!< DMA Requests Enable */
#define I2C_CR2_LAST_Pos                    (12U)
#define I2C_CR2_LAST_Msk                    (0x1UL << I2C_CR2_LAST_Pos)         /*!< 0x00001000 */
#define I2C_CR2_LAST                        I2C_CR2_LAST_Msk                   /*!< DMA Last Transfer */
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL_Pos                 (0U)
#define I2C_OAR2_ENDUAL_Msk                 (0x1UL << I2C_OAR2_ENDUAL_Pos)      /*!< 0x00000001 */
#define I2C_OAR2_ENDUAL                     I2C_OAR2_ENDUAL_Msk                /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2_Pos                   (1U)
/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB_Pos                      (0U)
#define I2C_SR1_SB_Msk                      (0x1UL << I2C_SR1_SB_Pos)           /*!< 0x00000001 */
#define I2C_SR1_SB                          I2C_SR1_SB_Msk                     /*!< Start Bit (Master mode) */
#define I2C_SR1_ADDR_Pos                    (1U)
#define I2C_SR1_ADDR_Msk                    (0x1UL << I2C_SR1_ADDR_Pos)         /*!< 0x00000002 */
#define I2C_SR1_ADDR                        I2C_SR1_ADDR_Msk                   /*!< Address sent (master mode)/matched (slave mode) */
#define I2C_SR1_BTF_Pos                     (2U)
#define I2C_SR1_BTF_Msk                     (0x1UL << I2C_SR1_BTF_Pos)          /*!< 0x00000004 */
#define I2C_SR1_BTF                         I2C_SR1_BTF_Msk                    /*!< Byte Transfer Finished */
#define I2C_SR1_ADD10_Pos                   (3U)
#define I2C_SR1_ADD10_Msk                   (0x1UL << I2C_SR1_ADD10_Pos)        /*!< 0x00000008 */
#define I2C_SR1_ADD10                       I2C_SR1_ADD10_Msk                  /*!< 10-bit header sent (Master mode) */
#define I2C_SR1_STOPF_Pos                   (4U)
#define I2C_SR1_STOPF_Msk                   (0x1UL << I2C_SR1_STOPF_Pos)        /*!< 0x00000010 */
#define I2C_SR1_STOPF                       I2C_SR1_STOPF_Msk                  /*!< Stop detection (Slave mode) */
#define I2C_SR1_RXNE_Pos                    (6U)
#define I2C_SR1_RXNE_Msk                    (0x1UL << I2C_SR1_RXNE_Pos)         /*!< 0x00000040 */
#define I2C_SR1_RXNE                        I2C_SR1_RXNE_Msk                   /*!< Data Register not Empty (receivers) */
#define I2C_SR1_TXE_Pos                     (7U)
#define I2C_SR1_TXE_Msk                     (0x1UL << I2C_SR1_TXE_Pos)          /*!< 0x00000080 */
#define I2C_SR1_TXE                         I2C_SR1_TXE_Msk                    /*!< Data Register Empty (transmitters) */
#define I2C_SR1_BERR_Pos                    (8U)
#define I2C_SR1_BERR_Msk                    (0x1UL << I2C_SR1_BERR_Pos)         /*!< 0x00000100 */
#define I2C_SR1_BERR                        I2C_SR1_BERR_Msk                   /*!< Bus Error */
#define I2C_SR1_ARLO_Pos                    (9U)
#define I2C_SR1_ARLO_Msk                    (0x1UL << I2C_SR1_ARLO_Pos)         /*!< 0x00000200 */
#define I2C_SR1_ARLO                        I2C_SR1_ARLO_Msk                   /*!< Arbitration Lost (master mode) */
#define I2C_SR1_AF_Pos                      (10U)
#define I2C_SR1_AF_Msk                      (0x1UL << I2C_SR1_AF_Pos)           /*!< 0x00000400 */
#define I2C_SR1_AF                          I2C_SR1_AF_Msk                     /*!< Acknowledge Failure */
#define I2C_SR1_OVR_Pos                     (11U)
#define I2C_SR1_OVR_Msk                     (0x1UL << I2C_SR1_OVR_Pos)          /*!< 0x00000800 */
#define I2C_SR1_OVR                         I2C_SR1_OVR_Msk                    /*!< Overrun/Underrun */
#define I2C_SR1_PECERR_Pos                  (12U)
#define I2C_SR1_PECERR_Msk                  (0x1UL << I2C_SR1_PECERR_Pos)       /*!< 0x00001000 */
#define I2C_SR1_PECERR                      I2C_SR1_PECERR_Msk                 /*!< PEC Error in reception */
#define I2C_SR1_TIMEOUT_Pos                 (14U)
#define I2C_SR1_TIMEOUT_Msk                 (0x1UL << I2C_SR1_TIMEOUT_Pos)      /*!< 0x00004000 */
#define I2C_SR1_TIMEOUT                     I2C_SR1_TIMEOUT_Msk                /*!< Timeout or Tlow Error */
#define I2C_SR1_SMBALERT_Pos                (15U)
#define I2C_SR1_SMBALERT_Msk                (0x1UL << I2C_SR1_SMBALERT_Pos)     /*!< 0x00008000 */
#define I2C_SR1_SMBALERT                    I2C_SR1_SMBALERT_Msk               /*!< SMBus Alert */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL_Pos                     (0U)
#define I2C_SR2_MSL_Msk                     (0x1UL << I2C_SR2_MSL_Pos)          /*!< 0x00000001 */
#define I2C_SR2_MSL                         I2C_SR2_MSL_Msk                    /*!< Master/Slave */
#define I2C_SR2_BUSY_Pos                    (1U)
#define I2C_SR2_BUSY_Msk                    (0x1UL << I2C_SR2_BUSY_Pos)         /*!< 0x00000002 */
#define I2C_SR2_BUSY                        I2C_SR2_BUSY_Msk                   /*!< Bus Busy */
#define I2C_SR2_TRA_Pos                     (2U)
#define I2C_SR2_TRA_Msk                     (0x1UL << I2C_SR2_TRA_Pos)          /*!< 0x00000004 */
#define I2C_SR2_TRA                         I2C_SR2_TRA_Msk                    /*!< Transmitter/Receiver */
#define I2C_SR2_GENCALL_Pos                 (4U)
#define I2C_SR2_GENCALL_Msk                 (0x1UL << I2C_SR2_GENCALL_Pos)      /*!< 0x00000010 */
#define I2C_SR2_GENCALL                     I2C_SR2_GENCALL_Msk                /*!< General Call Address (Slave mode) */
#define I2C_SR2_SMBDEFAULT_Pos              (5U)
#define I2C_SR2_SMBDEFAULT_Msk              (0x1UL << I2C_SR2_SMBDEFAULT_Pos)   /*!< 0x00000020 */
#define I2C_SR2_SMBDEFAULT                  I2C_SR2_SMBDEFAULT_Msk             /*!< SMBus Device Default Address (Slave mode) */
#define I2C_SR2_SMBHOST_Pos                 (6U)
#define I2C_SR2_SMBHOST_Msk                 (0x1UL << I2C_SR2_SMBHOST_Pos)      /*!< 0x00000040 */
#define I2C_SR2_SMBHOST                     I2C_SR2_SMBHOST_Msk                /*!< SMBus Host Header (Slave mode) */
#define I2C_SR2_DUALF_Pos                   (7U)
#define I2C_SR2_DUALF_Msk                   (0x1UL << I2C_SR2_DUALF_Pos)        /*!< 0x00000080 */
#define I2C_SR2_DUALF                       I2C_SR2_DUALF_Msk                  /*!< Dual Flag (Slave mode) */
#define I2C_SR2_PEC_Pos                     (8U)
#define I2C_SR2_PEC_Msk                     (0xFFUL << I2C_SR2_PEC_Pos)         /*!< 0x0000FF00 */
#define I2C_SR2_PEC                         I2C_SR2_PEC_Msk                    /*!< Packet Error Checking Register */
#endif /* INC_STM32F103X6_H_ */







