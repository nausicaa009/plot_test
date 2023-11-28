GCC=g++
CFLAGS= -g -std=c++14 -Wall -Wextra -pedantic

all: main.o reader.o expr.o func.o exception.o
	$(GCC) $(CFLAGS) -o plot main.o reader.o expr.o func.o exception.o

reader.o: reader.cpp reader.h
	$(GCC) $(CFLAGS) -c reader.cpp

expr.o: expr.cpp expr.h
	$(GCC) $(CFLAGS) -c expr.cpp

func.o: func.cpp func.h
	$(GCC) $(CFLAGS) -c func.cpp

exception.o: exception.cpp exception.h
	$(GCC) $(CFLAGS) -c exception.cpp

main.o: main.cpp
	$(GCC) $(CFLAGS) -c main.cpp

test: test.o
	$(GCC) $(CFLAGS) -o test test.o

test.o: test.cpp
	$(GCC) $(CFLAGS) -c test.cpp

clean:
	rm *.o plot

