#include <stdio.h>

int
main(void)
{
	int c = 0;
	int floor = 0;

	while ((c = fgetc(stdin)) != EOF)
		switch (c) {
			case '(': floor++; break;
			case ')': floor--; break;
			default: break;
		}

	printf("%d\n", floor);
}
