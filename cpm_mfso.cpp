#ifndef U_PARAM
#define U_PARAM 4
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdint.h>
#include "headers.h"

template<unsigned int U> void CPM_MFSO(char *P, int m, char *T, int n, unsigned int patt_size) {
	word D, B[ASIZE], i, 
	half_m = m/2, mod_m = m%2,
	half_patt_size = patt_size/2, mod_patt_size = patt_size%2, 
	pos = 0;
	int l_number = 0, r_number = 0, start = 0;
	char * str = NULL;

	if (m > MAX_WORD_SIZE) { printf("SO: Use pattern size <= word size. m=%d", m); return; }

	/* Preprocessing */
	for (i = 0; i < ASIZE; i++ )	B[i] = (((word)1 << m) - (word)1) << (MAX_WORD_SIZE - U - m);
	for (i = 0; i < m; i++ ) {
		B[(unsigned char)P[i]]		&= ~((word)1 << (MAX_WORD_SIZE - U - m + i));
		B[(unsigned char)P[i+half_patt_size]]	&= ~((word)1 << (MAX_WORD_SIZE - U - m + i));
	}

	/* Searching */ 
	D = (word)~0 << (MAX_WORD_SIZE - half_patt_size - 1); 
	i = (word)0;

	while ( i < n ) {
		for (int r = 0; r < U; r++) D = (D << 1) | B[(unsigned char)T[i + r]];
		if ( ~D >> (MAX_WORD_SIZE - U) != 0 ) {
			/* Verifying */
			++v_count;
			for( unsigned int j = 0; j < U+half_patt_size; j++ ) {
				if ( ( 1 << ( MAX_WORD_SIZE - 1 ) ) & ( D << j ) ) continue;

				start = ((int)i + (int)j - m) < 0 ? 0 : (i + j - m);
				if(memcmp(T + start, P+half_patt_size, m)==0) {
					l_number = chcpml(P, patt_size, T, n, start - 1, half_patt_size-1, 0);
					r_number = chcpmr(P, patt_size, T, n, i + j, half_patt_size + m, 0);
					for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
						pos = start - l_number + a;
						indexes[pos] = true;
					}
				} else if(memcmp(T + start, P, m)==0 ) {
					l_number = chcpml(P, patt_size, T, n, start - 1, -1, 0);
					r_number = chcpmr(P, patt_size, T, n, i + j, m, 0);
					for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
						pos = start - l_number + a;
						indexes[pos] = true;
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
*/
int main(int argc, char *argv[]) {
	if ( argc < 4 ) return EXIT_FAILURE;

	const char *patterns_filename = argv[1], *patt_size_pch = argv[2], *filename = argv[3];

	int patt_size = atoi(patt_size_pch), text_size = 0, i = 0;

	int	div = patt_size/2, mod = patt_size%2,
		m_size  = (div + mod + U_PARAM) > MAX_WORD_SIZE ? (MAX_WORD_SIZE - U_PARAM - mod) : div; /* check if pattern is too large */
	if(m_size<=1) { printf("Error: Something went wrong, msize<=1."); return EXIT_FAILURE; }

	char *text = NULL, *pattern = NULL;
	FILE * file = NULL;

	read_file_content(&text, filename);
	if (text == NULL) return EXIT_FAILURE;

	text_size = strlen(text);

	pattern = (char*)calloc (patt_size+1, CH_SIZE);
	if (pattern == NULL) { printf("Error: Can't allocate memory for pattern."); free(text); return EXIT_FAILURE; }

	file = fopen (patterns_filename, "rb");
	if (!file) { free(text); free(pattern); return EXIT_FAILURE; }

	while (fread (pattern, CH_SIZE, patt_size, file)==patt_size) {

		indexes = (bool*)calloc(text_size, BOOL_SIZE);

		QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&tick1);
		start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;

		CPM_MFSO<U_PARAM>(pattern, m_size, text, text_size, patt_size);

		QueryPerformanceCounter(&tick2);
		end = double(tick2.QuadPart)/ticksPerSecond.QuadPart;
		diff = end - start;
		times[i++] = diff;
		
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

