#include <openssl/md5.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

static void
compute_hashhex(char hex[33], const char *input, size_t length)
{
	unsigned char digest[16];
	MD5_CTX context;

	MD5_Init(&context);
	MD5_Update(&context, input, length);
	MD5_Final(digest, &context);

	for (size_t i = 0; i < 16; i++)
		sprintf(hex + (i * 2), "%02x", (unsigned int) digest[i]);
}

static uint64_t
find_lowest_hashcat(const char *key, const char *prefix, size_t length, uint64_t n)
{
	char keycat[128];
	char hexres[33];

	while (n < UINT64_MAX) {
		int rv = snprintf(keycat, sizeof keycat, "%s%" PRIu64, key, n);

		if (rv < 0 || (size_t) rv >= sizeof keycat) {
			fprintf(stderr, "key concatenation error. (RC: %d, bufsize: %zu).\n", rv, sizeof keycat);
			exit(EXIT_FAILURE);
		}

		compute_hashhex(hexres, keycat, (size_t) rv);

		if ((strncmp(hexres, prefix, length) == 0))
			break;

		n++;
	}

	return n;
}

int
main(int argc, char **argv)
{
	if (argc > 2)
		printf("%" PRIu64 "\n", find_lowest_hashcat(argv[1], argv[2], strlen(argv[2]), 0));
	else
		fprintf(stderr, "usage: %s KEY PREFIX\n", argv[0]);
}
