#include "lu.h"

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

matrix * matrix_multiply(matrix * a, matrix * b, matrix * res){
  if (a->nr_col != b->nr_row)
    perror("Dimension missmatch\n");
  
  double sum;
  for (int i=0; i<a->nr_row; i++)
    for (int j=0; j<b->nr_col; j++){
      sum = 0;
      for (int k=0; k<a->nr_col; k++)
	sum += matrix_value(a, i, k) * matrix_value(b, k, j);
      
      matrix_insert(res, sum, i, j);
    }

  return res;
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
  


lu_pair * lu_init(matrix * m){
  lu_pair * res = (lu_pair*) malloc(sizeof(lu_pair));
  res->l = matrix_init(NULL, m->nr_row, m->nr_col);
  res->u = matrix_init(NULL, m->nr_row, m->nr_col);
  res->p = matrix_init(NULL, m->nr_row, m->nr_col);
  return res;
}

void lu_free(lu_pair * lu){
  matrix_free(lu->l);
  matrix_free(lu->u);
  matrix_free(lu->p);
  free(lu);
  lu = NULL;
}


int not_in(int *list, int val){
  int len = sizeof(list)/sizeof(int);
  for(int i = 0; i<len; i++)
    if (list[i] == val)
      return 0;

  return 1;
}
matrix * pivot (matrix * m, matrix * p){
  double  max;
  int maxpos[m->nr_col];
  for (int i = 0; i < m->nr_col; i++)
    maxpos[i] = -1;
  for (int j = 0; j < m->nr_col; j++){
    max = -10000.0;
     
    for (int i = 0; i < m->nr_row; i++){
      if (not_in(maxpos, i) &&
	  max < matrix_value(m, i, j)){
	max = matrix_value(m, i, j);
	maxpos[j] = i;
      }
    }
    matrix_insert(p, 1, j, maxpos[j]);
  }

  return p;
  
}



lu_pair * lu(matrix * m){
  // perfoms an LU decomposition and returns the L and U
  if (m->nr_col != m->nr_row)
    perror("The number of colums and rows must be the same.\n");

  // allocate for the l and u matrices
  lu_pair * lu = lu_init(m);

  // pivot m
  lu->p  = pivot(m, lu->p);

  matrix * mprime = matrix_init(NULL, m->nr_col, m->nr_col);
  mprime = matrix_multiply(lu->p, m, mprime);

  // decompose
  int i, j, k;
  double sum;
  for (i = 0; i < mprime->nr_col; i++)
    for (j = i; j < mprime->nr_row; j++){
      // update u
      sum = 0;
      for (k = 0; k <= i-1; k++)
	sum += matrix_value(lu->u, k, j)*matrix_value(lu->l, i, k);

      matrix_insert(lu->u, matrix_value(mprime, i, j) - sum, i, j);

      // update l
      if (i == j)
	matrix_insert(lu->l, 1, i, j);
      else{
	sum = 0;
	for (k = 0; k <= i-1; k++)
	  sum += matrix_value(lu->u, k, i)*matrix_value(lu->l, j, k);

	matrix_insert(lu->l,
		      (matrix_value(mprime, j, i) - sum)/matrix_value(lu->u, i, i),
		      j,i);
      }
								     
    }

  matrix_free(mprime);
  return lu;
  
}
