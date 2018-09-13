/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xscal.cpp
 *
 * Code generation for function 'xscal'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "xscal.h"

/* Function Definitions */
void xscal(int n, double a, emxArray_real_T *x, int ix0)
{
  int i2;
  int k;
  i2 = (ix0 + n) - 1;
  for (k = ix0; k <= i2; k++) {
    x->data[k - 1] *= a;
  }
}

/* End of code generation (xscal.cpp) */
