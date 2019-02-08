all: a.out
CC=g++
CPPFLAGS=-O3 -std=c++11 -Wall -Wextra

a.out: test.cpp stopwatch.hpp
	$(CC) $(CPPFLAGS) $< -o $@


clean:
	rm -f a.out
