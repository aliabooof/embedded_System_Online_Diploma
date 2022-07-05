#include "stdio.h"

int main()
{
	char num;
	printf("Enter an alphabet: ");
	fflush(stdin); fflush(stdout);
	scanf("%c", &num);
	switch(num)
	{
	case 'a':
	case 'A':
	case 'e':
	case 'E':
	case 'i':
	case 'I':
	case 'o':
	case 'O':
	case 'u':
	case 'U':
		printf("%c is a vowel", num);
		break;
	default:
		printf("%c is a consonant", num);
	}
	return 0;
}
