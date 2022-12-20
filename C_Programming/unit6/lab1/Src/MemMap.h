/*
 * MemMap.h
 *
 *  Created on: Dec 20, 2022
 *      Author: aliab
 */

#ifndef MEMMAP_H_
#define MEMMAP_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// clock memory map
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
 //AFIO memory map
#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1 *(volatile uint32_t *)(AFIO_BASE + 0x08)


//GPIO memory map

//PORTA
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)


//EXTI
#define EXTI_BASE 0x40010400
#define EXTI_IMR *(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_PTSR *(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR *(volatile uint32_t *)(EXTI_BASE + 0x14)


#define NVIC_ISER0 *(volatile uint32_t *)(0xE000E100)

#endif /* MEMMAP_H_ */
