# Fast and Simple Circular Pattern Matching

**Note:** *more user friendly linux version is placed in [linux folder](https://github.com/rsusik/fscpm/tree/master/linux).*

## About
This source code was written for research purpose [SGD13] and has a minimal error checking.
The code may be not be very readable and comments may not be adequate.
There is no warranty, your use of this code is at your own risk.

Fast and Simple Circular Pattern Matching is a simple solution
of Circular Pattern matching problem described in [SGD13].

There are a couple of algorithms proposed:
* cpm_cf     - counting filter [JTU96, N97] based solution,
* cpm_so     - shift-or [BYG92] based solution (run twice),
* cpm_fso    - Fast Shift-Or [FG09] based solution (run twice),
* cpm_faoso  - Fast Average Optimal Shift-Or [FG09] based solution (run twice).
* cpm_mso    - Multipattern Shift-Or [SGD13] (SO with character classes),
* cpm_mfso   - Multipattern Fast Shift-Or [SGD13] (FSO with character classes),
* cpm_mfaoso - Multipattern Fast Average Optimal Shift-Or [SGD13] (FAOSO with character classes).

The FAOSO algorithm was orginally written by Kimmo Fredriksson.

## Requirements

* Windows OS
* C++ Compiler - MS Visual Studio
* Python 2 (for testing)

## Compilation

All codes were compiled on Windows and was not tested on other OSes, but
should compile on Linux as well (with some modifications).

To compile all variants of algorithm simply run:

```shell
git clone https://github.com/rsusik/fscpm fscpm
cd fscpm
nmake all
```

## Usage

The *nmake all* compilation generates multiple variants of the algorithm.
There are following constants defined:
* U_PARAM - FAOSO (and FSO) parameter (see [FG09])
* K_PARAM - FAOSO parameter (see [FG09], called *q* in original paper)

All of them can be executed from command line as follows:

```shell
ALGORITHM_NAME PATTERNS_FILE PATERN_SIZE TEXT_FILE
```
where:
* PATTERNS_FILE - location of file with patterns
* PATERN_SIZE - pattern size (e.g. 32)
* TEXT_FILE - text file

*For more details please refer to mentioned paper.*

Example:
```shell
cpm_mfaoso_u4_k2.exe "D:/patterns.r100/patterns.dna.200MB.32.bin" 32 "D:/sets/dna.200MB"
```

The files with patterns has all the patterns written one by one with no separator.
Algorithm reads *m* first bytes as the first pattern, then next *m* bytes as the second and so on.

**For testing purpose test_cf_win.py can be used.**

Example:
```shell
python test.py cpm_cf.exe,cpm_so.exe,cpm_mfaoso_u4_k2.exe english.200MB 10 8,16,32,64
```

*Please replace the paths in the test.py*.

## Citing FSCPM
```
@incollection {SGD13,
  author    = {R. Susik and Sz. Grabowski and S. Deorowicz},
  title     = {Fast and Simple Circular Pattern Matching},
  booktitle = {Man-Machine Interactions 3},
  year      = {2014},
  pages     = {537--544},
  publisher = {Springer},
  isbn      = {978-3-319-02309-0}
}
```

## References

[SGD13] R. Susik, Sz. Grabowski, S. Deorowicz.
*Fast and Simple Circular Pattern Matching*,
pages 537--544. Man-Machine Interactions 3, 2013.

[BYG92] R.A. Baeza-Yates, G.H. Gonnet.
*A new approach to text searching*,
pages 74–82. Communications of the ACM 35(10), 1992.

[FG09] K. Fredriksson, S. Grabowski.
*Average-optimal string matching. Journal of Discrete*,
pages 579–594. Algorithms 7(4), 2009.

[JTU96] P. Jokinen, J. Tarhio, and E. Ukkonen.
*A comparison of approximate string matching algorithms*,
pages 1439–1458. Software Practice & Experience, 1996.

[N97] G. Navarro.
*Multiple approximate string matching by counting*,
pages 125–139. In Proc. 4th South American Workshop on String Processing (WSP’97), 1997.


## Authors
* Robert Susik
* Szymon Grabowski
* Sebastian Deorowicz

