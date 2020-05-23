SHELL := bash
CXX = g++
CWD = $(shell pwd)
CFLAGS = --std=c++17 \
	-I /usr/local/include

all:
	$(CXX) $(CFLAGS) -w -o interactiveTest main.cpp String.hpp Identifier.hpp DecimalString.hpp String.cpp Identifier.cpp DecimalString.cpp

docker:
	docker build --tag gtest .
	docker run gtest

test:
	$(CXX) -c $(CFLAGS) test.cpp
	$(CXX) -c $(CFLAGS) String.cpp Identifier.cpp DecimalString.cpp
	$(CXX) -w -o test test.o String.o Identifier.o DecimalString.o -L /usr/local/lib -l gtest -l pthread

clean:
	rm -f interactiveTest test *.o

.PHONY: all test docker clean
