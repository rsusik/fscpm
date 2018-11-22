#ifndef HEADERS_H
#define HEADERS_H

/* Compile mode detection */
#if defined(_WIN32) || defined(_WIN64)
	#define WINDOWS
	#if defined(_WIN64)
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

#if defined(__GNUC__)
	#define UNIX
	#if defined(__x86_64__) || defined(__ppc64__)
		#define ENV64BIT
	#else
		#define ENV32BIT
	#endif
#endif

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <math.h>
#include <limits>
#include <iostream>
#include <algorithm> /* std:sort */

#ifdef WINDOWS
#ifndef NOMINMAX
#define NOMINMAX /* to disable windows.h min,max */
#endif
#include <windows.h>
#include <stdint.h> /* int64_t, etc. for Visual Studio */
#include <cstdint>
#endif

/* Print results flag */
#define PRINT_RESULTSS

/* Typedefs */
#ifdef ENV64BIT
	typedef		uint64_t word;
	typedef		long double ldouble;
#endif
#ifdef ENV32BIT
	typedef		uint32_t word;
	typedef		double ldouble;
#endif

typedef unsigned char uchar;
typedef unsigned char byte;

typedef unsigned int encoded_text_type;

/* Sizes of types */
const size_t CH_SIZE = sizeof(char);
const size_t PCH_SIZE = sizeof(char*);
const size_t PINT_SIZE = sizeof(unsigned int*);
const size_t BOOL_SIZE = sizeof(bool);
const size_t UCH_SIZE = sizeof(uchar);
const size_t BYTE_SIZE = sizeof(byte);

/* Other variables */
long long counter = 0;
bool *indexes = 0;
long long v_count = 0;

/* Time measurement stuff */
#ifdef UNIX

typedef struct {
	timespec start;
	timespec stop;
	timespec sum;
} t_timemes;
#define t_init(t) t.sum.tv_nsec = 0; t.sum.tv_sec = 0
#define t_start(t) clock_gettime(CLOCK_MONOTONIC, &(t.start))
#define t_stop(t) clock_gettime(CLOCK_MONOTONIC, &(t.stop)); \
t.sum.tv_sec += t.stop.tv_sec - t.start.tv_sec; \
t.sum.tv_nsec += t.stop.tv_nsec - t.start.tv_nsec
#define t_get_seconds(t) (double)t.sum.tv_sec + (double)t.sum.tv_nsec / (double)1000000000

#else

typedef struct {
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER tick;
	double start;   // A point in time
	double stop;
	double sum;
} t_timemes;
#define t_init(t) t.sum = 0; QueryPerformanceFrequency(&(t.ticksPerSecond))
#define t_start(t) QueryPerformanceCounter(&(t.tick)); t.start = double(t.tick.QuadPart)/t.ticksPerSecond.QuadPart
#define t_stop(t) QueryPerformanceCounter(&(t.tick)); \
t.stop = double(t.tick.QuadPart)/t.ticksPerSecond.QuadPart; \
t.sum = t.stop - t.start
#define t_get_seconds(t) t.sum

#endif


/*const ldouble log2 = log( (ldouble)2 );
static inline word ilog2( ldouble n ) {
	return (word) ( log( n ) / log2 );  
}*/
#define log2 0.69314718055994529
#define ilog2(n) (word) ( log( n ) / log2 )
// log cache (filled in main() function)
#define log2cache 70000
word log2v[log2cache];


const unsigned int MAX_WORD_SIZE = sizeof(word)*8;//, U = 16;

#define ASIZE 256

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