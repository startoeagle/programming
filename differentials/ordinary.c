#include "../linear_alg/matrix.h"
#include <stdio.h>

int main(){
  // try to solve u'(x) = 3u(x) + 2 for 0 < x <= 1, and u(0) = 1
  const int N = 100;
  double h = 1/(double)N;
  double u[N+1];
  double u_0 = 1;
  u[0] = u_0;

  
  // save function data
  FILE * fid = fopen("data", "w");
  for(int i = 0; i < N; i++){
    u[i+1] = (1 + 3*h)*u[i] + 2*h;
    fprintf(fid, "%f %f\n", (double)i/(double)N, u[i]);
  }
  fprintf(fid, "%f %f\n", (double)1, u[N]);

  fclose(fid);
  return 0;
}
