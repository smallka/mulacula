CC = g++
CPPFLAGS = -g -O2

all:	clean formula.o
	$(CC) main.cpp formula.o -lrt -o main

lint:
	python ../cpplint.py --filter=-whitespace,-whitespace/braces,-build/header_guard,-legal/copyright formula.*

clean:
	rm -rf *.o main *.pyc

