/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * _coder_ChhabraJensen_Yuj_w0_mex.cpp
 *
 * Code generation for function '_coder_ChhabraJensen_Yuj_w0_mex'
 *
 */

/* Include files */
#include "_coder_ChhabraJensen_Yuj_w0_api.h"
#include "_coder_ChhabraJensen_Yuj_w0_mex.h"

/* Function Declarations */
static void c_ChhabraJensen_Yuj_w0_mexFunct(int32_T nlhs, mxArray *plhs[10],
  int32_T nrhs, const mxArray *prhs[3]);

/* Function Definitions */
static void c_ChhabraJensen_Yuj_w0_mexFunct(int32_T nlhs, mxArray *plhs[10],
  int32_T nrhs, const mxArray *prhs[3])
{
  const mxArray *outputs[10];
  int32_T b_nlhs;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Check for proper number of arguments. */
  if (nrhs != 3) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 3, 4,
                        20, "ChhabraJensen_Yuj_w0");
  }

  if (nlhs > 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 20,
                        "ChhabraJensen_Yuj_w0");
  }

  /* Call the function. */
  ChhabraJensen_Yuj_w0_api(prhs, nlhs, outputs);

  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }

  emlrtReturnArrays(b_nlhs, plhs, outputs);

  /* Module termination. */
  ChhabraJensen_Yuj_w0_terminate();
}

void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs, const mxArray
                 *prhs[])
{
  mexAtExit(ChhabraJensen_Yuj_w0_atexit);

  /* Initialize the memory manager. */
  /* Module initialization. */
  ChhabraJensen_Yuj_w0_initialize();

  /* Dispatch the entry-point. */
  c_ChhabraJensen_Yuj_w0_mexFunct(nlhs, plhs, nrhs, prhs);
}

emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLS(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1);
  return emlrtRootTLSGlobal;
}

/* End of code generation (_coder_ChhabraJensen_Yuj_w0_mex.cpp) */
