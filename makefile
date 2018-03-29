CC = g++ -std=c++11
CFLAGS  = -g -Wall

default: valdi

valdi:  valdi.o node.o solve.o
	$(CC) $(CFLAGS) -o valdi valdi.o node.o solve.o

valdi.o:  valdi.cpp node.h operation.h
	$(CC) $(CFLAGS) -c valdi.cpp

node.o:  node.cpp node.h operation.h solve.hpp
	$(CC) $(CFLAGS) -c node.cpp

solve.o:  solve.cpp solve.hpp
	$(CC) $(CFLAGS) -c solve.cpp

clean: 
	$(RM) valdi *.o *~