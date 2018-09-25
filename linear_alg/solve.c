#include "solve.h"

void solve(matrix * a, matrix * b, matrix *  sol){
  // set up for wraper for LAPACKE_dgels

  lapack_int info, n,lda,ldb,nrhs, *ipiv;
  lda = a->nr_row;
  n = a->nr_col;
  ldb = b->nr_row;
  nrhs = b->nr_col;
  ipiv = malloc(sizeof(double)*lda);
  if(!matrix_copy(sol, b))
    printf("Could not copy matrix momery!\n");
#ifdef ROW_MAJ
  info = LAPACKE_dgesv(LAPACK_ROW_MAJOR,
		       n, nrhs, a->values, lda, ipiv, sol->values, ldb);
#endif
  free(ipiv);
  if (info)
    printf("Got the error: info = %d\n", info);
  
}
