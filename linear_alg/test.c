// #include <lapacke.h>
#include "matrix.h"
#include "solve.h"

int main(){
  double A[5][3] = {{1,2,3},{4,5,1},{3,5,2},{4,1,4},{2,5,3}};
  double b[5][2] = {{-10,12},{14,16},{18,-3},{14,12},{16,16}};
  
  /* Initialization */
  int m,n,nrhs, lda, ldb;
  m = 5;
  n = 3;
  nrhs = 2;
  lda = 5;
  ldb = 5;
 
  /* Print Entry Matrix */
  //print_matrix_colmajor( "Entry Matrix A", m, n, *A, lda );
  /* Print Right Rand Side */
  //print_matrix_colmajor( "Right Hand Side b", n, nrhs, *b, ldb );
  //printf( "\n" );
 
  /* Executable statements */
  printf( "LAPACKE_dgels (col-major, high-level) Example Program Results\n" );
  /* Solve least squares problem*/

  matrix *am, *bm, *sol;
  am = matrix_init(*A, m, n);
  bm = matrix_init(*b, ldb, nrhs);
  sol = matrix_init(NULL, am->nr_row, bm->nr_col);
  solve(am, bm, sol);
 
  /* Print Solution */
  //print_matrix_colmajor( "Solution", n, nrhs, *b, ldb );
  //printf( "\n" );

  matrix_free(am);
  matrix_free(bm);
  matrix_free(sol);
  return 0;
}

