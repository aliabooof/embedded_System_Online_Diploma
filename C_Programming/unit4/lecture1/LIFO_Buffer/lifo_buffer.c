/*
 * lifo_buffer.c
 *
 *  Created on: 2 Oct 2022
 *      Author: aliab
 */

#include "lifo_buffer.h"

buffer_status buf_init(lifo_buf_t* lifo_buf, unsigned char* buf ,unsigned int lenght){
	lifo_buf->base = buf;
	lifo_buf->head = buf;
	lifo_buf->count=0;
	lifo_buf->lenght=lenght;
	return lifo_no_error;

}
buffer_status buf_full(lifo_buf_t* lifo_buf){
	//check if buffer is valid
	if(!lifo_buf||!lifo_buf->base||!lifo_buf->head)
		return lifo_null;
	if(lifo_buf->count >= lifo_buf->lenght)
		return lifo_full;
	else return lifo_not_full;
}

buffer_status buf_push(lifo_buf_t* lifo_buf,unsigned char item){
	//check if buffer is valid
	if(!lifo_buf||!lifo_buf->base||!lifo_buf->head)
			return lifo_null;
	if( buf_full(lifo_buf) == lifo_full)
		return lifo_full;

	*(lifo_buf->head)=item;
	lifo_buf->head++;
	lifo_buf->count++;
	return lifo_no_error;

}
buffer_status buf_pop(lifo_buf_t* lifo_buf,unsigned char* item){
	//check if buffer is valid
	if(!lifo_buf||!lifo_buf->base||!lifo_buf->head)
		return lifo_null;
	if(lifo_buf->base == lifo_buf->head)
		return lifo_empty;
	lifo_buf->head--;
	*item=*(lifo_buf->head);
	lifo_buf->count--;
	return lifo_no_error;

}
