/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * log10.cpp
 *
 * Code generation for function 'log10'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "log10.h"

/* Function Definitions */
void b_log10(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k < nx; k++) {
    x->data[k] = std::log10(x->data[k]);
  }
}

/* End of code generation (log10.cpp) */
