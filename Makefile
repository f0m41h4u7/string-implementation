SHELL := bash
CXX = g++
CWD = $(shell pwd)
CFLAGS = --std=c++17 \
	-I /usr/local/include

dockerTest:
	docker build --tag gtest .
	docker run gtest

test:
	$(CXX) -c $(CFLAGS) test.cpp
	$(CXX) -c $(CFLAGS) str.cpp
	$(CXX) -w -o test test.o str.o -L /usr/local/lib -l gtest -l pthread

clean:
	rm -f run test *.o

.PHONY: all test dockerTest clean
