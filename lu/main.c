#include <stdio.h>
#include <stdlib.h>

#include "lu.h"

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
  
  matrix_print(matrix_multiply(LU->p, m));
  printf("\n");
  
  matrix_print(matrix_multiply(LU->l, LU->u));

  
  matrix_free(m);
  lu_free(LU);

  if (!m)
    printf("m is null\n");
  else
    printf("m is not null\n");
    
  return 0;
}
