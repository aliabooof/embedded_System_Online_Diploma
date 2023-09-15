/*
 * AVR_USART_DRIVER.h
 *
 * Created: 9/12/2023 1:27:08 AM
 *  Author: aliab
 */ 


#ifndef AVR_USART_DRIVER_H_
#define AVR_USART_DRIVER_H_

#include "../Util.h"
#include <stdint.h>
#include <avr/io.h>


//#define Even_Parity
#define two_stop_bit
#define frame_size 8

void UART_init();
void UART_SendChar(char data);
char UART_ReceiveChar();
void UART_SendString(char* str);
void UART_ReceiveString(char *Buffer);




#endif /* AVR_USART_DRIVER_H_ */