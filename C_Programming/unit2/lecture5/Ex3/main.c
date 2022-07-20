/*
 * main.c
 *
 *  Created on: 20 Jul 2022
 *      Author: aliab
 */

#include "stdio.h"
#include "string.h"

void reverse();
int main()
{
	printf("Enter a sentence:");
	fflush(stdin); fflush(stdout);
	reverse();

	return 0;
}

void reverse()
{
	char c;
	scanf("%c",&c);
	if(c!='\n')
	{
		reverse();
		printf("%c",c);
	}


}
