#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N_PATTERNS 2

static _Noreturn void
die_regex_error(int err, regex_t *rgx)
{
	char ebuf[128];

	regerror(err, rgx, ebuf, sizeof ebuf);
	fprintf(stderr, "err: %s\n", ebuf);

	exit(EXIT_FAILURE);
}

static bool
all_match(const char *string, regex_t *rgxs, size_t n)
{
	for (size_t i = 0; i < n; i++)
		if (regexec(rgxs + i, string, 0, NULL, 0))
			return false;

	return true;
}

int
main(void)
{
	const char *patterns[N_PATTERNS] = { "\\(..\\).*\\1", "\\(.\\).\\1" };
	regex_t regex[N_PATTERNS];
	char buffer[64];
	unsigned nice_strings = 0;
	int err;

	for (size_t i = 0; i < N_PATTERNS; i++)
		if ((err = regcomp(regex + i, patterns[i], REG_NEWLINE)))
			die_regex_error(err, regex + i);

	while (fgets(buffer, sizeof buffer, stdin))
		if (all_match(buffer, regex, N_PATTERNS))
			nice_strings++;

	for (size_t i = 0; i < N_PATTERNS; i++)
		regfree(regex + i);

	printf("%u\n", nice_strings);
}
