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

## Testing

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

1. build the docker image or pull from repository
2. and run the docker container

* Pull or build the image:

	* Pull from repository steps:
	```
	docker pull rsusik/fscpm
	docker tag docker.io/rsusik/fscpm fscpm
	```

	* Build steps:
		* Clone the git repository:
		```shell
		git clone https://github.com/rsusik/fscpm fscpm
		cd fscpm
		```
		* Build the image:
		```shell
		docker build -t fscpm .
		```

* Run test with default parameters:
```
docker run fscpm
```

*This will execute test with default parameters and output the results.*

* Additionally you may provide all the parameters mentioned in section [Testing](#testing) as follows:
```
docker run fscpm -a cpm_faoso_u8_k1,cpm_faoso_u4_k2 -c english.100MB -m 32
```

Above command supports only a mentioned Pizza&Chilli corpuses but you may provide your own 
datasets using -v parameter. Assuming you want to execute test for dataset `mydataset.5MB`
that is located in `/home/ok/mysets` you have to execute following command:
```
docker run -v /home/ok/mysets:/app/sets fscpm -a fscpm -c mydataset.5MB
```

*(for citation see root dir of this repository)*
