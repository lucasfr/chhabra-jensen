/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rdivide.cpp
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "rdivide.h"
#include "ChhabraJensen_Yuj_w0_emxutil.h"

/* Function Definitions */
void rdivide(const emxArray_real_T *x, double y, emxArray_real_T *z)
{
  int i0;
  int loop_ub;
  i0 = z->size[0] * z->size[1];
  z->size[0] = 1;
  z->size[1] = x->size[1];
  emxEnsureCapacity_real_T(z, i0);
  loop_ub = x->size[0] * x->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    z->data[i0] = x->data[i0] / y;
  }
}

/* End of code generation (rdivide.cpp) */
