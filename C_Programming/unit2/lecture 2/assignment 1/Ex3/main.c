#include <stdio.h>
#include <stdlib.h>
int main()
{
	int num1, num2, sum;
	printf("enter 2 integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%d %d", &num1, &num2);
	sum = num1 + num2;
	printf("sum: %d", sum);
	return 0;
}
