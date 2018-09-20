#include "solve.h"

void  solve(matrix * A, matrix * b, matrix * c){
  // solve Ab = c, for b

  // get lu decomposition
  lu_pair * LU = lu(A);
  
  // solve system
  matrix * cprim = matrix_init(NULL, LU->p->nr_row, c->nr_col);
  matrix_multiply(LU->p, c, cprim);
  matrix * y = matrix_init(NULL, A->nr_row, 1);
  int i,k;
  double sum;
  // this part seems to work!
  for (i = 0; i<y->nr_row; i++){
      sum = 0;
      for (k = 0; k<i; k++)
	sum += matrix_value(y, k, 0)*matrix_value(LU->l, i, k);
      matrix_insert(y, matrix_value(cprim, i, 0) - sum, i, 0);
  }

  for (i = cprim->nr_row-1; i>= 0; i--){
    sum = 0;
    for (k = cprim->nr_row-1; k>i; k--)
      sum += matrix_value(b, k, 0)*matrix_value(LU->u, i, k);
    matrix_insert(b,
		  (matrix_value(y, i, 0) - sum)/matrix_value(LU->u, i, i),
		  i, 0);
  }

  matrix * temp = matrix_init(NULL, LU->p->nr_row, LU->p->nr_col);
  matrix_free(cprim);
  matrix_free(temp);
  matrix_free(y);
  lu_free(LU);
}
