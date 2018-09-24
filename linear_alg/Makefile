DIR =/home/anton/Documents/programming/lapack/lapack-3.8.0/
include $(DIR)make.inc

# /LAPACKE/include/ can really be anything
LIBRARIES = $(DIR)$(LAPACKELIB) $(DIR)$(LAPACKLIB) $(DIR)LAPACKE/include/$(BLASLIB)  $(DIR)LAPACKE/include/$(CBLASLIB)

# Following the format of the examples in $(DIR)/LAPACKE/example/
test: test.o matrix.o solve.o $(LIBRARIES)
	$(LOADER) $(LOADOPTS) -o $@ $^

clean: cleanobj cleanexe
cleanobj:
	rm -f *.o
cleanexe:
	rm -f x*

.c.o:
	$(CC) -D COL_MAJ $(CFLAGS) -I$(DIR)LAPACKE -I$(DIR)LAPACKE/include -c -o $@ $< -g -lgscxzlcblas -Wall
## from make.inc
# BLASLIB      = ../../librefblas.a
# CBLASLIB     = ../../libcblas.a
# LAPACKLIB    = liblapack.a
# TMGLIB       = libtmglib.a
# LAPACKELIB   = liblapacke.a
