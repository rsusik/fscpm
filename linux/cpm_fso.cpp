#ifndef U_PARAM
#define U_PARAM 4
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers.h"

/*
	P - pointer to (sub)pattern (mostly 0 or half of pattern length)
	m - size of (sub)pattern
	T - text
	n - length of text
	offset - offset of subpattern P in real pattern
	patt_size - real size of pattern
*/
template<unsigned int U> void CPM_FSO(char *P, int m, char *T, int n, unsigned int offset, unsigned int patt_size) { 
	word D, B[ASIZE], i, half_patt_size = patt_size/2, pos = 0;
	int l_number = 0, r_number = 0, start = 0;

	if ((unsigned int)m > MAX_WORD_SIZE) { printf("SO: Use pattern size <= word size"); return; }

	// Preprocessing
	for (i = 0; i < ASIZE; i++ )	B[i] = (((word)1 << m) - (word)1) << (MAX_WORD_SIZE - U - m);
	for (i = 0; i < m; i++ ) {
		B[(unsigned char)P[i]] = B[(unsigned char)P[i]] & ~((word)1 << (MAX_WORD_SIZE - U - m + i));
	}

	// Searching
	D = ((word)~0) << (MAX_WORD_SIZE - m - 1); i = 0;
	while ( i < n ) {
		for (unsigned int r = 0; r < U; r++) D = (D << 1) | B[(unsigned char)T[i + r]];
		if ( ~D >> (MAX_WORD_SIZE - U) != 0 ) {
			for( unsigned int j = 0; j < U+half_patt_size; j++ ) {
				if ( ( 1 << ( MAX_WORD_SIZE - 1 ) ) & ( D << j ) ) continue;
				// Verifying
				start = ((int)i + (int)j - m) < 0 ? 0 : (i + j - m);
				if(memcmp(T+start, P, m)==0) {
					if (!offset) {
						l_number = chcpml(P, patt_size, T, n, start-1, -1, 0);
						r_number = chcpmr(P, patt_size, T, n, i +j, m, 0);
						for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
							pos = start-l_number+a;
							indexes[pos] = true;
						}
					} else {
						l_number = chcpml(P - offset, patt_size, T, n, start-1, offset-1, 0);
						r_number = chcpmr(P - offset, patt_size, T, n, i +j, offset+m, 0);
						for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
							pos = start-l_number+a;
							indexes[pos] = true;
						}
					}
				}
			}
		}
		i+=U;
	}
}

/* MAIN */
/* Parameters:
	patters file (e.g. patterns.6.542B.bin)
	pattern size (e.g. 3)
	text (e.g. english.542B)
	U (by default 8)
*/
int main(int argc, char *argv[]) {
	if ( argc < 4 ) return EXIT_FAILURE;

	/* Reading data from HD */
	const char *patterns_filename = argv[1], *patt_size_pch = argv[2], *filename = argv[3];
	
	int patt_size = atoi(patt_size_pch), text_size = 0, i = 0,
		div = patt_size/2, mod = patt_size%2,
		first_part_size  = (div + U_PARAM)       > MAX_WORD_SIZE ? (MAX_WORD_SIZE - U_PARAM) : (div), /* check if pattern is too large */
		second_part_size = (div + mod + U_PARAM) > MAX_WORD_SIZE ? (MAX_WORD_SIZE - U_PARAM) : (div);
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

		t_init(t_run);
		t_start(t_run);
		CPM_FSO<U_PARAM>(pattern      , first_part_size      , text, text_size, 0  , patt_size); // for first part of pattern
		CPM_FSO<U_PARAM>(pattern + div, second_part_size     , text, text_size, div, patt_size); // for second
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

