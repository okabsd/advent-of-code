#include <stdio.h>
#include <string.h>

int
main(void)
{
	char command[16] = { 0 };
	int distance = 0;
	int horizontal = 0;
	int depth = 0;
	int aim = 0;

	while (2 == scanf("%15s%d", command, &distance)) {
		if (strcmp(command, "forward") == 0) {
			horizontal += distance;
			depth += aim * distance;
		} else if (strcmp(command, "down") == 0)
			aim += distance;
		else if (strcmp(command, "up") == 0)
			aim -= distance;
	}

	printf("%d\n", horizontal * depth);
}
