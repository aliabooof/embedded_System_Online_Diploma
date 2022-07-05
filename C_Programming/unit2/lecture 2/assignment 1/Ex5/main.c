#include "stdio.h"

int main()
{
	char num;
	printf("Enter a character: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &num);
	printf("ASCII value of G = %d", num);
	return 0;
}
