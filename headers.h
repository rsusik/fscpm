#ifndef HEADERS_H
#define HEADERS_H

#include <cmath>

/* For time meassurement */
#include <windows.h>

/* Print results flag */
#define PRINT_RESULTS

/* Compile mode detection */
#if _WIN32 || _WIN64
  #if _WIN64
    #define ENV64BIT
  #else
    #define ENV32BIT
  #endif
#endif

/* Typedefs */
typedef 	unsigned char	uchar;
#ifdef ENV64BIT
	typedef		long long int word;
	typedef		long double ldouble;
#endif
#ifdef ENV32BIT
	typedef		unsigned int word;
	typedef		double ldouble;
#endif

/* Constants */
const unsigned int ASIZE = 256, MAX_WORD_SIZE = sizeof(word)*8;//, U = 16;

/* Sizes of types */
const size_t CH_SIZE = sizeof(char);
const size_t PCH_SIZE = sizeof(char*);
const size_t PINT_SIZE = sizeof(unsigned int*);
const size_t BOOL_SIZE = sizeof(bool);
const size_t UCH_SIZE = sizeof(uchar);

/* Variables for time measurement */
double start = 0, end = 0, diff = 0;
double times[101];
LARGE_INTEGER ticksPerSecond;
LARGE_INTEGER tick1;   // A point in time
LARGE_INTEGER tick2;   // A point in time

LARGE_INTEGER time1;   // For converting tick into real time
LARGE_INTEGER time2;   // For converting tick into real time

/* Other variables */
long long counter = 0;
bool *indexes = 0;
long long v_count = 0;

/* FUNCTIONS */

static inline word ilog2( ldouble n ) {
	return (word) ( log( n ) / log( (ldouble)2 ) );  
}

#define	ILOG_2( x ) ilog2( x )

static int	* build_verify_table( int m, int k, int r, int l )
{
	int	mk;
	int	h;
	int	mpk = m / k;
	int	c, f, * t;

	t = (int*)malloc( MAX_WORD_SIZE * sizeof( int ));

	for( f = 0; f < r; f++ ) {
		c = ( 1 - f - mpk ) * k;
		mk = ( mpk * l - 1 + f * l );

		for( h = 0; h < k; h++, c-- ) {
			t[ mk ] = c; 
			mk += mpk * l + r - 1;
		}
	}

	return t;
}

int double_cmp(const void *a, const void *b) {
	return *(double*)a - *(double*)b;
}

template <class T> void read_file_content( T**buffer, const char* filename ) {
	long length;
	FILE * file = fopen (filename, "rb");
	if (file) {
		fseek (file, 0, SEEK_END);
		length = ftell (file);
		fseek (file, 0, SEEK_SET);
		*buffer = (T*)malloc (length+1);
		if (*buffer==NULL) return;
		fread (*buffer, 1, length, file);
		*(*buffer+length) = '\0';
		fclose (file);
	}
}

template <class T> void printf_binnary(T var) {
	unsigned int size = sizeof(T)*8;
	
	for ( int i = size - 1; i >= 0; i--) {
		printf("%d", var >> i & 1);
	}
}

template <class T> char * deb_printf_binnary(T var) {
	unsigned int size = sizeof(T)*8;
	char *str = new char[size];
	char *tmp = str;
	for ( int i = size - 1; i >= 0; i--) {
		sprintf(tmp++, "%d", var >> i & 1);
	}
	return str;
}

/*
Checks how many chars on the left are matched 
Parameters:
	P		- pattern pointer
	p_size	- size of the pattern
	T		- text pointer
	t_size	- size of the text
	t_index	- index (position) in text where the matching will begin
	p_index	- index (position) in pattern where the matching will begin
	number	- number of founded chars (should be zero)
*/
unsigned int chcpml( const char *P, unsigned int p_size, const char *T, unsigned int t_size, int t_index, int p_index, unsigned int number ) {
	if ( p_index < 0) p_index = p_size-1;
	if ( t_index < 0) return number;
	if ( P[p_index--] != T[t_index--] ) return number;
	return chcpml( P, p_size, T, t_size, t_index, p_index, ++number );
}

/* 
Checks how many chars on the right are matched
Parameters - look at the chcpml function description
*/
unsigned int chcpmr( const char *P, unsigned int p_size, const char *T, unsigned int t_size, int t_index, int p_index, unsigned int number ) {
	if ( p_index > (int)p_size-1) p_index = 0;
	if ( t_index > (int)t_size-1) return number;
	if ( P[p_index++] != T[t_index++] ) return number;
	return chcpmr( P, p_size, T, t_size, t_index, p_index, ++number );
}

#endif