/*
 * main.c
 *
 *  Created on: 4 Jul 2022
 *      Author: aliab
 */
#include "stdio.h"
int main()
{
	int nums[20],n,element,loc,i;


	printf("Enter number of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	while(n>20||n<=0)
	{
		printf("Enter no of elements : ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&n);

	}


	for(int i=0;i<n; i++)
		scanf("%d",&nums[i]);


	printf("Enter the element to be searched : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);


	for (i=0;i<n;i++)
	{
		if(nums[i]==element)
		{
			loc=i+1;
			printf("Number found at location %d",loc);
		}
	}


	return 0;
}

