#include <stdlib.h>
#include <stdio.h>

typedef struct matrix{
  double * values;
  int nr_row;
  int nr_col;
} matrix;

typedef struct lu_pair{
  struct matrix * l;
  struct matrix * u;
  struct matrix * p; // pivot matrix
} lu_pair;


matrix * matrix_init(double * values, int nr_row, int nr_col);
matrix * tri_matrix_init(double * values, int size);
void  matrix_insert(matrix * m, double val, int row, int col);
double matrix_value(matrix * m, int row, int col);
void matrix_free(matrix * m);
matrix * matrix_multiply(matrix * a, matrix * b, matrix * res);
matrix * matrix_transpose(matrix * m, matrix * res);

void matrix_print(matrix * m);

lu_pair * lu_init(matrix * m);
void lu_free(lu_pair * lu);

matrix * pivot (matrix * m, matrix * p);
lu_pair * lu(matrix * m);
