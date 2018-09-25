#include <stdio.h>
#include <malloc.h>
#include <gsl/gsl_cblas.h>
// #include <lapacke.h>
void print(double * a, int row, int col){
   for(int i = 0; i<row; i++){
    printf("[");
    for(int j = 0; j<col-1; j++)
      printf("%f ", a[i*col + j]);
    printf("%f]\n", a[i*col + col-1]);
  }
   printf("\n");
}
void printa(double * a, int len){
  for(int i = 0; i<len; i++){
    printf("[");
    printf("%f]\n", a[i]);
  }
  printf("\n");
}
int main(){
  double a[2][2] = {{7,2},{2,2}};
  double b[2][2] = {{-7,2},{4,-2}};
  int m,n,k,lda,ldb,ldc;
  m=n=k=lda=ldb=ldc = 2;
  double out[2][2] = {0};
  printf("Multiplying\n");
  print(*a, 2, 2);
  printf("with\n");
  print(*b, 2, 2);
  
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
			 m, n, k, 1, *a, lda, *b, ldb, 0, *out, ldc);
  print(*out, m, n);

  // multply a matrix with a vector

  /* double *x = (double *) malloc(2*sizeof(double)); */
  /* x[0] = 1; */
  /* x[1] = 3; */
  double x[2]= {2,1};
  double *y = (double *) malloc(2*sizeof(double));
  printf("Multiplying\n");
  print(*a, 2, 2);
  printf("with\n");
  printa(x, 2);
  cblas_dgemv(CblasColMajor, CblasNoTrans,
	      m, n, 1.0, *a, lda, x, 1, 0.0, y, 1);
  printa(y, n);
  /* free(x); */
  free(y);
  
}
