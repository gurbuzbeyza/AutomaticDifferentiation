CC = g++ -std=c++11
CFLAGS  = -g -Wall

default: valdi.dylib

valdi.dylib:  valdi.o var.o solve.o
	$(CC) $(CFLAGS) -dynamiclib -o valdi.dylib valdi.o var.o solve.o

valdi.o:  valdi.cpp valdi.h var.h operation.h
	$(CC) $(CFLAGS) -c valdi.cpp

var.o:  var.cpp var.h operation.h solve.hpp
	$(CC) $(CFLAGS) -c var.cpp

solve.o:  solve.cpp solve.hpp
	$(CC) $(CFLAGS) -c solve.cpp

clean: 
	$(RM) valdi.dylib *.o *~