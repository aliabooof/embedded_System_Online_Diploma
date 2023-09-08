/*
 * main.c
 *
 *  Created on: 4 Jul 2022
 *      Author: aliab
 */
#include "stdio.h"
int main()
{
	float arr1[2][2];
	float arr2[2][2];
	float arr3[2][2];


	printf("Enter the element of the 1st matrix\r\n");
	for(int i=0; i<2;i++)
	{
		for (int j = 0;j<2 ; j++)
		{
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdin);	fflush(stdout);
			scanf("%f",&arr1[i][j]);
		}

	}

	printf("Enter the element of the 2nd matrix\r\n");
	for(int i=0; i<2;i++)
	{
		for (int j = 0;j<2 ; j++)
		{
			printf("Enter b%d%d: ",i+1,j+1);
			fflush(stdin);	fflush(stdout);
			scanf("%f",&arr2[i][j]);
		}

	}


	for(int i=0; i<2;i++)
	{
		for (int j = 0;j<2 ; j++)
		{
			arr3[i][j]=	arr1[i][j]+	arr2[i][j];

		}

	}

	printf("the matrix is :\r\n");
	for(int i=0; i<2;i++)
		{
			for (int j = 0;j<2 ; j++)
			{
				printf("%.1f \t",arr3[i][j]);

			}
			printf("\r\n");

		}
	return 0;
}

