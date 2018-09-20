// function wrapers for solving linear systems
#include <lapacke.h>
#include "matrix.h"

#ifndef _SOLVE_
#define _SOLVE_
void solve(matrix * a, matrix * b, matrix *  sol);
#endif
