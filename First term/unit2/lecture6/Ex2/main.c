/*
 * main.c
 *
 *  Created on: 30 Sep 2022
 *      Author: aliab
 */


#include "stdio.h"
struct distance {
	int feet;
	float inch;
}d1,d2,result;
int main(){
	printf("enter information for 1st distance : \n");
	printf("Enter feet:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d1.feet);
	printf("Enter inch:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&d1.inch);
	printf("enter information for 2nd distance : \n");
	printf("Enter feet:");
	fflush(stdin);fflush(stdout);
	scanf("%d",&d2.feet);
	printf("Enter inch:");
	fflush(stdin);fflush(stdout);
	scanf("%f",&d2.inch);

	result.feet = d1.feet + d2.feet;
	result.inch = d1.inch + d2.inch;
	if(result.inch > 12){
		result.inch = result.inch - 12;
		++result.feet;
	}
	printf("sum of distances = %d\'-%.1f\"",result.feet,result.inch);


}
