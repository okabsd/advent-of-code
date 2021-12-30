#include <stdio.h>
#include <stdlib.h>

#define LF_MAX_AGE 9
#define LF_SPAWN_RATE 1

static void
simulate_lanternfish_growth(
	unsigned long *data,
	size_t length,
	unsigned cycles,
	unsigned long spawn_rate)
{
	const size_t spawn_age = length - 1;
	const size_t recycle_age = length - 3;

	while (cycles--) {
		unsigned long recycling = data[0];
		unsigned long spawns = recycling * spawn_rate;

		for (size_t age = 0; age < spawn_age; age++)
			data[age] = data[age + 1];

		data[recycle_age] += recycling;
		data[spawn_age] = spawns;
	}
}

int
main(int argc, char **argv)
{
	unsigned total_cycles = argc > 1 ? (unsigned) atoi(argv[1]) : 80;
	unsigned long counts[LF_MAX_AGE] = { 0 };
	unsigned long sum = 0;

	for (size_t fish; 1 == scanf("%zu", &fish); (void) getchar())
		if (fish < LF_MAX_AGE)
			counts[fish]++;

	simulate_lanternfish_growth(counts, LF_MAX_AGE, total_cycles, LF_SPAWN_RATE);

	for (size_t age = 0; age < LF_MAX_AGE; age++)
		sum += counts[age];

	printf("%lu\n", sum);
}
