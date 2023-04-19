/*
 * fifo_buffer.c
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */

#include "fifo_buffer.h"

//APIS
buffer_status FIFO_INIT(FIFO_BUF_t* fifo, element_type* buff,unsigned int length){

	fifo->count = 0;
	fifo->length = length;
	fifo->base = buff;
	fifo->head = buff;
	fifo->tail = buff;
	return fifo_no_error;

}



buffer_status FIFO_ENQUEUE(FIFO_BUF_t* fifo,element_type item){

	//checking FIFO is valid
	if(!fifo || !fifo->base || !fifo->head || !fifo->tail)
		return fifo_null;

	if(FIFO_IS_FULL(fifo) == fifo_full)
		return fifo_full;

	*(fifo->head) = item;
	fifo->count++;
	if(fifo->head == fifo->base + (sizeof(element_type) * fifo->length))
		fifo->head = fifo->base;
	else
		fifo->head++;

	return fifo_no_error;

}

buffer_status FIFO_DEQUEUE(FIFO_BUF_t* fifo,element_type* item){
	//checking FIFO is valid
	if(!fifo || !fifo->base || !fifo->head || !fifo->tail)
		return fifo_null;
	//checking if FIFO is empty
	if(fifo->count == 0)
		return fifo_empty;
	*item = *(fifo->tail);
	fifo->count--;
	if(fifo->tail == fifo->base + (sizeof(element_type) * fifo->length))
			fifo->tail = fifo->base;
		else
			fifo->tail++;
	return fifo_no_error;


}



buffer_status FIFO_IS_FULL(FIFO_BUF_t* fifo){
	//checking FIFO is valid
	if(!fifo || !fifo->base || !fifo->head || !fifo->tail)
		return fifo_null;

	if(fifo->count == fifo->length)
		return fifo_full;
	else
		return fifo_no_error;
}


void FIFO_PRINT(FIFO_BUF_t* fifo){

	element_type* temp;
	int i;
	if(fifo->count == 0)
		printf("FIFO is empty\n");
	else{
	temp = fifo->tail;
	for(i=0; i < (fifo->count) ;i++){
		printf("%X \n",*temp);
		temp++;
	}

	}

}

