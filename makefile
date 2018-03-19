CC = g++ -std=c++11
CFLAGS  = -g -Wall

default: valdi

valdi:  valdi.o node.o
	$(CC) $(CFLAGS) -o valdi valdi.o node.o

valdi.o:  valdi.cpp node.h operation.h
	$(CC) $(CFLAGS) -c valdi.cpp

node.o:  node.cpp node.h operation.h
	$(CC) $(CFLAGS) -c node.cpp

clean: 
	$(RM) valdi *.o *~