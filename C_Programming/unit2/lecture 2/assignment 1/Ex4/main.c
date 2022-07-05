#include <stdio.h>
#include <stdlib.h>
int main()
{
	float num1, num2, mul;
	printf("enter 2 integers: ");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &num1, &num2);
	mul = num1 * num2;
	printf("product: %f", mul);
	return 0;
}
