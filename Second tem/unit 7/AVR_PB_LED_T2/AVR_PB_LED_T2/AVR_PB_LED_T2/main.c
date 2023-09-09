/*
 * AVR_PB_LED_T2.c
 *
 * 
 * Author : aliab
 */ 
#define F_CPU 1000000ul

#include "platform_types.h"

#include "util/delay.h"

#define SETBIT(register,bit)     (register |=(1<<bit))

#define CLEARBIT(register,bit)   (register &=~(1<<bit))

#define TOGGLEBIT(register,bit)  (register ^=(1<<bit))

#define READBIT(register,bit)    ((register>>bit)&1)



//GPIO
#define GPIO_BASE 0x20
//PORTD
#define PORTD 	*(vuint8_t*) (GPIO_BASE + 0x12)
#define DDRD 	*(vuint8_t*) (GPIO_BASE + 0x11)

//PORTC
#define PORTC 	*(vuint8_t*) (GPIO_BASE + 0x15)
#define DDRC 	*(vuint8_t*) (GPIO_BASE + 0x14)
#define PINC 	*(vuint8_t*) (GPIO_BASE + 0x13)
void gpio_init()
{
	// portD is output
	DDRD = 0xFF;
	
	//Pin 4 input in portC
	DDRC &= ~(1<<4);

}


int main(void)
{
	gpio_init();
	uint8 count = 0, flag = 0;
	while(1)
	{
		if(((PINC & (1<<4)) >> 4) == 0) //pressed
		{
			while(((PINC & (1<<4)) >> 4) == 0);  //single press
			//toggle led
			PORTD ^= (1<<count);
			//if reached last led
			if(count == 7)
			{
				//to keep value 7 until toggle last led again
				if(flag == 1)
				{
					count--;
				}
				flag = 1;

			}
			//if reach first led
			else if(flag == 1 && count != 0)
			{
				count--;
			}
			else
			{
				//to keep value 0 until toggle first led again
				if(flag != 1)
				{
					count++;
				}
				flag = 0;
			}
		}
		
	}
}
