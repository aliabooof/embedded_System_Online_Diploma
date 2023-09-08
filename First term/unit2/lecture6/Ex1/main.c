/*
 * main.c
 *
 *  Created on: 30 Sep 2022
 *      Author: aliab
 */


#include "stdio.h"

struct student{
	char name[50];
	int roll;
	float marks;
};
int main(){

	struct student s;
	printf("Enter student name : ");
	fflush(stdin); fflush(stdout);
	scanf("%s",&s.name);
	printf("Enter roll number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&s.roll);
	printf("Enter marks : ");
	fflush(stdin); fflush(stdout);
	scanf("%f",&s.marks);
	printf("displaying information : \n");
	printf("name : %s\n",s.name);
	printf("roll : %d\n",s.roll);
	printf("marks : %f\n",s.marks);
	return 0;
}
