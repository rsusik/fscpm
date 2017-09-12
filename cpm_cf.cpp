#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "headers.h"


void CPM_CF (const char *P, const int m, const char *y, const int n, const int k, char **perms) {
	/* Preprocessing */
	unsigned int pos = 0;
	const static int ASIZE = 256;
	long  count = 0, j = 0;
	unsigned char *A = (unsigned char*)malloc(CH_SIZE*256);
	if (A==NULL) { printf("Error: CMP_CountFilter: Can't allocate memory for variable A."); return; }
	for ( int i = 0; i < ASIZE; ++i) A[ i ] = 0;
	for ( int i = 0; i < m; ++i) A[ (unsigned char)P[i] ]++;
	count = -( m - k );

	/* Searching */
	for ( j = 0; j < m; j++ ) /* Fill the initial window */
		if ( A[ (unsigned char)y[j] ]-- > 0 ) count++;

	while (j <= n) { /* Move the window */
		if ( count >= 0 ) {
			++v_count;
			/* Verify */
			for( int i = 0; i < m; ++i) {
				if(j<n-m && memcmp(perms[i], y+j-m, m)==0) {
					pos = j-m, m, y+j-m;
					indexes[pos] = true;
					break;
				}
			}
		}
		if ( ++A[ (unsigned char)y[j - m] ] > 0 ) count--;
		if ( A[ (unsigned char)y[j++] ]-- > 0 ) count++;
	}
	free(A);
}

/* MAIN */

int main(int argc, char *argv[]) {
	if ( argc < 4 ) return EXIT_FAILURE;

	/* Reading data from HD */
	const char *patterns_filename = argv[1], *patt_size_pch = argv[2], *filename = argv[3];
	int patt_size = atoi(patt_size_pch), text_size = 0, div = 0, mod = 0, i = 0;
	char *text = NULL, *pattern = NULL, **perms = NULL;

	FILE * file = NULL;

	read_file_content(&text, filename);
	if (text == NULL) return EXIT_FAILURE;

	text_size = strlen(text);

	pattern = (char*)calloc (patt_size+1, CH_SIZE);
	if (pattern == NULL) { printf("Error: Can't allocate memory for pattern."); free(text); return EXIT_FAILURE; }

	file = fopen (patterns_filename, "rb");
	if (!file) { printf("Error: Can't open patterns file."); free(text); free(pattern); return EXIT_FAILURE; }

	while (fread (pattern, CH_SIZE, patt_size, file)==patt_size) {
		indexes = (bool*)calloc(text_size, BOOL_SIZE);

		// fill the permutations of pattern 
		perms = (char**)malloc(PCH_SIZE*patt_size);
		if(perms == NULL) { printf("Error. Cannot allocate memory!\nPress any key..."); return 1; }
		for ( int i = 0; i < patt_size; i++ ) { 
			perms[i] = (char*)calloc(patt_size+1, CH_SIZE); 
			if(perms[i] == NULL) { printf("Error. Cannot allocate memory!\nPress any key..."); return 1; }
		}
		for ( int i = 0; i < patt_size; i++ ) {
			strncpy(perms[i]+i, pattern, patt_size-i);
			strncpy(perms[i], pattern+(patt_size-i), i);
		}

		QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&tick1);
		start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;

		CPM_CF(pattern, patt_size, text, text_size, 0, perms);

		QueryPerformanceCounter(&tick2);
		end = double(tick2.QuadPart)/ticksPerSecond.QuadPart;
		diff = end - start;
		times[i++] = diff;

		for(unsigned int l = 0; l < text_size; ++l) if( indexes[l] ) counter++;

		free(indexes);
		for ( int i = 0; i < patt_size; i++ ) free(perms[i]); 
		free(perms);
		perms = NULL;
	}

	qsort(times, i-1, sizeof(double), double_cmp);
	printf("%f\t%lld\t%lld\n", times[i/2], v_count, counter);

	free(text);
	free(pattern);
	fclose(file);

	return EXIT_SUCCESS;
}