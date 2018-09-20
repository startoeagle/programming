#include <stdio.h>
#include <stdlib.h>

//#include "lu.h"
#include "solve.h"

int main(){
  int nr_row = 3;
  int nr_col = 3;

  int data[] = {1,3,5,2,4,7,1,1,0};

 
  matrix * m = matrix_init(NULL, nr_row, nr_col);

  for (int i = 0; i < nr_row; i++)
    for (int j = 0; j < nr_col; j++)
      matrix_insert(m, data[i*nr_col + j], i, j);

  matrix_print(m);

  lu_pair * LU;
  LU = lu(m);

  printf("L = \n");
  matrix_print(LU->l);
  printf("U = \n");
  matrix_print(LU->u);
  printf("P = \n");
  matrix_print(LU->p);
  printf("\n");

  matrix * c = matrix_init(NULL, nr_col, nr_col);
  matrix_print(matrix_multiply(LU->p, m, c));
  printf("\n");
  
  matrix_print(matrix_multiply(LU->l, LU->u, c));

  matrix_free(c);
  lu_free(LU);

  double rhs[] = {1,5,2};
  c = matrix_init(NULL, nr_row, 1);
  matrix * b = matrix_init(NULL, 3, 1);
  for (int i = 0; i < nr_row; i++)
    matrix_insert(c, rhs[i], i, 0);
  printf("c = \n");
  matrix_print(c);

  /* printf("\ntranposing...\n"); */
  /* matrix * temp = matrix_init(NULL, m->nr_col, m->nr_row); */
  /* temp = matrix_transpose(m, temp); */
  /* matrix_print(temp); */
  /* matrix_free(temp); */
  /* printf("\n"); */
 
  
  printf("solving\n");
  solve(m, b, c);
  printf("solved\n");

  matrix_print(m);
  matrix_print(b);
  matrix_print(c);

  printf("Does the solution work?\n Mb = \n");
  matrix_print(matrix_multiply(m,b,c));

  matrix_free(c); 
  matrix_free(b); 
  matrix_free(m);
  
  return 0;
}
