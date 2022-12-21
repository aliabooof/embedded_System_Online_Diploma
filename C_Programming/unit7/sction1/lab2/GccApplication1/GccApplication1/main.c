/*
 * GccApplication1.c
 *
 * Created: 12/20/2022 6:01:50 PM
 * Author : aliab
 */ 


#include "MemMap.h"
#define F_CPU 8000000ul
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	CLEAR_BIT(DDRC,0);
	SET_BIT(PORTC,0);
	DDRA = 0b11111111;
	int i = 0 ;
	
    while (1) 
    {
		if(i <= 7)
		{
			if(READ_BIT(PINC,0) == 0)
			{
				SET_BIT(PORTA,i);
				i++;	
				_delay_ms(500);
			}
		}
    }
}

