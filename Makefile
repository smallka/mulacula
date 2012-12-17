CC = g++
CPPFLAGS = -g -DSINGLE_RUN

all:	formula.o
	$(CC) main.cpp formula.o -o main

lint:
	python ../cpplint.py --filter=-whitespace,-whitespace/braces,-build/header_guard,-legal/copyright formula.*

clean:
	rm -rf *.o main

