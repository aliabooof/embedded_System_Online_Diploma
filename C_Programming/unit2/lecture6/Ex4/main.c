/*
 * main.c
 *
 *  Created on: 30 Sep 2022
 *      Author: aliab
 */


#include <stdio.h>
struct student{
	char name[50];
	int roll;
	float marks;
};
int main(){
	struct student s[10];
	int i;
	printf("Enter information of students:\n");
	for(i=0;i<10;++i)
	{
		s[i].roll=i+1;
		printf("\nForroll number %d\n",s[i].roll);
		printf("Enter name: ");
		fflush(stdin); 	fflush(stdout);
		scanf("%s",s[i].name);
		printf("Enter marks:");
		fflush(stdin); 	fflush(stdout);
		scanf("%f",&s[i].marks);
		printf("\n");
	}
	printf("Displaying information of students:\n\n");
	for(i=0;i<10;++i)
	{
		printf("\nInformation for roll number %d:\n",i+1);
		printf("Name:");
		puts(s[i].name);
		printf("Marks: %.1f",s[i]. marks);
	}

	return 0;

}
