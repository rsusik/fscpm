#ifndef U_PARAM
#define U_PARAM 4
#endif
#ifndef K_PARAM
#define K_PARAM 2
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits>
#include <amp.h>
#include <amp_math.h>
#include <iostream>
#include <windows.h>
#include "headers.h"

static int verify_opt( uchar * t, uchar * p, int m, word d, word mm, int pos, int * vt, int myn, int offset, int patt_size )
{
	int	matches = 0;
	int	s, c, l;
	int l_number = 0, r_number = 0;
	int my_pos = 0;
	bool ok = false;
	int half_patt_size = patt_size / 2;

	v_count++;

	d = ( d & mm ) ^ mm;
	
	while( d ) {
		s = ilog2( d );
		c = vt[ s ] + pos;
		l = 0;
		ok = false;
		for( l = 0; l < m; l++ ) {
			if( p[ l ] != t[ c + l ] ) break;
		}
		if( l == m ) { 
			ok = true; 
		} else {
			for( l = 0; l < m; l++ ) {
				if( p[ l + half_patt_size ] != t[ c + l ] ) break;
			}
			if( l == m ) ok = true;
		}


		if( ok ) {
				if(memcmp(t+c, p, m)==0) {
						l_number = chcpml((const char*)p, patt_size, (const char*)t, myn, c-1, -1, 0);
						r_number = chcpmr((const char*)p, patt_size, (const char*)t, myn, c +m, m, 0);
						
						for (int a = 0; a <= l_number + r_number + (int)m - (int)patt_size;  a++) {
							my_pos = c-l_number+a;
							indexes[my_pos] = true;
						}
					
				}

				if(memcmp(t+c, p+half_patt_size, m)==0) {
						l_number = chcpml((const char*)p, patt_size, (const char*)t, myn, c-1, half_patt_size-1, 0);
						r_number = chcpmr((const char*)p, patt_size, (const char*)t, myn, c +m, half_patt_size+m, 0);
						
						for (int a = 0; a <= l_number + r_number + (int)m - (int)patt_size;  a++) {
							my_pos = c-l_number+a;
							indexes[my_pos] = true;
						}
				}
				
		}
		d &= ~(( word )1 << s );
	}
	
	return matches;
}


template<unsigned int U, unsigned int k> int CPM_MFAOSO( uchar * p, int m, uchar * t, int n, int offset, int patt_size ) {
	word		b[ 256 ];
	word		d;
	word		mm;
	int		i, j, h, r, matches = 0, foo = U * k, *vt, half_patt_size = patt_size/2;
	uchar		* tt;

	if( m > MAX_WORD_SIZE ) return 0;

	for( i = 0; i < 256; i++ ) b[ i ] = ~( word )0; 

	for( j = h = 0, mm = ( word )0; j < k; j++ ) {
		for( i = 0; i < m/k; i++ ) {
			b[ p[ i * k + j ]] &= ~(( word )1 << ( h ));
			b[ p[ i * k + j + half_patt_size ]] &= ~(( word )1 << ( h ));
			++h;
		}
		for( r = 0; r < U; r++, h++ )
			mm = mm | (( word )1 << ( h - 1 )); 
		--h;
	}

	if( h > MAX_WORD_SIZE ) { printf("h=%d > %d\n", h, ( int )MAX_WORD_SIZE ); exit(1); }

	for( i = 0; i < 256; i++ ) b[ i ] &= ~( mm & ( mm << 1 ));

	vt = build_verify_table( m, k, U, 1 );

	d = ~mm; i = n; tt = t; 

	do {	switch( 0 ) {
		case 0:	d = ( d << 1 ) | b[ t[ 0 * k ]]; if( U == 1 ) break; // should be replaced with template
			d = ( d << 1 ) | b[ t[ 1 * k ]]; if( U == 2 ) break;
			d = ( d << 1 ) | b[ t[ 2 * k ]]; if( U == 3 ) break;
			d = ( d << 1 ) | b[ t[ 3 * k ]]; if( U == 4 ) break;
			d = ( d << 1 ) | b[ t[ 4 * k ]]; if( U == 5 ) break;
			d = ( d << 1 ) | b[ t[ 5 * k ]]; if( U == 6 ) break;
			d = ( d << 1 ) | b[ t[ 6 * k ]]; if( U == 7 ) break;
			d = ( d << 1 ) | b[ t[ 7 * k ]]; if( U == 8 ) break;
			d = ( d << 1 ) | b[ t[ 8  * k ]]; if( U == 9  ) break;
			d = ( d << 1 ) | b[ t[ 9  * k ]]; if( U == 10 ) break;
			d = ( d << 1 ) | b[ t[ 10 * k ]]; if( U == 11 ) break;
			d = ( d << 1 ) | b[ t[ 11 * k ]]; if( U == 12 ) break;
			d = ( d << 1 ) | b[ t[ 12 * k ]]; if( U == 13 ) break;
			d = ( d << 1 ) | b[ t[ 13 * k ]]; if( U == 14 ) break;
			d = ( d << 1 ) | b[ t[ 14 * k ]]; if( U == 15 ) break;
			d = ( d << 1 ) | b[ t[ 15 * k ]]; if( U == 16 ) break;
			fprintf( stderr, "Too many unrolls, exiting...\n");
			exit( 1 );
		}

		if(( d & mm ) != mm ) matches += verify_opt( tt, p, m, d, mm, t - tt - k + foo, vt, n, offset, patt_size );
		d &= ~mm;

		t += foo;

	} while(( i -= U * k ) > 0 );

	return matches;
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

	int patt_size = atoi(patt_size_pch), text_size = 0, 
		div = patt_size/2, mod = 0, i = 0,
		max_m = ( MAX_WORD_SIZE / K_PARAM + 1 - U_PARAM ) * K_PARAM - 2,
		j, h, m = div,
		first_part_size  = max_m       < div ? max_m : div; /* check if pattern is too large */
	
	uchar *text = NULL, *pattern = NULL;
	FILE * file = NULL;

	if(first_part_size <= K_PARAM) { printf("Error: (m/2 and max_m)>=K_PARAM, m=%d, max_m=%d, K_PARAM=%d\n", patt_size, max_m, K_PARAM); return EXIT_FAILURE; }
	
	read_file_content(&text, filename);
	if (text == NULL) return EXIT_FAILURE;
	
	file = fopen (patterns_filename, "rb");
	if (!file) { printf("Error: Can't open file %s.\n", patterns_filename); free(text); return EXIT_FAILURE; }

	pattern = (uchar*)calloc (patt_size+1, sizeof(uchar));
	if (pattern == NULL) { printf("Error: Can't allocate memory for pattern (%d bytes).\n", patt_size); free(text); fclose(file); return EXIT_FAILURE; }

	text_size = strlen((char*)text);

	while (fread (pattern, CH_SIZE, patt_size, file)==patt_size) {

		indexes = (bool*)calloc(text_size, BOOL_SIZE);
		
		QueryPerformanceFrequency(&ticksPerSecond);
		QueryPerformanceCounter(&tick1);
		start = double(tick1.QuadPart)/ticksPerSecond.QuadPart;
		
		CPM_MFAOSO<U_PARAM, K_PARAM>(pattern      , first_part_size      , text, text_size, 0  , patt_size); // for first part of pattern
		
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

