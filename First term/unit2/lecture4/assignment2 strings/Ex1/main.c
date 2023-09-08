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
	char c;
	int  freq=0;
	char string[100];

	printf("Enter a string: ");
	fflush(stdout);fflush(stdin);
	gets(string);

	printf("Enter a character to find frequency: ");
	fflush(stdout);fflush(stdin);
	scanf("%c",&c);

	for(int i=0;i<strlen(string);i++)
	{
		if(string[i]==c){freq++;}
	}

	printf("Frequency of %c = %d",c,freq);


return 0 ;

}
