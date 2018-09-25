#include "matrix.h"

#ifdef ROW_MAJ
matrix * matrix_init(double * values, int nr_row, int nr_col){
  matrix * res = (matrix *) malloc(sizeof(matrix));
  res->nr_row = nr_row;
  res->nr_col = nr_col;
  if (values == NULL){    // set all values to zero
    // assuming that values are allocated prior if not NULL.
    res->values = (double *) malloc(sizeof(double*)*nr_row*nr_col);
     
    for (int i = 0; i < nr_row; i++)
      for(int j = 0; j < nr_col; j++)
	*(res->values + i*nr_col + j) = 0;
  }
  else
    res->values = values;
  return res;
}
#endif

#ifdef ROW_MAJ
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

#ifdef ROW_MAJ
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

#ifdef ROW_MAJ
matrix *  matrix_copy(matrix * dst, matrix * src){
  // copies the data from src to dst
  for (int i = 0; i< dst->nr_row; i++)
    for (int j = 0; j<dst->nr_col; j++)
      matrix_insert(dst, matrix_value(src, i, j), i, j);
  return dst;
}
#endif

#ifdef ROW_MAJ
matrix * matrix_multiply(matrix * a, matrix * b, matrix * c){
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
  	      a->nr_row, b->nr_col, a->nr_col, 1.0, a->values,
  	      a->nr_row, b->values, b->nr_row, 0.0, c->values, c->nr_row);
  return c;
}
#endif

matrix * matrix_insert_col(matrix * a, vector *b, int col){
  for(int i = 0; i<a->nr_row; i++){
    matrix_insert(a, vector_value(b, i), i, col);
  }
  return a;
}


vector * vector_init(double * values, int len){
  vector * res = (vector *) malloc(sizeof(vector));
  res->len = len;
  if (values == NULL){
    res->values = (double *) malloc(sizeof(double)*res->len);
    for (int i = 0; i<len; i++)
      res->values[i] = 0;
  }
  else
    res->values = values;
  return res;
}

void vector_free(vector * m){
  free(m->values);
  free(m);
}
void vector_insert(vector * m, double val, int pos){
  m->values[pos] = val;
}
double vector_value(vector * m, int pos){
  return m->values[pos];
}

#ifdef ROW_MAJ
vector * mv_multiply(matrix * a, vector * b, vector * res){
  cblas_dgemv(CblasRowMajor, CblasNoTrans,
	      a->nr_row, a->nr_col, 1.0, a->values, a->nr_row,
	      b->values, 1, 0.0, res->values, 1);
  return res;
}
#endif


void vector_print(vector * m){
  for (int i = 0; i < m->len; i++){
    printf("[%f]\n", vector_value(m, i));
  }
  printf("\n");
}
