/*
 * AVR_MemMap.h
 *
 * Created: 9/10/2023 5:23:12 AM
 *  Author: aliab
 */ 


#ifndef AVR_MEMMAP_H_
#define AVR_MEMMAP_H_

#include "../../PlatformTypes.h"
/* ================================================================ */
/* ========== Base Addresses of FLASH and SRAM memories =========== */
/* ================================================================ */

#define FLASH_MEMORY		0x00
#define SRAM				0x60

/* ================================================================ */
/* ================ Bus Peripheral Base Addresses ================= */
/* ================================================================ */

#define GPIOA_Base			0x39
#define GPIOB_Base			0x36
#define GPIOC_Base			0x33
#define GPIOD_Base			0x30

/* ================================================================ */
/* ================= Peripheral Registers GPIO ==================== */
/* ================================================================ */

typedef struct{

	// PIN Register
	volatile union {
		vuint8_t PIN;
		struct{
			vuint8_t PIN0 :1;
			vuint8_t PIN1 :1;
			vuint8_t PIN2 :1;
			vuint8_t PIN3 :1;
			vuint8_t PIN4 :1;
			vuint8_t PIN5 :1;
			vuint8_t PIN6 :1;
			vuint8_t PIN7 :1;
		}bits;
	}PIN;
	//####################################

	// DDR Register
	volatile union {
		vuint8_t DDR;
		struct{
			vuint8_t DD0 :1;
			vuint8_t DD1 :1;
			vuint8_t DD2 :1;
			vuint8_t DD3 :1;
			vuint8_t DD4 :1;
			vuint8_t DD5 :1;
			vuint8_t DD6 :1;
			vuint8_t DD7 :1;
		}bits;
	}DDR;
	//###################################

	// PORT Register
	volatile union{
		vuint8_t PORT;
		struct{
			vuint8_t PORT0 :1;
			vuint8_t PORT1 :1;
			vuint8_t PORT2 :1;
			vuint8_t PORT3 :1;
			vuint8_t PORT4 :1;
			vuint8_t PORT5 :1;
			vuint8_t PORT6 :1;
			vuint8_t PORT7 :1;
		}bits;
	}PORT;
}GPIO_Typedef_t;

/* ================================================================ */
/* =================== Peripheral Instants  ======================= */
/* ================================================================ */

#define GPIOA 				((GPIO_Typedef_t *)(GPIOA_Base))
#define GPIOB  				((GPIO_Typedef_t *)(GPIOB_Base))
#define GPIOC 				((GPIO_Typedef_t *)(GPIOC_Base))
#define GPIOD 				((GPIO_Typedef_t *)(GPIOD_Base))



#endif /* AVR_MEMMAP_H_ */