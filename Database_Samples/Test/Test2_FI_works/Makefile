CC      := g++
CFLAGS  := -O3 -march=native
LIBS    := -lulmblas -lm

BLASDIR=/localdata/Mary/Workspace_2/ADAD_ADAF/BLAS_Samples/ulmBLAS_ADAD
ULMBLAS_INC := $(BLASDIR)/include
ULMBLAS_LIB := $(BLASDIR)/build/lib

TARGET := test_saxpy
SRC    := test_saxpy.cpp

all: $(TARGET)

$(TARGET): $(SRC)
    $(CC) $(CFLAGS) \
        -I$(ULMBLAS_INC) \
        $(SRC) \
        -L$(ULMBLAS_LIB) \
        $(LIBS) \
        -o $@

clean: rm -f $(TARGET)

.PHONY: all clean



BLASDIR=/localdata/Mary/Workspace_2/ADAD_ADAF/BLAS_Samples/ulmBLAS_ADAD
    g++ test_saxpy.cpp \
    -I$BLASDIR \
    -L$BLASDIR \
    -lcblas \
    -lm \
    -o test_saxpy