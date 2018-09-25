
MYCFLAGS=-Wall
DIR =../linear_alg/
LIBS =-lm

LAPACKEDIR = /home/anton/Documents/programming/lapack/lapack-3.8.0
# read the things defined in another makefile, make.inc
include $(LAPACKEDIR)/make.inc

BLAS = $(LAPACKEDIR)/LAPACKE/include/$(BLASLIB)
CBLAS = $(LAPACKEDIR)/LAPACKE/include/$(CBLASLIB)

OBJS =$(DIR)matrix.o $(CBLAS) $(BLAS)

heat: heat.o $(OBJS)
	$(LOADER)  -o $@ $^

ordinary: ordinary.o
	gcc ordinary.c -o ordinary


db-heat:
	make heat 	DEBUGFLAGS=-g

clean:
	rm -f *.o

.c.o:
	$(CC) $(CFLAGS) $(MYCFLAGS) -c -o $@ $< $(DEBUGFLAGS) $(LIBS)
