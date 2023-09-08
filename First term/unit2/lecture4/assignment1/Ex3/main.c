/*
 * main.c
 *
 *  Created on: 4 Jul 2022
 *      Author: aliab
 */

#include "stdio.h"
int main()
{
	int arr[10][10],tra[10][10],r,c,i,j;
	printf("Enter rows and column of matrix:");
	fflush(stdin);   fflush(stdout);
	scanf("%d %d",&r,&c);
	printf("Enter elements of matrix:\n");
	for (i=0;i<r;i++)
	{
		for (j=0;j<c;j++)
		{
			printf("Enter element a%d%d :",i+1,j+1);
			fflush(stdin);   fflush(stdout);
			scanf("%d",&arr[i][j]);
		}
	}

	printf("Entered matrix is :\n");
	for(int i=0; i<r;i++)
	{
		for (int j = 0;j<c ; j++)
		{
			printf("%d \t",arr[i][j]);

		}
		printf("\r\n");

			}


	for(int i=0; i<r;i++)
		{
			for (int j = 0;j<c ; j++)
			{
				tra[j][i]=arr[i][j];

			}

				}
	printf("transpose of matrix :\n");
		for(int i=0; i<c;i++)
		{
			for (int j = 0;j<r ; j++)
			{
				printf("%d \t",tra[i][j]);

			}
			printf("\r\n");

				}



	return 0;
}
