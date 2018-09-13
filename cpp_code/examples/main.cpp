/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * main.cpp
 *
 * Code generation for function 'main'
 *
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include files */
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "main.h"
#include "ChhabraJensen_Yuj_w0_terminate.h"
#include "ChhabraJensen_Yuj_w0_emxAPI.h"
#include "ChhabraJensen_Yuj_w0_initialize.h"

/* Function Declarations */
static emxArray_real_T *argInit_1xUnbounded_real_T();
static double argInit_real_T();
static void main_ChhabraJensen_Yuj_w0();

/* Function Definitions */
static emxArray_real_T *argInit_1xUnbounded_real_T()
{
  emxArray_real_T *result;
  static int iv0[2] = { 1, 2 };

  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result = emxCreateND_real_T(2, iv0);

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result->data[result->size[0] * idx1] = argInit_real_T();
  }

  return result;
}

static double argInit_real_T()
{
  return 0.0;
}

static void main_ChhabraJensen_Yuj_w0()
{
  emxArray_real_T *alpha;
  emxArray_real_T *falpha;
  emxArray_real_T *Dq;
  emxArray_real_T *Rsqr_alpha;
  emxArray_real_T *Rsqr_falpha;
  emxArray_real_T *Rsqr_Dq;
  emxArray_real_T *muScale;
  emxArray_real_T *Md;
  emxArray_real_T *Ma;
  emxArray_real_T *Mf;
  emxArray_real_T *Timeseries;
  emxArray_real_T *qValues;
  emxArray_real_T *scales;
  emxInitArray_real_T(&alpha, 1);
  emxInitArray_real_T(&falpha, 1);
  emxInitArray_real_T(&Dq, 1);
  emxInitArray_real_T(&Rsqr_alpha, 1);
  emxInitArray_real_T(&Rsqr_falpha, 1);
  emxInitArray_real_T(&Rsqr_Dq, 1);
  emxInitArray_real_T(&muScale, 2);
  emxInitArray_real_T(&Md, 2);
  emxInitArray_real_T(&Ma, 2);
  emxInitArray_real_T(&Mf, 2);

  /* Initialize function 'ChhabraJensen_Yuj_w0' input arguments. */
  /* Initialize function input argument 'Timeseries'. */
  Timeseries = argInit_1xUnbounded_real_T();

  /* Initialize function input argument 'qValues'. */
  qValues = argInit_1xUnbounded_real_T();

  /* Initialize function input argument 'scales'. */
  scales = argInit_1xUnbounded_real_T();

  /* Call the entry-point 'ChhabraJensen_Yuj_w0'. */
  ChhabraJensen_Yuj_w0(Timeseries, qValues, scales, alpha, falpha, Dq,
                       Rsqr_alpha, Rsqr_falpha, Rsqr_Dq, muScale, Md, Ma, Mf);
  emxDestroyArray_real_T(Mf);
  emxDestroyArray_real_T(Ma);
  emxDestroyArray_real_T(Md);
  emxDestroyArray_real_T(muScale);
  emxDestroyArray_real_T(Rsqr_Dq);
  emxDestroyArray_real_T(Rsqr_falpha);
  emxDestroyArray_real_T(Rsqr_alpha);
  emxDestroyArray_real_T(Dq);
  emxDestroyArray_real_T(falpha);
  emxDestroyArray_real_T(alpha);
  emxDestroyArray_real_T(scales);
  emxDestroyArray_real_T(qValues);
  emxDestroyArray_real_T(Timeseries);
}

int main(int, const char * const [])
{
  /* Initialize the application.
     You do not need to do this more than one time. */
  ChhabraJensen_Yuj_w0_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_ChhabraJensen_Yuj_w0();

  /* Terminate the application.
     You do not need to do this more than one time. */
  ChhabraJensen_Yuj_w0_terminate();
  return 0;
}

/* End of code generation (main.cpp) */
