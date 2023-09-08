/*
 * main.c
 *
 *  Created on: 20 Jul 2022
 *      Author: aliab
 */


#include "stdio.h"
#include "stdbool.h"

bool check_prime(int num);
int main()
{
	int n1,n2;
	printf("enter two numbers(intervals):");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &n1,&n2);
	printf("prime numbers between %d and %d are:",n1,n2);
	for(int i =n1+1; i<n2;i++)
	{
		if (check_prime(i))
			printf("%d  ",i);
	}


	return 0;
}



bool check_prime(int num)
{

	if (num==1||num==0)
		return false;
	else{
		for (int i =2;i<=num/2;i++)
		{
			if (num%i==0)
			{
				return false;
				break;
			}


			else
				return true;
		}



	}


}
