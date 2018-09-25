#ifndef _MATRIX_
#define _MATRIX_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <lapacke.h>
// #include "cblas.h"
#include <gsl/gsl_cblas.h>

typedef struct matrix{
  double * values;
  int nr_row;
  int nr_col;
} matrix;
typedef struct vector{
  double * values;
  int len;
} vector;

matrix * matrix_init(double * values, int nr_row, int nr_col);
void  matrix_insert(matrix * m, double val, int row, int col);
double matrix_value(matrix * m, int row, int col);
void matrix_free(matrix * m);
void matrix_print(matrix * m);
matrix * matrix_copy(matrix * dst, matrix * src);
matrix * matrix_multiply(matrix * a, matrix * b, matrix * c);
matrix * matrix_insert_col(matrix * a, vector *b, int col);
vector * vector_init(double * values, int len);
void vector_free(vector * m);
void vector_insert(vector * m, double val, int pos);
double vector_value(vector * m, int len);
vector * mv_multiply(matrix * a, vector * b, vector * res);
void vector_print(vector * m);


#endif
