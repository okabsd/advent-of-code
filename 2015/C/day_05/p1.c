#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static unsigned
substrings(const char *in, int n, ...)
{
	unsigned contains = 0;
	va_list args;

	va_start(args, n);

	for (int i = 0; i < n; i++)
		if (strstr(in, va_arg(args, const char *)))
			contains++;

	va_end(args);

	return contains;
}

static int
is_nice_string(const char *string)
{
	unsigned duplicates = 0;
	unsigned vowels = 0;
	char last = '\0';

	for (const char *s = string; *s; last = *s++) {
		if (strchr("aeiou", *s))
			vowels++;

		if (*s == last)
			duplicates++;
	}

	return vowels >= 3 && duplicates &&
		!substrings(string, 4, "ab", "cd", "pq", "xy");
}

int
main(void)
{
	char buffer[64];
	unsigned nice_strings = 0;

	while (fgets(buffer, sizeof buffer, stdin))
		if (is_nice_string(buffer))
			nice_strings++;

	printf("%u\n", nice_strings);
}
