#include "matrix.h"

#ifdef COL_MAJ
matrix * matrix_init(double * values, int nr_row, int nr_col){
  matrix * res = (matrix *) malloc(sizeof(matrix));
  res->values = (double *) malloc(sizeof(double*)*nr_row*nr_col);
  res->nr_row = nr_row;
  res->nr_col = nr_col;
  if (values == NULL){
    // set all values to zero
    for (int i = 0; i < nr_row; i++)
      for(int j = 0; j < nr_col; j++)
	*(res->values + i*nr_col + j) = 0;
  }
  else
    res->values = values;
  return res;
}
#endif

#ifdef COL_MAJ
void  matrix_insert(matrix * m, double values, int row, int col){
  m->values[row*(m->nr_col) + col] = values;
}

double matrix_value(matrix * m, int row, int col){
  return *(m->values + row*m->nr_col + col);
}
#endif
void matrix_free(matrix * m){
  free(m->values);
  m->values = NULL;
  free(m);
  m = NULL;
}

#ifdef COL_MAJ
void matrix_print(matrix * m){
  for (int i = 0; i < m->nr_row; i++){
    printf("[");
    for (int j = 0; j < m->nr_col-1; j++)
      printf("%f ", matrix_value(m, i, j));
    printf("%f]\n", matrix_value(m, i, m->nr_col-1));
  }
  printf("\n");
}
#endif

#ifdef COL_MAJ
matrix *  matrix_copy(matrix * dst, matrix * src){
  // copies the data from src to dst
  for (int i = 0; i< dst->nr_row; i++)
    for (int j = 0; j<dst->nr_col; j++)
      matrix_insert(dst, matrix_value(src, i, j), i, j);
  return dst;
}
#endif

#ifdef COL_MAJ
matrix * matrix_multiply(matrix * a, matrix * b, matrix * c){
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
  	      a->nr_row, b->nr_col, a->nr_col, 1.0, a->values,
  	      a->nr_row, b->values, b->nr_row, 0.0, c->values, c->nr_row);
  return c;
}
#endif
