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
	DDRD = 0b11111110;
    /* Replace with your application code */
	CLEAR_BIT(DDRD,0);
	SET_BIT(PORTD,0);
	
	
    while (1) 
    {
			if(READ_BIT(PIND,0) == 1)
			{
				SET_BIT(PORTD,4);
				_delay_ms(50);
				CLEAR_BIT(PORTD,4);
			}
	}
}

