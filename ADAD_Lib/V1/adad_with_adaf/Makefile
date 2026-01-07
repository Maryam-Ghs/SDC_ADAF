DEBUG=	0
CXX=	g++

ifeq ($(DEBUG),1)
  CFLAGS= -g -O0 -pedantic -Wall
  CXXFLAGS= -g -O0 -pedantic -Wall
else
  CFLAGS= -O3
  CXXFLAGS= -O3
endif

HDR=	adad.h adaf.h
SRC=	adad.cpp adaf.cpp fault.cpp 
OBJ=	adad.o adaf.o fault.o 

all:	sorter linreg

sorter:	main.o sorter.o $(OBJ) $(HDR) Makefile
	$(CXX) $(CXXFLAGS) -o $@ main.o sorter.o $(OBJ) -lm

linreg:	main.o linreg.o $(OBJ) $(HDR) Makefile
	$(CXX) $(CXXFLAGS) -o $@ main.o linreg.o $(OBJ) -lm

$(OBJ): $(HDR) Makefile

.PHONY:	tags
tags:
	etags *.c *.h

clean:
	rm -f sorter linreg *.o

