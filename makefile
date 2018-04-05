CC = g++ -std=c++11
CFLAGS  = -g -Wall

default: valdi

valdi:  valdi.o var.o solve.o
	$(CC) $(CFLAGS) -o valdi valdi.o var.o solve.o

valdi.o:  valdi.cpp var.h operation.h
	$(CC) $(CFLAGS) -c valdi.cpp

var.o:  var.cpp var.h operation.h solve.hpp
	$(CC) $(CFLAGS) -c var.cpp

solve.o:  solve.cpp solve.hpp
	$(CC) $(CFLAGS) -c solve.cpp

clean: 
	$(RM) valdi *.o *~