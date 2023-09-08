/*
 * main.c
 *
 *  Created on: 30 Sep 2022
 *      Author: aliab
 */


#include <stdio.h>
#define Pi 3.1415
#define area(r) (Pi*(r)*(r))
int main(){
	int radius;
	float area;
	printf("Enter the radius: ");
	fflush(stdin);	fflush(stdout);
	scanf("%d", &radius);
	area=area(radius);
	printf("Area=%.2f", area);
	return 0;

}
