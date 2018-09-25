// #include <lapacke.h>
#include "matrix.h"
#include "solve.h"

int main(){
  double A[3][3] = {{1,2,3},{4,5,1},{3,5,2}};
  // double b[5][2] = {{-10,12},{14,16},{18,-3},{14,12},{16,16}};
  double * b = (double *) malloc(sizeof(double)*3);

  b[0] = 6;
  b[1] = 3;
  b[2] = 8;
  
  /* Initialization */
  int n, lda, ldb;
  n = 3;
  lda = 3;
  ldb = 3;
 
  /* Executable statements */
  /* Solve least squares problem*/

  matrix *am;
  vector *bm, *sol;
  am = matrix_init(*A, lda, n);
  bm = vector_init(b, ldb);
  vector_print(bm);
  sol = vector_init(NULL, ldb);
  /* printf("Solving Ax = b\n"); */
  /* printf("A = \n"); */
  /* matrix_print(am); */
  /* printf("b = \n"); */
  /* matrix_print(bm); */
  /* solve(am, bm, sol); */
  /* printf("x = \n"); */
  /* matrix_print(sol); */

  // A does not exist any more!
  double A2[3][3] = {{1,1,1},{4,5,1},{3,5,2}};

  am->values = *A2;
  printf("The A matrix:\n");
  matrix_print(am);
  vector * res = vector_init(NULL, bm->len);
  mv_multiply(am, bm, res);
  
  vector_print(res);

  free(am);
  free(bm);
  free(b);
  vector_free(sol);
  vector_free(res);
  return 0;
}

