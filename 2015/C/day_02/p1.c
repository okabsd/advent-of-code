#include <stdio.h>

static int
min(int *array, size_t length)
{
	int value = array[0];

	for (size_t i = 1; i < length; i++)
		if (array[i] < value)
			value = array[i];

	return value;
}

static int
sum(int *array, size_t length)
{
	int value = 0;

	for (size_t i = 0; i < length; i++)
		value += array[i];

	return value;
}

int
main(void)
{
	int length = 0;
	int width = 0;
	int height = 0;
	int total = 0;

	while (3 == scanf("%dx%dx%d\n", &length, &width, &height)) {
		int sides[3] = { length * width, width * height, height * length };

		total += 2 * sum(sides, 3) + min(sides, 3);
	}

	printf("%d\n", total);
}
