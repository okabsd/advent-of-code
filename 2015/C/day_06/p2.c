#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

enum command {
	OFF,
	ON,
	TOGGLE,
	NONE
};

struct lightpoint {
	size_t x;
	size_t y;
};

static uint8_t lights[1000][1000];

static enum command
parse(const char *input, struct lightpoint *start, struct lightpoint *end)
{
	const char *commands[] = { "turn off", "turn on", "toggle" };

	for (enum command cmd = OFF; cmd < NONE; cmd++) {
		size_t cmd_len = strlen(commands[cmd]);

		if (0 == strncmp(input, commands[cmd], cmd_len) &&
			4 == sscanf(input + cmd_len, "%zu,%zu through %zu,%zu",
						&start->x, &start->y, &end->x, &end->y))
				return cmd;
	}

	return NONE;
}

static void
execute(enum command c, struct lightpoint *start, struct lightpoint *end)
{
	for (size_t x = start->x; x <= end->x; x++)
		for (size_t y = start->y; y <= end->y; y++)
			switch (c) {
				case OFF:
					if (lights[x][y])
						lights[x][y]--;
					break;
				case ON:
					lights[x][y]++;
					break;
				case TOGGLE:
					lights[x][y] += 2;
					break;
				default:
				case NONE:
					break;
			}
}

static uint64_t
total_brightness(void)
{
	uint64_t brightness = 0;

	for (size_t i = 0; i < 1000; i++)
		for (size_t j = 0; j < 1000; j++)
			brightness += lights[i][j];

	return brightness;
}

int
main(void)
{
	char buffer[128];
	enum command cmd;
	struct lightpoint start;
	struct lightpoint end;

	while (fgets(buffer, sizeof buffer, stdin))
		if ((cmd = parse(buffer, &start, &end)) != NONE)
			execute(cmd, &start, &end);

	printf("%" PRIu64 "\n", total_brightness());
}
