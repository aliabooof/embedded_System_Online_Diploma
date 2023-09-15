/*
 * AVR_USART_DRIVER.c
 *
 * Created: 9/12/2023 1:24:23 AM
 * Author : aliab
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "Util.h"
#include "MCAL/AVR_USART_DRIVER.h"
#include "HAL/inc/LCD.h"


int main(void)
{
	
	
	char strr[200];
	LCD_INIT();
	LCD_CLEAR_SCREEN();
	_delay_ms(5000);
	LCD_WRITE_STRING("HELLO ");
	_delay_ms(5000);
	LCD_CLEAR_SCREEN();
	UART_init();
	LCD_WRITE_STRING("UART is initialized ");
	_delay_ms(5000);
	LCD_CLEAR_SCREEN();
	UART_SendString("ALI OSAMA ABOOUF");
	
	while (1)
	{
		UART_ReceiveString(strr);
		LCD_WRITE_STRING(strr);
	}
}
