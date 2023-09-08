/*
 * main.c
 *
 *  Created on: 20 Jul 2022
 *      Author: aliab
 */


#include "stdio.h"


int calc_power(int n1,int n2);


int main()
{
	int base,power;
	printf("Enter base number:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&base);
	printf("Enter power number(positive integer):");
	fflush(stdin); fflush(stdout);
	scanf("%d",&power);
	printf("%d ^ %d = %d",base,power,calc_power(base,power));


}



int calc_power(int n1,int n2)
{
	if(n2!=0)
		return n1*calc_power(n1,n2-1);
	else
		return 1;

}
