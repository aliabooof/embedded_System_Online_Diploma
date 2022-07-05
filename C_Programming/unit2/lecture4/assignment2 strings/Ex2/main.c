/*
 * main.c
 *
 *  Created on: 4 Jul 2022
 *      Author: aliab
 */


#include <stdio.h>
#include "string.h"

int main()
{

	int  i,len=0;
	char string[100];

	printf("Enter a string: ");
	fflush(stdout);fflush(stdin);
	gets(string);

	for(i=0;string[i]!=0;i++)
	{
		len++;
	}


	printf("Length of string : %d",len);


return 0 ;

}
