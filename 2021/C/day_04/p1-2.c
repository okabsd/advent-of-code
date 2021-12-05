#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cell {
	bool marked;
	unsigned number;
};

struct board {
	struct cell cells[5][5];
	bool has_won;
};

static size_t
parse_inputs(unsigned **list, char *csv_data)
{
	size_t n = 0;
	unsigned temp;

	for (
		char *tok = strtok(csv_data, ",");
		tok;
		tok = strtok(NULL, ",")
	) {
		if (1 != sscanf(tok, "%u", &temp))
			break;

		*list = realloc(*list, sizeof **list * (n + 1));
		(*list)[n++] = temp;
	}

	return n;
}

static size_t
parse_boards(struct board **list, FILE *src)
{
	size_t n = 0;

	while (1) {
		*list = realloc(*list, sizeof **list * (n + 1));

		for (size_t i = 0; i < 5; i++) {
            for (size_t j = 0; j < 5; j++) {
				if (1 != fscanf(src, "%u", &((*list)[n].cells[i][j].number))) {
					*list = realloc(*list, sizeof **list * n);
					return n;
				}

				(*list)[n].cells[i][j].marked = false;
			}

			(*list)[n].has_won = false;
		}

		n++;
	}

	return n;
}

static bool
row_all_marked(struct board *b, size_t n)
{
	for (size_t i = 0; i < 5; i++)
		if (!b->cells[n][i].marked)
			return false;

	return true;
}

static bool
col_all_marked(struct board *b, size_t n)
{
	for (size_t i = 0; i < 5; i++)
		if (!b->cells[i][n].marked)
			return false;

	return true;
}

static bool
check_win_condition(struct board *b)
{
	for (size_t i = 0; i < 5; i++) {
		if (row_all_marked(b, i))
			return true;

		if (col_all_marked(b, i))
			return true;
	}

	return false;
}

static bool
apply_marks(struct board *b, unsigned n)
{
	if (b->has_won)
		return false;

	for (size_t i = 0; i < 5; i++)
		for (size_t j = 0; j < 5; j++)
			if (b->cells[i][j].number == n)
				b->cells[i][j].marked = true;

	return check_win_condition(b);
}

static unsigned
sum_unmarked(struct board *b)
{
    unsigned t = 0;

    for (size_t i = 0; i < 5; i++)
        for (size_t j = 0; j < 5; j++)
            if (!b->cells[i][j].marked)
                t += b->cells[i][j].number;

    return t;
}

static unsigned
simulate_game(
	struct board *boards,
	size_t b_len,
	unsigned *inputs,
	size_t i_len,
	struct board **final,
	bool report_first_win)
{
	size_t counter = 0;

	for (size_t i = 0; i < i_len; i++)
		for (size_t b = 0; b < b_len; b++)
			if (apply_marks(boards + b, inputs[i])) {
				boards[b].has_won = true;

				if (report_first_win || ++counter == b_len) {
					*final = boards + b;
					return inputs[i];
				}
			}

	*final = NULL;
	return UINT_MAX;
}

static void
cheat_at_bingo(char *input_data, FILE *file, bool which)
{
	unsigned *inputs = NULL;
	size_t n_inputs = parse_inputs(&inputs, input_data);

	struct board *boards = NULL;
	size_t n_boards = parse_boards(&boards, file);

	struct board *result = NULL;
	unsigned last_number = simulate_game(
			boards, n_boards, inputs, n_inputs, &result, which);

	printf("%u\n", last_number * sum_unmarked(result));

	free(boards);
	free(inputs);
}

int
main(int argc, char **argv) {
	char buffer[512];
	bool find_first = 1;

	if (argc > 1) {
		if (0 == strcmp(argv[1], "-h") || 0 == strcmp(argv[1], "--help")) {
			fprintf(stderr,
				"usage: %s [first|last]\n"
				"\tDefaults to <first>.\n",
				argv[0]);
			return EXIT_SUCCESS;
		}

		find_first = 0 != strcmp(argv[1], "last");
	}

	if (!fgets(buffer, sizeof buffer, stdin)) {
		fprintf(stderr, "Could not read input.\n");
		return EXIT_FAILURE;
	}

	cheat_at_bingo(buffer, stdin, find_first);
}
