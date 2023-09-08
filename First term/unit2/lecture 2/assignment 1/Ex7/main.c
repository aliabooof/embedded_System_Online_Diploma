#include <stdio.h>
#include <stdlib.h>
int main()
{
	int num1, num2;
	printf("Enter value of a: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num1);
	printf("Enter value of b: ");
	fflush(stdin); fflush(stdout);
	scanf("%d", &num2);
	num1 = num1 + num2;
	num2 = num1 - num2;
	num1 = num1 - num2;
	printf("After swapping, value of a = %d\n", num1);
	printf("After swapping, value of b = %d", num2);
	return 0;
}
