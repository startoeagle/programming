// #include <lapacke.h>
#include "matrix.h"
#include "solve.h"

int main(){
  double A[3][3] = {{1,2,3},{4,5,1},{3,5,2}};
  // double b[5][2] = {{-10,12},{14,16},{18,-3},{14,12},{16,16}};
  double b [3][1] = {{6},{3},{8}};
  
  /* Initialization */
  int n,nrhs, lda, ldb;
  n = 3;
  nrhs = 1;
  lda = 3;
  ldb = 3;
 
  /* Executable statements */
  /* Solve least squares problem*/

  matrix *am, *bm, *sol;
  am = matrix_init(*A, lda, n);
  bm = matrix_init(*b, ldb, nrhs);
  sol = matrix_init(NULL, am->nr_row, bm->nr_col);
  printf("Solving Ax = b\n");
  printf("A = \n");
  matrix_print(am);
  printf("b = \n");
  matrix_print(bm);
  solve(am, bm, sol);

  double A2[3][3] = {{1,2,3},{4,5,1},{3,5,2}};

  am->values = *A2;
  printf("The A matrix:\n");
  matrix_print(am);
  printf("The solution array:\n");
  matrix_print(sol);

  matrix * res = matrix_init(NULL, bm->nr_row, bm->nr_col);
  matrix_multiply(am, sol, res);
  matrix_print(res);
  return 0;
}

