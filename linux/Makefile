cpm_cf: cpm_cf.cpp
	g++ -std=c++11 -Wno-unused-result -Wno-aggressive-loop-optimizations -O3 -o cpm_cf cpm_cf.cpp 

cpm_so: cpm_so.cpp headers.h
	g++ -std=c++11 -Wno-unused-result -Wno-aggressive-loop-optimizations -O3 -o cpm_so cpm_so.cpp 

cpm_mso: cpm_mso.cpp headers.h
	g++ -std=c++11 -Wno-unused-result -Wno-aggressive-loop-optimizations -O3 -o cpm_mso cpm_mso.cpp 

cpm_fso_u4: cpm_fso.cpp headers.h
	g++ -D U_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_fso_u4 cpm_fso.cpp 

cpm_fso_u8: cpm_fso.cpp headers.h
	g++ -D U_PARAM=8 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_fso_u8 cpm_fso.cpp 

cpm_mfso_u4: cpm_mfso.cpp headers.h
	g++ -D U_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfso_u4 cpm_mfso.cpp 

cpm_mfso_u8: cpm_mfso.cpp headers.h
	g++ -D U_PARAM=8 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfso_u8 cpm_mfso.cpp 

cpm_faoso_u8_k4: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u8_k4 cpm_faoso.cpp 

cpm_faoso_u8_k2: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=2 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u8_k2 cpm_faoso.cpp 

cpm_faoso_u8_k1: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=1 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u8_k1 cpm_faoso.cpp 

cpm_faoso_u4_k4: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u4_k4 cpm_faoso.cpp 

cpm_faoso_u4_k2: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=2 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u4_k2 cpm_faoso.cpp 

cpm_faoso_u4_k1: cpm_faoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=1 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_faoso_u4_k1 cpm_faoso.cpp 

cpm_mfaoso_u8_k4: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u8_k4 cpm_mfaoso.cpp 

cpm_mfaoso_u8_k2: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=2 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u8_k2 cpm_mfaoso.cpp 

cpm_mfaoso_u8_k1: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=8 -D K_PARAM=1 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u8_k1 cpm_mfaoso.cpp 

cpm_mfaoso_u4_k4: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=4 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u4_k4 cpm_mfaoso.cpp 

cpm_mfaoso_u4_k2: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=2 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u4_k2 cpm_mfaoso.cpp 

cpm_mfaoso_u4_k1: cpm_mfaoso.cpp headers.h
	g++ -D U_PARAM=4 -D K_PARAM=1 -std=c++11 -Wno-unused-result -Wno-shift-count-overflow -Wno-aggressive-loop-optimizations -O3 -o cpm_mfaoso_u4_k1 cpm_mfaoso.cpp 

all: cpm_mfaoso_u8_k4 cpm_mfaoso_u8_k2 cpm_mfaoso_u8_k1 cpm_mfaoso_u4_k4 cpm_mfaoso_u4_k2 cpm_mfaoso_u4_k1 cpm_faoso_u8_k4 cpm_faoso_u8_k2 cpm_faoso_u8_k1 cpm_faoso_u4_k4 cpm_faoso_u4_k2 cpm_faoso_u4_k1 cpm_mfso_u4 cpm_mfso_u8 cpm_fso_u4 cpm_fso_u8 cpm_mso cpm_so cpm_cf

clean:
	rm -f cpm_mfaoso_u8_k4 cpm_mfaoso_u8_k2 cpm_mfaoso_u8_k1 cpm_mfaoso_u4_k4 cpm_mfaoso_u4_k2 cpm_mfaoso_u4_k1 cpm_faoso_u8_k4 cpm_faoso_u8_k2 cpm_faoso_u8_k1 cpm_faoso_u4_k4 cpm_faoso_u4_k2 cpm_faoso_u4_k1 cpm_mfso_u4 cpm_mfso_u8 cpm_fso_u4 cpm_fso_u8 cpm_mso cpm_so cpm_cf

