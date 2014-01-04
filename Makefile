all: bin
	g++-4.8 src/test.cpp -std=c++11 -o bin/test

bin:
	mkdir bin

