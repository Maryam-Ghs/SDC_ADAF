IGNR = -Wno-implicit-int -Wno-implicit-function-declaration -Wno-format -Wno-deprecated-non-prototype -Wno-return-type

OBJS = mulGlobal.o mulSetup.o mulMats.o mulDo.o mulDisplay.o mulMulti.o \
mulLocal.o direct.o calcp.o fastcap.o blkDirect.o uglyalloc.o \
patran.o quickif.o electric.o input.o psMatDisplay.o capsolve.o savemat_mod.o \
zbufInOut.o zbuf2fastcap.o zbufProj.o zbufSort.o

SRCS = mulGlobal.c mulSetup.c mulMats.c mulDo.c mulDisplay.c mulMulti.c \
mulLocal.c direct.c calcp.c fastcap.c blkDirect.c uglyalloc.c \
patran.c quickif.c electric.c input.c psMatDisplay.c capsolve.c savemat_mod.c \
zbufInOut.c zbuf2fastcap.c zbufProj.c zbufSort.c

HDRS = mulStruct.h mulGlobal.h patran.h resusage.h Makefile

LIBS = -lm
CFLAGS = -O -DOTHER $(IGNR)

all : fastcap

fastcap: $(OBJS)
	$(CC) -o fastcap $(CFLAGS) $(OBJS) $(LIBS)

clean:
	$(RM) -f $(OBJS)

$(OBJS) : $(HDRS)
$(SRCS) : $(HDRS)

