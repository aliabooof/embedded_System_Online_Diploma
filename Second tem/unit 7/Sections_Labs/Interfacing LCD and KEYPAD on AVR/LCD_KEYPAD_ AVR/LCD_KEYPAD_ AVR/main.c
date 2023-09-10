/*
 * LCD_KEYPAD_ AVR.c
 *
 * Created: 9/10/2023 6:22:07 AM
 * Author : aliab
 */ 

#define F_CPU 1000000UL

#include "avr/io.h"
#include "util/delay.h"

#include "HAL/inc/KEYPAD.h"
#include "HAL/inc/LCD.h"

int main(void)
{
	LCD_INIT();
	KEYPAD_INIT();
	char pressed_key;
	
	while (1)
	{
		pressed_key = KEYPAD_GET_KEY();
		switch(pressed_key)
		{
			case '?':
			LCD_CLEAR_SCREEN();
			break;
			
			case 'A':
			break;
			
			default:
			LCD_WRITE_CHAR(pressed_key);
			break;
		}
	}
	
	return 0;
}