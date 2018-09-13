/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ChhabraJensen_Yuj_w0_api.h
 *
 * Code generation for function '_coder_ChhabraJensen_Yuj_w0_api'
 *
 */

#ifndef _CODER_CHHABRAJENSEN_YUJ_W0_API_H
#define _CODER_CHHABRAJENSEN_YUJ_W0_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_ChhabraJensen_Yuj_w0_api.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};

#endif                                 /*struct_emxArray_real_T*/

#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T

typedef struct emxArray_real_T emxArray_real_T;

#endif                                 /*typedef_emxArray_real_T*/

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void ChhabraJensen_Yuj_w0(emxArray_real_T *Timeseries, emxArray_real_T
  *qValues, emxArray_real_T *scales, emxArray_real_T *alpha, emxArray_real_T
  *falpha, emxArray_real_T *Dq, emxArray_real_T *Rsqr_alpha, emxArray_real_T
  *Rsqr_falpha, emxArray_real_T *Rsqr_Dq, emxArray_real_T *muScale,
  emxArray_real_T *Md, emxArray_real_T *Ma, emxArray_real_T *Mf);
extern void ChhabraJensen_Yuj_w0_api(const mxArray * const prhs[3], int32_T nlhs,
  const mxArray *plhs[10]);
extern void ChhabraJensen_Yuj_w0_atexit(void);
extern void ChhabraJensen_Yuj_w0_initialize(void);
extern void ChhabraJensen_Yuj_w0_terminate(void);
extern void ChhabraJensen_Yuj_w0_xil_terminate(void);

#endif

/* End of code generation (_coder_ChhabraJensen_Yuj_w0_api.h) */
