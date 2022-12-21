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
	DDRA = 0b11111111;
	int i;
    while (1) 
    {
		for(i=0;i<=7;i++){
			
			SET_BIT(PORTA,i);
			_delay_ms(500);	
		}
		for(i=7;i>=0;i--){
			CLEAR_BIT(PORTA,i);
			_delay_ms(500);	
		}
    }
}

