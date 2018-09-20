#ifndef _MATRIX_
#define _MATRIX_
#include <stdlib.h>
#include <stdio.h>

typedef struct matrix{
  double * values;
  int nr_row;
  int nr_col;
} matrix;

matrix * matrix_init(double * values, int nr_row, int nr_col);
void  matrix_insert(matrix * m, double val, int row, int col);
double matrix_value(matrix * m, int row, int col);
void matrix_free(matrix * m);
void matrix_print(matrix * m);
#endif
