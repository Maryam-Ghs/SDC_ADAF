CFLAGS=	 -g -Wall -Wno-deprecated-non-prototype -Wno-implicit-function-declaration
SRCS=	init0.c choles.c linalg.c optlp.c iolp.c corbo.c
OBJS=	init0.o choles.o linalg.o optlp.o iolp.o corbo.o
INCL=	lp.h

corbo:	$(OBJS)
	cc $(OBJS) $(INLN) -lm -o corbo

$(OBJS):$(INCL)

clean:
	/bin/rm -f $(OBJS)
