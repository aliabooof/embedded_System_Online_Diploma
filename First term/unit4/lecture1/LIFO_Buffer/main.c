/*
 * main.c
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */

#include "stdio.h"
#include "lifo_buffer.h"
#define lifo_buf_legnth 5
int main(){
	lifo_buf_t uart_lifo;
	unsigned char buffer1[lifo_buf_legnth];
	unsigned char i,temp;

	buf_init(&uart_lifo,buffer1,lifo_buf_legnth);

	for(i=0;i<lifo_buf_legnth;i++){
		buf_push(&uart_lifo,i);
	}
	for(i=0;i<lifo_buf_legnth;i++){
			buf_pop(&uart_lifo,&temp);
			printf("%d",temp);
		}


}
