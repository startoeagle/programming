#include <stdio.h>
#include <gsl/gsl_cblas.h>
#include <lapacke.h>

int main(){
  double a[2][2] = {{7,2},{2,2}};
  double b[2][2] = {{-7,2},{4,-2}};
  int m,n,k,lda,ldb,ldc;
  m=n=k=lda=ldb=ldc = 2;
  double out[2][2] = {0};

  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans,
			 m, n, k, 1, *a, lda, *b, ldb, 0, *out, ldc);

  for(int i = 0; i<m; i++){
    printf("[");
    for(int j = 0; j<n-1; j++)
      printf("%f ", out[i][j]);
    printf("%f]\n", out[i][n-1]);
  }

  
  // try to to solve a linear sys of equations using lapacke
  // a[2][2] = {{7,2},{2,2}};
  double b_new[2][1] = {{-7},{-2}};
  int nrhs, *ipiv;
  ipiv = (int *) malloc(sizeof(int)*m);
  
  n=k=lda=ldb=ldc = 2;
  nrhs = 2;
  
  int info = LAPACKE_dgesv(LAPACK_COL_MAJOR, n, nrhs, *a, lda, ipiv, *b_new, ldb);
  if (info)
    printf("Something went wrong\n");

  for(int i = 0; i<m; i++){
    printf("[");
    for(int j = 0; j<n-1; j++)
      printf("%f ", b_new[i][j]);
    printf("%f]\n", b_new[i][n-1]);
  }

  
}
