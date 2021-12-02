#include <stdio.h>
#include <string.h>

#define FRAME_SIZE 4
#define WINDOW_SIZE (FRAME_SIZE - 1)

static unsigned
usum(unsigned *array, size_t length)
{
	unsigned sum = 0;

	for (size_t i = 0; i < length; i++)
		sum += array[i];

	return sum;
}

int
main(void)
{
	unsigned frame[FRAME_SIZE] = { 0 };
	unsigned slopes = 0;

	for (size_t i = 0; i < FRAME_SIZE; i++)
		scanf("%u", frame + i);

	 do {
		if (usum(frame + 1, WINDOW_SIZE) > usum(frame, WINDOW_SIZE))
			slopes++;

		memmove(frame, frame + 1, sizeof *frame * WINDOW_SIZE);
	} while (1 == scanf("%u", frame + WINDOW_SIZE));

	printf("%u\n", slopes);
}
