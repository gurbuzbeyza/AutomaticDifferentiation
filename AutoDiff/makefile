CC = g++ -std=c++11
CFLAGS  = -g -Wall

default: autodiff.so

autodiff.so:  autodiff.o var.o
	$(CC) $(CFLAGS) -dynamiclib -o autodiff.so autodiff.o var.o

autodiff.o:  autodiff.cpp autodiff.h var.h operation.h
	$(CC) $(CFLAGS) -c autodiff.cpp

var.o:  var.cpp var.h operation.h
	$(CC) $(CFLAGS) -c var.cpp

clean: 
	$(RM) autodiff.dylib *.o *~