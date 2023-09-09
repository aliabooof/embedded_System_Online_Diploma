/*
 * AVR_amit_T3.c
 *
 * Created: 9/9/2023 8:59:28 AM
 * Author : aliab
 */ 

#define FCPU 100000UL
#include "platform_types.h"


//GPIO
#define GPIO_BASE 0x20
//PORTD
#define PORTD 	*(vuint8_t*) (GPIO_BASE + 0x12)
#define DDRD 	*(vuint8_t*) (GPIO_BASE + 0x11)
#define PIND 	*(vuint8_t*) (GPIO_BASE + 0x10)

void gpio_init()
{
	//Pin 0 input in portD
	DDRD &= ~(1<<0);
	//Pin 4 output in portD
	DDRD |= (1<<4);
}
void delay(vuint32_t x)
{
	vuint32_t i, j;
	for (i = 0; i < x; ++i)
	for (j = 0; j < 255; ++j);
}
int main(void)
{
	gpio_init();
	while(1)
	{
		if(((PIND & (1<<0)) >> 0) == 1) //pressed
		{
			//turn buzzer on
			PORTD |= (1<<4);
			delay(500);
			//turn buzzer off
			PORTD &= ~(1<<4);
			while((PIND & 1) == 1); //single press
		}
	}
}