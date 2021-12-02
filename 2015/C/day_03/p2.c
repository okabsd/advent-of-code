#include <stdio.h>
#include <stdlib.h>

struct house {
	int x;
	int y;
};

static void
add_house(struct house **dest, size_t *sz, int x, int y)
{
	*dest = realloc(*dest, sizeof **dest * (*sz + 1));

	(*dest)[*sz].x = x;
	(*dest)[*sz].y = y;

	*sz += 1;
}

static struct house *
find_house(struct house *set, size_t length, int x, int y)
{
	for (size_t i = 0; i < length; i++)
		if (set[i].x == x && set[i].y == y)
			return set + i;

	return NULL;
}

int
main(void)
{
	struct house locations[2] = { 0 };
	size_t turn = 0;
	struct house *houses = NULL;
	size_t n_houses = 0;
	int c;

	add_house(&houses, &n_houses, 0, 0);

	while ((c = fgetc(stdin)) != EOF) {
		switch (c) {
			case '>': locations[turn].x++; break;
			case '<': locations[turn].x--; break;
			case '^': locations[turn].y++; break;
			case 'v': locations[turn].y--; break;
		}

		if (!find_house(houses, n_houses, locations[turn].x, locations[turn].y))
			add_house(&houses, &n_houses, locations[turn].x, locations[turn].y);

		turn = (turn + 1) % 2;
	}

	printf("%zu\n", n_houses);

	free(houses);
}
