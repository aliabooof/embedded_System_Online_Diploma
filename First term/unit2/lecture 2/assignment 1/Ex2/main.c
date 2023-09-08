#include "stdio.h"

int main()
{
	int num;
	printf("enter a integer: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num);
	printf("you entered: %d", num);
	return 0;
}
