/*
 * main.c
 *
 *  Created on: 4 Oct 2022
 *      Author: aliab
 */


#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "conio.h"

#define Dprintf(...) {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}



struct Sdata{
	int ID;
	char name[40];
	float height;
};

struct Sstudent{
	struct Sdata Student;
	struct Sstudent* pNextStudent;
};

struct Sstudent* gpFirstStudent = NULL;

void FillRecords(struct Sstudent* new_student){

	char temp_text[40];
	Dprintf("Enter student ID : \n");
	gets(temp_text);
	new_student->Student.ID = atoi(temp_text);

	Dprintf("Enter student name : \n");
	gets(new_student->Student.name);


	Dprintf("Enter student height : \n");
	gets(temp_text);
	new_student->Student.height = atof(temp_text);


}


void AddStudent(){

	struct Sstudent* pLastStudent;
	struct Sstudent* pNewStudent;

	if(gpFirstStudent == NULL){
		//create first pointer
		pNewStudent = (struct Sstudent *) malloc(sizeof(struct Sstudent));
		gpFirstStudent = pNewStudent;

	}else{

		pLastStudent = gpFirstStudent;
		//find the last student record
		while(pLastStudent->pNextStudent){
			pLastStudent = pLastStudent->pNextStudent;
		}
		//create new record and assign next pointer to it
		pNewStudent = (struct Sstudent *) malloc(sizeof(struct Sstudent));
		pLastStudent->pNextStudent=pNewStudent;


	}

	//fill the new record
	FillRecords(pNewStudent);

	//set next record to null
	pNewStudent->pNextStudent = NULL;
}

int DeleteRecord(){
	char temp_text[40];
	int selected_id;
	Dprintf("Enter student ID to be deleted : \n");
	gets(temp_text);
	selected_id = atoi(temp_text);


	if(gpFirstStudent){
		struct Sstudent* pSelectedStudent = gpFirstStudent;
		struct Sstudent* pPrevStudent = NULL;
		while(pSelectedStudent){
			if(pSelectedStudent->Student.ID == selected_id){
				if(pPrevStudent){
					pPrevStudent->pNextStudent = pSelectedStudent->pNextStudent;

				}else{
					gpFirstStudent=pSelectedStudent->pNextStudent;

				}
				free(pSelectedStudent);
				return 1;
			}
			pPrevStudent = pSelectedStudent;
			pSelectedStudent = pSelectedStudent->pNextStudent;
		}
	}
	Dprintf("couldn\'t find the student \n");
	return 0 ;
}

void ViewStudents(){
	int count = 0;
	struct Sstudent* pCurrentStudent = gpFirstStudent;


	if(gpFirstStudent == NULL){

		Dprintf("list is empty")
	}


	while(pCurrentStudent){
		Dprintf("Record number %d \n",count+1);
		Dprintf("ID : %d \n",pCurrentStudent->Student.ID);
		Dprintf("Name : %s \n",pCurrentStudent->Student.name);
		Dprintf("Height : %f \n",pCurrentStudent->Student.height);
		pCurrentStudent = pCurrentStudent->pNextStudent;
		count++;

	}

}



int GetNth(int index){
	int count = 0;
	struct Sstudent* pCurrentNode = gpFirstStudent;
	if(!gpFirstStudent){
		Dprintf("Empty list \n");
		return 0;
	}
	while(pCurrentNode){
		if(count == index)
		{
			Dprintf("Node which has index %d \n",index);
			Dprintf("ID : %d \n",pCurrentNode->Student.ID);
			Dprintf("Name : %s \n",pCurrentNode->Student.name);
			Dprintf("Height : %f \n",pCurrentNode->Student.height);
			return 0;
		}
		pCurrentNode = pCurrentNode->pNextStudent;
		count++;

	}
	Dprintf("couldn\'t find node with index %d /n",index);
	return 0;
}


void DeleteAll(){

	struct Sstudent* pCurrentStudent = gpFirstStudent;
	if(gpFirstStudent == NULL)
		Dprintf("List is empty\n");
	while(pCurrentStudent){
		struct Sstudent* temp = pCurrentStudent;
		pCurrentStudent = pCurrentStudent->pNextStudent;
		free(temp);
	}
	gpFirstStudent = NULL;
}

int GetLength(){
	int length = 0;
	struct Sstudent* pCurrentNode = gpFirstStudent;
	if(!gpFirstStudent)
			return 0;
	while(pCurrentNode){
		length++;
		pCurrentNode = pCurrentNode->pNextStudent;
	}
	return length;


}

int main(){

	char text_temp[40];
	while(1){
		Dprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
		Dprintf("\t choose one of the following \n");
		Dprintf("1 Add student \n");
		Dprintf("2 View student \n");
		Dprintf("3 Delete student \n");
		Dprintf("4 Delete all students \n");
		Dprintf("5 View node \n");
		Dprintf("6 View length \n");
		Dprintf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ \n");
		gets(text_temp);
		switch (atoi(text_temp)){

		case 1:AddStudent();
		break;
		case 2: ViewStudents();
		break;
		case 3: DeleteRecord();
		break;
		case 4: DeleteAll();
		break;
		case 5:{
			Dprintf("Enter index \n ");
			gets(text_temp);
			GetNth(atoi(text_temp));
		}
		break;
		case 6 : Dprintf("Length of list is %d \n",GetLength());
				break;

		default: Dprintf("wrong option \n");
		break;

		}
	}

	return 0;
}
