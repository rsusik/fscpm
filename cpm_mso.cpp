#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "headers.h"

void CPM_MSO(char *P, int m, char *T, int n, unsigned int patt_size) {
	word D, mm, i, B[ASIZE], 
		half_m = m/2, mod_m = m%2,
		half_patt_size = patt_size/2, 
		pos = 0;
	if (m > MAX_WORD_SIZE) { printf("SO: Use pattern size <= word size"); return; }
	int l_number = 0, r_number = 0;
	char * str = NULL;
	
	/* Preprocessing */
	for (i = 0; i < ASIZE; ++i) B[i] = (word)~0;
	for (i=0; i < m; ++i) {
		B[(unsigned char)P[i]] &= ~((word)1<<i);
		B[(unsigned char)P[i+half_patt_size]] &= ~((word)1<<i);
	}
	
	D = (word)~0; mm = (word)1 << (i-1); i = 0;

	int start = 0;

	/* Searching */
	while (i < n) {
		D = ( D << 1 ) | B[(unsigned char)T[i]];
		if ( (D & mm) != mm ) {
			/* Verifying */
			++v_count;
			start = i-m +1 < 0 ? 0 : i-m+1;
			if(memcmp(T+start, P+half_patt_size, m)==0) {
				l_number = chcpml(P, patt_size, T, n, i - m, half_patt_size-1, 0);
				r_number = chcpmr(P, patt_size, T, n, i + 1 , half_patt_size+m, 0);
				for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
					pos = start-l_number+a;
					indexes[pos] = true;
				}
			} else 
			if(memcmp(T+start, P, m)==0) {
				l_number = chcpml(P, patt_size, T, n, start-1, -1, 0);
				r_number = chcpmr(P, patt_size, T, n, i +1, m, 0);
				for (int a = 0; a <= l_number + r_number + m - (int)patt_size;  a++) {
					pos = start-l_number+a;
					indexes[pos] = true;
				}
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
		m_size  = (div + mod) > MAX_WORD_SIZE ? (MAX_WORD_SIZE - mod) : div; /* check if pattern is too large */
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

		CPM_MSO(pattern, m_size, text, text_size, patt_size);

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

