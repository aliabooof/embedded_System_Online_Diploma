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
	{

		scanf("%d",&nums[i]);

	}
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&element);
	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&loc);



	for (i=n;i>=loc-1;i--)
		nums[i+1]=nums[i];

	nums[loc-1]=element;


	for(i=0;i<=n;i++)
		printf("%d\t",nums[i]);

	return 0;
}
