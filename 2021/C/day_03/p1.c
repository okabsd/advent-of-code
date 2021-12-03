#include <stdio.h>
#include <stdlib.h>

#define BITLENGTH 12

static char
mcb(const unsigned b[2])
{
	return b[1] >= b[0] ? '1' : '0';
}

int
main(void)
{
	unsigned bits[BITLENGTH][2] = { 0 };
	char gamma[BITLENGTH + 1] = { 0 };
	char epsilon[BITLENGTH + 1] = { 0 };
	char buffer[64];

	while (fgets(buffer, sizeof buffer, stdin))
		for (size_t i = 0; i < BITLENGTH; i++)
			bits[i][buffer[i] - '0']++;

	for (size_t i = 0; i < BITLENGTH; i++)
		epsilon[i] = (gamma[i] = mcb(bits[i])) == '0' ? '1': '0';

	printf("%ld\n", strtol(gamma, NULL, 2) * strtol(epsilon, NULL, 2));
}
