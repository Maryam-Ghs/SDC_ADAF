CXX=	g++
CFLAGS=	-g -Wno-writable-strings

all: svm-train svm-predict svm-scale

svm-predict: svm-predict.o svm.o
	$(CXX) $(CFLAGS) svm-predict.o svm.o -o svm-predict -lm

svm-train: svm-train.o svm.o
	$(CXX) $(CFLAGS) svm-train.o svm.o -o svm-train -lm

svm-scale: svm-scale.o
	$(CXX) $(CFLAGS) svm-scale.o -o svm-scale

svm.o: svm.cpp svm.h
	$(CXX) $(CFLAGS) -c svm.cpp

clean:
	rm -f *~ svm.o svm-train svm-predict svm-scale libsvm.so.$(SHVER)
