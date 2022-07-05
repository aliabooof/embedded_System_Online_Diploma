/*
 * main.c
 *
 *  Created on: 4 Jul 2022
 *      Author: aliab
 */


#include "stdio.h"
int main()
{
	float nums[100], average , sum=0;
	int n;

	printf("Enter number of data : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	while(n>100||n<=0)
	{
		printf("Enter number of data : ");
		fflush(stdin); fflush(stdout);
		scanf("%d",&n);

	}
	for(int i=0;i<n; i++)
	{
		printf("Enter number :");
		fflush(stdin); fflush(stdout);
		scanf("%f",&nums[i]);
		sum+=nums[i];
	}

	average = sum / n;
	printf("Average = %.2f",average);



	return 0;
}
