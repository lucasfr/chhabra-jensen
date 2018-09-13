/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ChhabraJensen_Yuj_w0_api.c
 *
 * Code generation for function '_coder_ChhabraJensen_Yuj_w0_api'
 *
 */

/* Include files */
#include "tmwtypes.h"
#include "_coder_ChhabraJensen_Yuj_w0_api.h"
#include "_coder_ChhabraJensen_Yuj_w0_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131466U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "ChhabraJensen_Yuj_w0",              /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y);
static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret);
static const mxArray *c_emlrt_marshallOut(const emxArray_real_T *u);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *Timeseries,
  const char_T *identifier, emxArray_real_T *y);
static const mxArray *emlrt_marshallOut(const emxArray_real_T *u);
static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray);
static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);
static void emxInit_real_T1(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush);

/* Function Definitions */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, emxArray_real_T *y)
{
  c_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *b_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv1[2] = { 0, 0 };

  y = NULL;
  m1 = emlrtCreateNumericArray(2, iv1, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m1, u->size, 2);
  emlrtAssign(&y, m1);
  return y;
}

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, emxArray_real_T *ret)
{
  static const int32_T dims[2] = { 1, -1 };

  const boolean_T bv0[2] = { false, true };

  int32_T iv3[2];
  emlrtCheckVsBuiltInR2012b(sp, (const emlrtMsgIdentifier *)msgId, src, "double",
    false, 2U, *(int32_T (*)[2])&dims[0], (boolean_T *)&bv0[0], iv3);
  ret->size[0] = iv3[0];
  ret->size[1] = iv3[1];
  ret->allocatedSize = ret->size[0] * ret->size[1];
  ret->data = (real_T *)emlrtMxGetData(src);
  ret->canFreeData = false;
  emlrtDestroyArray(&src);
}

static const mxArray *c_emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv2[2] = { 0, 0 };

  y = NULL;
  m2 = emlrtCreateNumericArray(2, iv2, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m2, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m2, u->size, 2);
  emlrtAssign(&y, m2);
  return y;
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *Timeseries,
  const char_T *identifier, emxArray_real_T *y)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(Timeseries), &thisId, y);
  emlrtDestroyArray(&Timeseries);
}

static const mxArray *emlrt_marshallOut(const emxArray_real_T *u)
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 0 };

  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m0, (void *)&u->data[0]);
  emlrtSetDimensions((mxArray *)m0, u->size, 1);
  emlrtAssign(&y, m0);
  return y;
}

static void emxFree_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (real_T *)NULL) && (*pEmxArray)->canFreeData) {
      emlrtFreeMex2018a(sp, (void *)(*pEmxArray)->data);
    }

    emlrtFreeMex2018a(sp, (void *)(*pEmxArray)->size);
    emlrtFreeMex2018a(sp, (void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

static void emxInit_real_T(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2018a(sp, (void *)pEmxArray, (void (*)(const
      void *, void *))emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

static void emxInit_real_T1(const emlrtStack *sp, emxArray_real_T **pEmxArray,
  int32_T numDimensions, boolean_T doPush)
{
  emxArray_real_T *emxArray;
  int32_T i;
  *pEmxArray = (emxArray_real_T *)emlrtMallocMex(sizeof(emxArray_real_T));
  if (doPush) {
    emlrtPushHeapReferenceStackR2018a(sp, (void *)pEmxArray, (void (*)(const
      void *, void *))emxFree_real_T);
  }

  emxArray = *pEmxArray;
  emxArray->data = (real_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int32_T *)emlrtMallocMex(sizeof(int32_T) * numDimensions);
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

void ChhabraJensen_Yuj_w0_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[10])
{
  emxArray_real_T *Timeseries;
  emxArray_real_T *qValues;
  emxArray_real_T *scales;
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
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtHeapReferenceStackEnterFcnR2012b(&st);
  emxInit_real_T(&st, &Timeseries, 2, true);
  emxInit_real_T(&st, &qValues, 2, true);
  emxInit_real_T(&st, &scales, 2, true);
  emxInit_real_T1(&st, &alpha, 1, true);
  emxInit_real_T1(&st, &falpha, 1, true);
  emxInit_real_T1(&st, &Dq, 1, true);
  emxInit_real_T1(&st, &Rsqr_alpha, 1, true);
  emxInit_real_T1(&st, &Rsqr_falpha, 1, true);
  emxInit_real_T1(&st, &Rsqr_Dq, 1, true);
  emxInit_real_T(&st, &muScale, 2, true);
  emxInit_real_T(&st, &Md, 2, true);
  emxInit_real_T(&st, &Ma, 2, true);
  emxInit_real_T(&st, &Mf, 2, true);

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "Timeseries", Timeseries);
  emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "qValues", qValues);
  emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "scales", scales);

  /* Invoke the target function */
  ChhabraJensen_Yuj_w0(Timeseries, qValues, scales, alpha, falpha, Dq,
                       Rsqr_alpha, Rsqr_falpha, Rsqr_Dq, muScale, Md, Ma, Mf);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(alpha);
  alpha->canFreeData = false;
  emxFree_real_T(&st, &alpha);
  scales->canFreeData = false;
  emxFree_real_T(&st, &scales);
  qValues->canFreeData = false;
  emxFree_real_T(&st, &qValues);
  Timeseries->canFreeData = false;
  emxFree_real_T(&st, &Timeseries);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(falpha);
  }

  falpha->canFreeData = false;
  emxFree_real_T(&st, &falpha);
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(Dq);
  }

  Dq->canFreeData = false;
  emxFree_real_T(&st, &Dq);
  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(Rsqr_alpha);
  }

  Rsqr_alpha->canFreeData = false;
  emxFree_real_T(&st, &Rsqr_alpha);
  if (nlhs > 4) {
    plhs[4] = emlrt_marshallOut(Rsqr_falpha);
  }

  Rsqr_falpha->canFreeData = false;
  emxFree_real_T(&st, &Rsqr_falpha);
  if (nlhs > 5) {
    plhs[5] = emlrt_marshallOut(Rsqr_Dq);
  }

  Rsqr_Dq->canFreeData = false;
  emxFree_real_T(&st, &Rsqr_Dq);
  if (nlhs > 6) {
    plhs[6] = b_emlrt_marshallOut(muScale);
  }

  muScale->canFreeData = false;
  emxFree_real_T(&st, &muScale);
  if (nlhs > 7) {
    plhs[7] = c_emlrt_marshallOut(Md);
  }

  Md->canFreeData = false;
  emxFree_real_T(&st, &Md);
  if (nlhs > 8) {
    plhs[8] = c_emlrt_marshallOut(Ma);
  }

  Ma->canFreeData = false;
  emxFree_real_T(&st, &Ma);
  if (nlhs > 9) {
    plhs[9] = c_emlrt_marshallOut(Mf);
  }

  Mf->canFreeData = false;
  emxFree_real_T(&st, &Mf);
  emlrtHeapReferenceStackLeaveFcnR2012b(&st);
}

void ChhabraJensen_Yuj_w0_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  ChhabraJensen_Yuj_w0_xil_terminate();
}

void ChhabraJensen_Yuj_w0_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void ChhabraJensen_Yuj_w0_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_ChhabraJensen_Yuj_w0_api.c) */
