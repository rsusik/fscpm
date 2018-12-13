# Fast and Simple Circular Pattern Matching (linux)

## About
This is linux version of [fscpm](https://github.com/rsusik/fscpm).
In addition the testing script is improved and updated.

## Requirements

* Windows OS
* C++ Compiler - MS Visual Studio
* Python 3 (for [testing](#testing))
* [Docker](#docker) (optional)

## Compilation

To compile all variants of algorithm simply run:

```shell
git clone https://github.com/rsusik/fscpm fscpm
cd fscpm/linux
make all
```

## Usage

For testing please use `test.py` script. The syntax is following:
```
usage: test.py [-h] [-a A] [-c C] [-m M]

Circullar patter matching script.

optional arguments:
  -h, --help           show this help message and exit
  -a A, --algorithm A  algorithm[s] to be tested
  -c C, --corpus C     corpus
  -m M, --length M     pattern length[s] (e.g. 8,16,32)

Example: python3 test.py -a cpm_faoso_u8_k1,cpm_faoso_u4_k2 -c english.10MB -m
8,32
```

## Docker

The simplest way you can test the algorithm is by using docker. All you need to do is to:

* Clone the git repository:
```shell
git clone https://github.com/rsusik/fscpm fscpm
cd fscpm/linux
```

* Build the image:
```shell
docker build -t fscpm .
```

* Run container:
```shell
docker run --rm fscpm
```

* Additionally you may add parameters:
```shell
docker run --rm fscpm -a cpm_faoso_u8_k1,cpm_faoso_u4_k2 -c english.100MB -m 32
```


## Authors
* Robert Susik
* Szymon Grabowski
* Sebastian Deorowicz

