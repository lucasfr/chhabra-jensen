/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * combineVectorElements.cpp
 *
 * Code generation for function 'combineVectorElements'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "combineVectorElements.h"

/* Function Definitions */
double combineVectorElements(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

/* End of code generation (combineVectorElements.cpp) */
