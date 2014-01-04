all: bin
	g++ src/test.cpp -std=c++11 -o bin/test

bin:
	mkdir bin

