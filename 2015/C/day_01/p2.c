#include <stdio.h>

int
main(void)
{
	int c = 0;
	int floor = 0;
	int instruction = 0;

	while ((c = fgetc(stdin)) != EOF) {
		instruction++;

		switch (c) {
			case '(': floor++; break;
			case ')': floor--; break;
			default: break;
		}

		if (floor == -1)
			break;
	}

	printf("%d\n", instruction);
}
