/*
 * lifo_buffer.h
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */

#ifndef LIFO_BUFFER_H_
#define LIFO_BUFFER_H_

typedef struct{
	unsigned int lenght;
	unsigned char* base;
	unsigned char* head;
	unsigned int count;
}lifo_buf_t;

typedef enum {
	lifo_no_error,
	lifo_full,
	lifo_not_full,
	lifo_empty,
	lifo_null

}buffer_status;

buffer_status buf_init(lifo_buf_t* lifo_buf, unsigned char* buf ,unsigned int lenght);
buffer_status buf_push(lifo_buf_t* buf , unsigned char item);
buffer_status buf_pop(lifo_buf_t* buf,unsigned char* item);
buffer_status buf_full(lifo_buf_t* buf);
#endif /* LIFO_BUFFER_H_ */
