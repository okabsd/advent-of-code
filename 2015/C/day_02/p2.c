#include <stdio.h>
#include <stdlib.h>

static int
order_asc(const void *a, const void *b)
{
	return *(const int *) a - *(const int *) b;
}

static int
prod(int *array, size_t length)
{
	int value = 1;

	for (size_t i = 0; i < length; i++)
		value *= array[i];

	return value;
}

int
main(void)
{
	int dim[3] = { 0 };
	int total = 0;

	while (3 == scanf("%dx%dx%d\n", &dim[0], &dim[1], &dim[2])) {
		qsort(dim, 3, sizeof *dim, order_asc);
		total += prod(dim, 3) + 2 * (dim[0] + dim[1]);
	}

	printf("%d\n", total);
}
