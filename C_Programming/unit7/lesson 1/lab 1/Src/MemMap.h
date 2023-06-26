/*
 * MemMap.h
 *
 *  Created on: Dec 19, 2022
 *      Author: aliab
 */

#ifndef MEMMAP_H_
#define MEMMAP_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

// clock memory map
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)

//GPIO memory map

//PORTA
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

//PORTB

#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR *(volatile uint32_t *)(GPIOB_BASE + 0x0C)

#endif /* MEMMAP_H_ */
