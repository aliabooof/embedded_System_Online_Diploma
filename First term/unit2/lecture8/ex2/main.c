/*
 * main.c
 *
 *  Created on: Apr 29, 2023
 *      Author: aliab
 */


#include"stdio.h"
int main()
{
	int i;
	char z = 'A';
	char* ptr = &z;
	for(i = 0;i < ('Z' - 'A');i++)
	{
		printf(" %c\t", *ptr + i);


	}

	return 0;
}
