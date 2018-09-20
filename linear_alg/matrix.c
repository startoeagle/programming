#include "matrix.h"

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

matrix * tri_matrix_init(double * values, int size){
  matrix * res = malloc(sizeof(matrix));
  res->values = (double *) malloc(sizeof(double*)*(size*(size+1))/2);
  if (values == NULL){
    // set all values to zero
    for (int i = 0; i < size; i++)
      for(int j = i; j < size; j++)
	*(res->values + i*size + j) = 0;
  }
  else
    res->values = values;
  return res;
}

void  matrix_insert(matrix * m, double values, int row, int col){
  m->values[row*(m->nr_col) + col] = values;
}

double matrix_value(matrix * m, int row, int col){
  return *(m->values + row*m->nr_col + col);
}

void matrix_free(matrix * m){
  free(m->values);
  m->values = NULL;
  free(m);
  m = NULL;
}


matrix * matrix_transpose(matrix * m, matrix * res){
  for (int i = 0; i < m->nr_row; i++)
    for (int j = 0; j < m->nr_col; j++)
      matrix_insert(res, matrix_value(m, i, j), j, i);

  return res;
}

void matrix_print(matrix * m){
  for (int i = 0; i<m->nr_row; i++){
    printf("[");
    for (int j = 0; j<m->nr_col-1; j++)
      printf("%f ", matrix_value(m, i, j));
    printf("%f]\n", matrix_value(m, i, m->nr_col-1));
  }
}
  



