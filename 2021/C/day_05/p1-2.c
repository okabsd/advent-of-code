#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define SIZE 1000
#define FORMAT_STRING "%" SCNd64 ",%" SCNd64 " -> %" SCNd64 ",%" SCNd64

static uint64_t grid[SIZE][SIZE];

static void
minswap(int64_t *a, int64_t *b)
{
	if (*a > *b) {
		int64_t t = *a;
		*a = *b;
		*b = t;
	}
}

static int8_t
dir(int64_t a, int64_t b)
{
	return a > b ? -1: 1;
}

static bool
in_bounds(int64_t start, int64_t end, int8_t dir)
{
	return dir == 1 ? start <= end : start >= end;
}

int
main(int argc, char **argv)
{
	int64_t xs, ys, xe, ye;
	int64_t total = 0;

	bool running_p2 = argc > 1 && 0 == strcmp(argv[1], "p2");

	while (4 == fscanf(stdin, FORMAT_STRING, &xs, &ys, &xe, &ye)) {
		if (xs == xe || ys == ye) {
			minswap(&xs, &xe);
			minswap(&ys, &ye);

			for (int64_t x = xs; x <= xe; x++)
				for (int64_t y = ys; y <= ye; y++)
					if (++grid[x][y] == 2)
						total++;
		} else if (running_p2) {
			int8_t xd = dir(xs, xe);
			int8_t yd = dir(ys, ye);

			while (in_bounds(xs, xe, xd) && in_bounds(ys, ye, yd)) {
				if (++grid[xs][ys] == 2)
					total++;

				xs += xd;
				ys += yd;
			}
		}
	}

	printf("%" PRId64 "\n", total);
}
