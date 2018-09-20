#include "solve.h"

void solve(matrix * a, matrix * b, matrix *  sol){
  // set up for wraper for LAPACKE_dgels

  double *A, *B;
  A = a->values;
  B = b->values;
  lapack_int info, m,n,lda,ldb,nrhs;
  m = a->nr_row;
  n = a->nr_col;
  lda = m;
  ldb = b->nr_row;
  nrhs = b->nr_col;

  matrix_copy(sol, b);

  info = LAPACKE_dgels(LAPACK_COL_MAJOR, 'N', m,n,nrhs, A, lda, sol->values, ldb);
  if (info)
    printf("Got the error: info = %d\n", info);

}
