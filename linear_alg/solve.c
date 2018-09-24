#include "solve.h"

void solve(matrix * a, matrix * b, matrix *  sol){
  // set up for wraper for LAPACKE_dgels

  lapack_int info, n,lda,ldb,nrhs, *ipiv;
  lda = a->nr_row;
  n = a->nr_col;
  ldb = b->nr_row;
  nrhs = b->nr_col;
  ipiv = malloc(sizeof(double)*lda);
  printf("Trying to copy memory\n");
  if(matrix_copy(sol, b))
    printf("Succes!\n");
  info = LAPACKE_dgesv(LAPACK_COL_MAJOR,
		       n, nrhs, a->values, lda, ipiv, sol->values, ldb);
  matrix_print(a);
  if (info)
    printf("Got the error: info = %d\n", info);
  else{
    printf("The solution was \n");
    matrix_print(sol);
  }

}
