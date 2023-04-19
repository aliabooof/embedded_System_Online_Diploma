/*
 * fifo_buffer.h
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */

#ifndef FIFO_BUFFER_H_
#define FIFO_BUFFER_H_

#include "stdint.h"
#include "stdio.h"


#define element_type uint8_t
element_type buffer1[5];

typedef struct {
	unsigned int count;
	unsigned int length;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_BUF_t;

typedef enum{
	fifo_no_error,
	fifo_full,
	fifo_empty,
	fifo_null
}buffer_status;


//APIS
buffer_status FIFO_INIT(FIFO_BUF_t* fifo, element_type* buff,unsigned int length);
buffer_status FIFO_ENQUEUE(FIFO_BUF_t* fifo,element_type item);
buffer_status FIFO_DEQUEUE(FIFO_BUF_t* fifo,element_type* item);
buffer_status FIFO_IS_FULL(FIFO_BUF_t* fifo);
void FIFO_PRINT(FIFO_BUF_t* fifo);


#endif /* FIFO_BUFFER_H_ */
