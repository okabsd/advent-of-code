#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BITLENGTH 12

static size_t
getlines(char ***dest, FILE *file)
{
	size_t n = 0;
	size_t length;
	char buffer[1024];

	while (fgets(buffer, sizeof buffer, file)) {
		*dest = realloc(*dest, sizeof **dest * (n + 1));
		length = strlen(buffer);
		buffer[length - 1] = '\0';
		(*dest)[n++] = strcpy(malloc(length), buffer);
	}

	return n;
}

static char
mcb(const unsigned b[2])
{
	return b[1] >= b[0] ? '1' : '0';
}

static char
lcb(const unsigned b[2])
{
	return b[0] <= b[1] ? '0' : '1';
}

static char
bit_select(
	char **data,
	size_t length,
	size_t at,
	char (*selector)(const unsigned [2]))
{
	unsigned bits[2] = { 0 };

	for (size_t i = 0; i < length; i++)
		if (data[i])
			bits[data[i][at] - '0']++;

	return selector(bits);
}

static void
filter(char **data, size_t *length, size_t at, char bit)
{
	for (size_t i = *length - 1; i != SIZE_MAX; i--)
		if (data[i][at] != bit) {
			for (size_t j = i; j < *length - 1; j++)
				data[j] = data[j + 1];

			(*length)--;
		}
}

static const char *
find_rating(char **list, size_t length, char (*selector)(const unsigned [2]))
{
	const char *final;
	char bit;
	size_t pos = 0;
	char **data = malloc(sizeof *data * length);

	memcpy(data, list, sizeof *data * length);

	while (pos < BITLENGTH && length != 1) {
		bit = bit_select(data, length, pos, selector);
		filter(data, &length, pos, bit);
		pos++;
	}

	final = data[0];
	free(data);

	return final;
}

int
main(void)
{
	char **lines = NULL;
	size_t length = getlines(&lines, stdin);
	const char *oxygen = find_rating(lines, length, mcb);
	const char *co2 = find_rating(lines, length, lcb);

	printf("%ld\n", strtol(oxygen, NULL, 2) * strtol(co2, NULL, 2));

	for (size_t i = 0; i < length; i++)
		free(lines[i]);

	free(lines);
}
