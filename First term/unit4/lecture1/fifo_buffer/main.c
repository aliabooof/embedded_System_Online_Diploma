/*
 * main.c
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */


#include "fifo_buffer.h"

int main(){

	FIFO_BUF_t uart_buffer;
	unsigned char i , temp;
	if(FIFO_INIT(&uart_buffer , buffer1 ,5) == fifo_no_error)
		printf("FIFO INIT ----Done \n");




	for(i=0; i<7;i++){

		if (FIFO_ENQUEUE(&uart_buffer,i) == fifo_no_error)
			printf("FIFO enqueue %x ----Done \n",i);
		else
			printf("FIFO enqueue %x ----failed \n",i);
	}

	FIFO_PRINT(&uart_buffer);

	if (FIFO_DEQUEUE(&uart_buffer,&temp) == fifo_no_error)
		printf("FIFO dequeue %x ----Done \n",temp);
	if (FIFO_DEQUEUE(&uart_buffer,&temp) == fifo_no_error)
			printf("FIFO dequeue %x ----Done \n",temp);
	FIFO_PRINT(&uart_buffer);


	return 0;
}
