#include <stdio.h>
#include <math.h>
#include "../linear_alg/matrix.h"

int main () {
  unsigned int  N,T;
  
  T = 4;
  N = 2*T;
    
  double dt, dx, alpha, r;
  alpha = 1.0;
  dt = 1.0/(double)N;
  dx = 1.0/(double)T;
  r = alpha*dt / (dx*dx);

  // set up matrix
  printf("Set the matrix\n");
  matrix * a = matrix_init(NULL, N, N);
  matrix_insert(a, 1+r*2, 0, 0); // approx second order derivative to the right
  matrix_insert(a, -5*r,  0, 1); 
  matrix_insert(a, 4*r,   0, 2); 
  matrix_insert(a, -1*r,  0, 3); 
  for (int i = 1; i<N-1; i++){
    matrix_insert(a, r,     i, i-1);
    matrix_insert(a, 1-2*r, i, i);
    matrix_insert(a, r,     i, i+1);
  }
  matrix_insert(a, -1*r,  N-1, N-4); // approx second order derivative to the right
  matrix_insert(a, 4*r,   N-1, N-3); 
  matrix_insert(a, -5*r,  N-1, N-2); 
  matrix_insert(a, 1+r*2, N-1, N-1); 


  // use the forward euler method
  printf("Prepare for the solution step\n");
  matrix * u = matrix_init(NULL, N, T);
  vector *temp, *res;
  double *temp_data = (double *)(malloc(sizeof(double)*N));
  for (int i = 0; i<N; i++)
    temp_data[i] = exp(-pow((double)i/(double)N - 0.5,2.0));
    
  temp = vector_init(temp_data, N);
  matrix_insert_col(u, temp, 0);
  res = vector_init(NULL, N);
  matrix *atemp = matrix_init(NULL, a->nr_row, a->nr_col);
  printf("Start solving\n");
  for (int t = 1; t<T; t++){
    matrix_copy(atemp, a);
    mv_multiply(atemp, temp, res);
    vector_print(res);
    // save result
    temp->values = res->values;    
    matrix_insert_col(u, res, t);
  }

  matrix_free(a);
  matrix_free(atemp);
  matrix_free(u);
  vector_free(temp);
  free(temp_data);
  free(res);

  return 0;
}
