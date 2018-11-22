#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"

void CPM_SO(char *P, int m, char *T, int n, unsigned int offset, unsigned int patt_size) {
	word D, mm, i, B[ASIZE], pos;
	if (m > MAX_WORD_SIZE) { printf("SO: Use pattern size <= word size"); return; }

	/* Preprocessing */
	for (i = 0; i < ASIZE; ++i) B[i] = (word)~0;
	for (i = 0; i < m; ++i) B[(unsigned char)P[i]] &= ~((word)1<<i);
	D = (word)~0; mm = (word)1 << ( m - 1); i = 0;
	char * str = NULL;
	int l_number = 0, r_number = 0;

	/* Searching */
	while (i < n) {
		D = ( D << 1 ) | B[(unsigned char)T[i]];
		if ( (D & mm) != mm ) {
			++v_count;
			/* Verifying */
			l_number = chcpml(P - offset, patt_size, T, n, i - m, offset-1, 0);
			r_number = chcpmr(P - offset, patt_size, T, n, i + 1, !offset?m:offset+m, 0);
			for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
				pos = i-m+1-l_number+a;
				indexes[pos] = true;
			}
		}
		++i;
	}
}

/* MAIN */
int main(int argc, char *argv[]) {
	if ( argc < 4 ) return EXIT_FAILURE;

	/* Reading data from HD */
	const char *patterns_filename = argv[1], *patt_size_pch = argv[2], *filename = argv[3];
	int patt_size = atoi(patt_size_pch), text_size = 0, i = 0,
		div = patt_size/2, mod = patt_size%2,
		first_part_size  = div > MAX_WORD_SIZE ? MAX_WORD_SIZE : div,
		second_part_size = div + mod > MAX_WORD_SIZE ? MAX_WORD_SIZE : (div + mod);
	char *text = NULL, *pattern = NULL;
	FILE * file = NULL;
	double times[100];
	t_timemes t_run = {0};
	t_init(t_run);

	read_file_content(&text, filename);
	if (text == NULL) return EXIT_FAILURE;

	text_size = strlen(text);

	pattern = (char*)calloc (patt_size+1, CH_SIZE);
	if (pattern == NULL) { printf("Error: Can't allocate memory for pattern."); free(text); return EXIT_FAILURE; }

	file = fopen (patterns_filename, "rb");
	if (!file) { free(text); free(pattern); return EXIT_FAILURE; }

	while (fread (pattern, CH_SIZE, patt_size, file)==patt_size) {

		indexes = (bool*)calloc(text_size, BOOL_SIZE);

		t_init(t_run);
		t_start(t_run);
		CPM_SO(pattern      , first_part_size , text, text_size, 0      , patt_size); // for first part of pattern
		CPM_SO(pattern + div, second_part_size, text, text_size, div    , patt_size); // for second
		t_stop(t_run);
		times[i++] = t_get_seconds(t_run);

		for(unsigned int l = 0; l < text_size; ++l) if( indexes[l] ) counter++;

		free(indexes);
	}

	qsort(times, i-1, sizeof(double), double_cmp);
	printf("%f\t%lld\t%lld\n", times[i/2], v_count, counter);

	free(text);
	free(pattern);
	fclose(file);

	return EXIT_SUCCESS;
}

