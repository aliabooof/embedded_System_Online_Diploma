/*
 * TIM.C
 *
 *  Created on: Feb 7, 2023
 *      Author: aliab
 */


#include "TIM.h"

void delay(uint16_t ms){
	TIM1->TIMx_PSC = 0X8C9F;
	TIM1->TIMx_ARR = ms-1;
	TIM1->TIMx_CR1 |=(1<<0);
	while(!(TIM1->TIMx_SR&0x0001));
	TIM1->TIMx_SR|=(1<<0);
	TIM1->TIMx_CR1 &= ~(1<<0);

}
