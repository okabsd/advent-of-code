#include <limits.h>
#include <stdio.h>

int
main(void)
{
	unsigned depth = UINT_MAX;
	unsigned reading = 0;
	unsigned slopes = 0;

	while (1 == scanf("%u", &reading)) {
		if (reading > depth)
			slopes++;

		depth = reading;
	}

	printf("%u\n", slopes);
}
