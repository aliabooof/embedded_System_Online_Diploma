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

	char string[100];
	char reversed[100];
	int i;

	printf("Enter the string: ");
	fflush(stdout);fflush(stdin);
	gets(string);

	for(i=0;i<strlen(string);i++)
	{
		reversed[i]=string[strlen(string)-i-1];
	}
	reversed[i]=0;
	printf("Reverse string is: %s",reversed);


return 0 ;

}
