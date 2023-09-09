/*
 * Toggle_Leds_Seq.c
 *
 * 
 * Author : aliab
 */ 

#define F_CPU 1000000ul

#include "util/delay.h"
#include "platform_types.h"

//GPIO
#define GPIO_BASE 0x20
//PORTD
#define PORTD 	*(vuint8_t*) (GPIO_BASE + 0x12)
#define DDRD 	*(vuint8_t*) (GPIO_BASE + 0x11)



#define SETBIT(register,bit)     (register |=(1<<bit))

#define CLEARBIT(register,bit)   (register &=~(1<<bit))

#define TOGGLEBIT(register,bit)  (register ^=(1<<bit))

#define READBIT(register,bit)    ((register>>bit)&1)

void GPIO_Init(){
	
	//make port D as output
	DDRD = 0xFF;
}

int main(void)
{
	int i;
	GPIO_Init();
    /* Replace with your application code */
    while (1) 
    {
		for(i = 0;i<8;i++){
			SETBIT(PORTD,i);
			_delay_ms(1000);
		}
		
		for(i = 7;i>=0;i--){
			CLEARBIT(PORTD,i);
			_delay_ms(1000);
		}
    }
}

