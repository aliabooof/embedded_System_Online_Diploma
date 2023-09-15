/*
 * AVR_USART_DRIVER.c
 *
 * Created: 9/12/2023 1:27:19 AM
 *  Author: aliab
 */ 
#include "AVR_USART_DRIVER.h"

void UART_init(){
	//---------------baud rate----------------------------
	//choose asynch mode (default)
	//CLEAR_BIT(UCSRC,UMSEL);
	
	//we are working with f_osc = 16MHz
	//normal mode (divider = 16)
	CLEAR_BIT(UCSRA,U2X);
	UBRRL = 103; //from data sheet
	
	//choose asynch mode (default)
	//CLEAR_BIT(UCSRC,UMSEL);
	
	
	//--------------------frame---------------------------
	#ifdef  Even_Parity
	CLEAR_BIT(UCSRC,UPM0);
	SET_BIT( UCSRC,UPM1);
	#endif
	#ifdef Odd_Parity
	SET_BIT(UCSRC,UPM0);
	SET_BIT(UCSRC,UPM1);
	#endif
	
	//stop bit
	#ifdef  one_stop_bit
	CLEAR_BIT(UCSRC,USBS);
	#endif
	#ifdef two_stop_bit
	SET_BIT(UCSRC,USBS);
	#endif
	
	//Data  size
	switch(frame_size)
	{
		case 5:
		CLEAR_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;
		
		case 6:
		SET_BIT(UCSRC,UCSZ0);
		CLEAR_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;

		case 7:
		CLEAR_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;

		case 8:
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		break;

		case 9:
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		SET_BIT(UCSRB,UCSZ2);
		break;

		default:
		SET_BIT(UCSRC,UCSZ0);
		SET_BIT(UCSRC,UCSZ1);
		CLEAR_BIT(UCSRB,UCSZ2);
		
	}
	
	//-----------------Enable----------------------
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
}

void UART_SendChar(char data){
	
	while(!(READ_BIT(UCSRA,UDRE)));
	UDR = data;
}
char UART_ReceiveChar(){
	while(!(READ_BIT(UCSRA,RXC)));
	return UDR;
}


void UART_SendString(char* str) {
	while (*str != '\0') {
		UART_SendChar(*str);
		str++;
	}
	//to indicate end
	UART_SendChar('\r');
}


void UART_ReceiveString(char *Buffer)
{
	
	*Buffer = UART_ReceiveChar();
	while (*Buffer != '\r') {
		Buffer++;
		*Buffer = UART_ReceiveChar();
	}
	*Buffer = '\0';
}