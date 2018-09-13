/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * power.cpp
 *
 * Code generation for function 'power'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "power.h"
#include "ChhabraJensen_Yuj_w0_emxutil.h"
#include "ChhabraJensen_Yuj_w0_rtwutil.h"

/* Function Definitions */
void b_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int a_idx_0;
  unsigned int b_a_idx_0;
  int k;
  a_idx_0 = (unsigned int)a->size[0];
  b_a_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)b_a_idx_0;
  emxEnsureCapacity_real_T1(y, k);
  for (k = 0; k < (int)a_idx_0; k++) {
    y->data[k] = rt_powd_snf(a->data[k], 2.0);
  }
}

void power(const emxArray_real_T *a, double b, emxArray_real_T *y)
{
  int unnamed_idx_1;
  int k;
  unnamed_idx_1 = a->size[1];
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = a->size[1];
  emxEnsureCapacity_real_T(y, k);
  for (k = 0; k < unnamed_idx_1; k++) {
    y->data[k] = rt_powd_snf(a->data[k], b);
  }
}

/* End of code generation (power.cpp) */
