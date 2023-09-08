#include "stdio.h"

int main()
{
	int num1, num2, temp;
	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num1);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num2);
	temp = num1;
	num1 = num2;
	num2 = temp;
	printf("After swapping, value of a = %d\n", num1);
	printf("After swapping, value of b = %d", num2);
	return 0;
}
