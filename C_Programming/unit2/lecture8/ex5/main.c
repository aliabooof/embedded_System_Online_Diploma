/*
 * main.c
 *
 *  Created on: Apr 29, 2023
 *      Author: aliab
 */


#include"stdio.h"
struct employee
{
	char* m_name;
	int m_id;

}	S_emp1 = {"ali", 1000}, S_emp2 = {"diaa", 1001}, S_emp3 = {"ahmed", 1002};




int main()
{
struct employee* arr[3] = {&S_emp1, &S_emp2, &S_emp3};
struct employee (*(*ptr)[3]) = &arr;
printf("%s\n", (*(*ptr + 1))->m_name);
printf("%d", (*(*ptr + 1))->m_id);





	return 0;
}
