/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ChhabraJensen_Yuj_w0.cpp
 *
 * Code generation for function 'ChhabraJensen_Yuj_w0'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "sum.h"
#include "ChhabraJensen_Yuj_w0_emxutil.h"
#include "log10.h"
#include "rdivide.h"
#include "power.h"
#include "combineVectorElements.h"
#include "mldivide.h"
#include "ChhabraJensen_Yuj_w0_rtwutil.h"

/* Function Declarations */
static int div_s32(int numerator, int denominator);
static void fitting(const emxArray_real_T *x, const emxArray_real_T *y, double
                    *b, double *R2);

/* Function Definitions */
static int div_s32(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    absNumerator /= absDenominator;
    if (quotientNeedsNegation) {
      quotient = -(int)absNumerator;
    } else {
      quotient = (int)absNumerator;
    }
  }

  return quotient;
}

static void fitting(const emxArray_real_T *x, const emxArray_real_T *y, double
                    *b, double *R2)
{
  emxArray_real_T *b_y;
  int k;
  int loop_ub;
  emxArray_real_T *X;
  emxArray_real_T *yF;
  double B[2];
  int m;
  emxArray_real_T *c_y;
  int aoffset;
  double d_y;
  emxArray_real_T *r0;
  emxInit_real_T1(&b_y, 1);

  /*  end of main function */
  /*  fitting function */
  k = b_y->size[0];
  b_y->size[0] = y->size[1];
  emxEnsureCapacity_real_T1(b_y, k);
  loop_ub = y->size[1];
  for (k = 0; k < loop_ub; k++) {
    b_y->data[k] = y->data[y->size[0] * k];
  }

  emxInit_real_T(&X, 2);

  /*  CALCULATING THE COEFFICIENTS */
  loop_ub = x->size[1];
  k = X->size[0] * X->size[1];
  X->size[0] = loop_ub;
  X->size[1] = 2;
  emxEnsureCapacity_real_T(X, k);
  for (k = 0; k < loop_ub; k++) {
    X->data[k] = 1.0;
  }

  loop_ub = x->size[1];
  for (k = 0; k < loop_ub; k++) {
    X->data[k + X->size[0]] = x->data[x->size[0] * k];
  }

  emxInit_real_T1(&yF, 1);
  mldivide(X, b_y, B);
  *b = B[1];

  /* a = B(1); */
  /*  ESTIMATING THE LINE */
  m = X->size[0];
  k = yF->size[0];
  yF->size[0] = X->size[0];
  emxEnsureCapacity_real_T1(yF, k);
  for (loop_ub = 1; loop_ub <= m; loop_ub++) {
    yF->data[loop_ub - 1] = 0.0;
  }

  for (k = 0; k < 2; k++) {
    if (B[k] != 0.0) {
      aoffset = k * m;
      for (loop_ub = 0; loop_ub < m; loop_ub++) {
        yF->data[loop_ub] += B[k] * X->data[aoffset + loop_ub];
      }
    }
  }

  emxFree_real_T(&X);
  emxInit_real_T1(&c_y, 1);

  /*  CALCULATING THE R2 */
  d_y = combineVectorElements(b_y) / (double)b_y->size[0];
  k = c_y->size[0];
  c_y->size[0] = b_y->size[0];
  emxEnsureCapacity_real_T1(c_y, k);
  loop_ub = b_y->size[0];
  for (k = 0; k < loop_ub; k++) {
    c_y->data[k] = b_y->data[k] - yF->data[k];
  }

  emxInit_real_T1(&r0, 1);
  b_power(c_y, r0);
  k = c_y->size[0];
  c_y->size[0] = b_y->size[0];
  emxEnsureCapacity_real_T1(c_y, k);
  loop_ub = b_y->size[0];
  for (k = 0; k < loop_ub; k++) {
    c_y->data[k] = b_y->data[k] - d_y;
  }

  emxFree_real_T(&b_y);
  b_power(c_y, yF);
  *R2 = 1.0 - b_sum(r0) / b_sum(yF);
  emxFree_real_T(&c_y);
  emxFree_real_T(&r0);
  emxFree_real_T(&yF);
}

void ChhabraJensen_Yuj_w0(const emxArray_real_T *Timeseries, const
  emxArray_real_T *qValues, const emxArray_real_T *scales, emxArray_real_T
  *alpha, emxArray_real_T *falpha, emxArray_real_T *Dq, emxArray_real_T
  *Rsqr_alpha, emxArray_real_T *Rsqr_falpha, emxArray_real_T *Rsqr_Dq,
  emxArray_real_T *muScale, emxArray_real_T *Md, emxArray_real_T *Ma,
  emxArray_real_T *Mf)
{
  int xpageoffset;
  int loop_ub;
  int k;
  int i;
  emxArray_real_T *ps;
  emxArray_real_T *p;
  emxArray_real_T *mu;
  emxArray_real_T *b_mu;
  double q;
  int j;
  double window;
  int calclen;
  double b_Mf;
  double R2_Mf;
  double b_Md;
  double R2_Md;

  /*  LICENSE */
  /*   */
  /*  This software is licensed under an MIT License. */
  /*   */
  /*  Copyright (c) 2018 Lucas G S França, Yujiang Wang, José Miranda. */
  /*   */
  /*  Permission is hereby granted, free of charge, to any person obtaining a  */
  /*  copy of this software and associated documentation files (the "Software"),  */
  /*  to deal in the Software without restriction, including without limitation  */
  /*  the rights to use, copy, modify, merge, publish, distribute, sublicense,  */
  /*  and/or sell copies of the Software, and to permit persons to whom the  */
  /*  Software is furnished to do so, subject to the following conditions: */
  /*   */
  /*  The above copyright notice and this permission notice shall be included  */
  /*  in all copies or substantial portions of the Software. */
  /*   */
  /*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  */
  /*  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  */
  /*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  */
  /*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER  */
  /*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  */
  /*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER  */
  /*  DEALINGS IN THE SOFTWARE. */
  /*   */
  /*  Authors: Lucas França(1), Yujiang Wang(1,2,3), José Miranda (4) */
  /*   */
  /*  1 Department of Clinical and Experimental Epilepsy, UCL Institute of Neurology, */
  /*  University College London, London, United Kingdom */
  /*   */
  /*  2 Interdisciplinary Computing and Complex BioSystems (ICOS) research group, */
  /*  School of Computing Science, Newcastle University, Newcastle upon Tyne, */
  /*  United Kingdom */
  /*   */
  /*  3 Institute of Neuroscience, Newcastle University, Newcastle upon Tyne, */
  /*  United Kingdom */
  /*  */
  /*  4 Institute of Physics, Federal University of Bahia, Salvador, Bahia, */
  /*  Brazil */
  /*   */
  /*  email address: lucas.franca.14@ucl.ac.uk, Yujiang.Wang@newcastle.ac.uk */
  /*  Website: https://lucasfr.github.io/, http://xaphire.de/ */
  /* %% THIS FUNCTION WAS DEVELOPED IN ORDER TO ESTIMATE THE MULTIFRACTAL SPECTRA  */
  /* %% FROM TIME SERIES AND WAS DEVOLEP BASED ON A CODE ORIGINALLY WRITTEN BY */
  /* %% J. G. V. MIRANDA, modified by L. G. S. FRANCA. It is based on the */
  /* %% publication by Chhabra & Jensen 1989 PRL. */
  /*  This version is a faster and cleaner version of the previous codes */
  /*  written by Yujiang.Wang@newcastle.ac.uk 15th Dec 2016. It fully utilises */
  /*  the vectorisation in Matlab to speed up operations. A diagram summary of */
  /*  the algorithm can be found on the author's website www.ywang.co.uk */
  /* INPUT: */
  /* Timeseries, qValues, and scales are all row vectors */
  /* This function assumes that your time series is all positive values (sigm transform it if needed)  */
  /* None of the qValue can be between 0 and 1. */
  /* OUTPUT: */
  /* alpha and falpha scattered against each other give the multifractal spectrum */
  /* qValues and Dq scattered against each other give the generalised dimensions spectrum */
  /* Rsqr_alpha, Rsqr_falpha, and Rsqr_Dq are the R^2 values for each of the values in alpha, falpha, and Dq respectively. It is recommended to run the following code outside of the function: */
  /*  Rrej=0.9; %R^2 value below which values are rejected */
  /*  kid=Rsqr_alpha>Rrej & Rsqr_falpha>Rrej; */
  /*  alpha=alpha(kid); */
  /*  falpha=falpha(kid); */
  /* muScale, Md, Ma, and Mf are the basic matricies from which alpha, falpha, and Dq can be constructed by linear regression (see code below line 81 - 92 for details). They are included in the output mainly for completeness. */
  /*     %% initialise */
  xpageoffset = Ma->size[0] * Ma->size[1];
  Ma->size[0] = qValues->size[1];
  Ma->size[1] = scales->size[1];
  emxEnsureCapacity_real_T(Ma, xpageoffset);
  loop_ub = qValues->size[1] * scales->size[1];
  for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
    Ma->data[xpageoffset] = 0.0;
  }

  xpageoffset = Mf->size[0] * Mf->size[1];
  Mf->size[0] = qValues->size[1];
  Mf->size[1] = scales->size[1];
  emxEnsureCapacity_real_T(Mf, xpageoffset);
  loop_ub = qValues->size[1] * scales->size[1];
  for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
    Mf->data[xpageoffset] = 0.0;
  }

  xpageoffset = Md->size[0] * Md->size[1];
  Md->size[0] = qValues->size[1];
  Md->size[1] = scales->size[1];
  emxEnsureCapacity_real_T(Md, xpageoffset);
  loop_ub = qValues->size[1] * scales->size[1];
  for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
    Md->data[xpageoffset] = 0.0;
  }

  loop_ub = scales->size[1];
  xpageoffset = muScale->size[0] * muScale->size[1];
  muScale->size[0] = 1;
  muScale->size[1] = scales->size[1];
  emxEnsureCapacity_real_T(muScale, xpageoffset);
  for (k = 0; k < loop_ub; k++) {
    muScale->data[k] = rt_powd_snf(2.0, scales->data[k]);
  }

  b_log10(muScale);
  loop_ub = muScale->size[0] * muScale->size[1] - 1;
  xpageoffset = muScale->size[0] * muScale->size[1];
  muScale->size[0] = 1;
  emxEnsureCapacity_real_T(muScale, xpageoffset);
  for (xpageoffset = 0; xpageoffset <= loop_ub; xpageoffset++) {
    muScale->data[xpageoffset] = -muScale->data[xpageoffset];
  }

  /* muScale=[muScale 0]; */
  /*     %% calculating Ma_ij Mf_ij Md_ij */
  xpageoffset = Dq->size[0];
  Dq->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(Dq, xpageoffset);
  xpageoffset = falpha->size[0];
  falpha->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(falpha, xpageoffset);
  xpageoffset = alpha->size[0];
  alpha->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(alpha, xpageoffset);
  xpageoffset = Rsqr_alpha->size[0];
  Rsqr_alpha->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(Rsqr_alpha, xpageoffset);
  xpageoffset = Rsqr_falpha->size[0];
  Rsqr_falpha->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(Rsqr_falpha, xpageoffset);
  xpageoffset = Rsqr_Dq->size[0];
  Rsqr_Dq->size[0] = qValues->size[1];
  emxEnsureCapacity_real_T1(Rsqr_Dq, xpageoffset);
  i = 0;
  emxInit_real_T(&ps, 2);
  emxInit_real_T(&p, 2);
  emxInit_real_T(&mu, 2);
  emxInit_real_T(&b_mu, 2);
  while (i <= qValues->size[1] - 1) {
    q = qValues->data[i];
    for (j = 0; j < scales->size[1]; j++) {
      /* determine how many windows we will have at this scale */
      window = rt_powd_snf(2.0, scales->data[j]);

      /* break the time series into windows & sum */
      if ((int)window > 0) {
        calclen = div_s32(Timeseries->size[1], (int)window);
      } else {
        calclen = 0;
      }

      /* calculate p */
      if ((calclen == 0) || ((int)window == 0) || (calclen == 0)) {
        xpageoffset = ps->size[0] * ps->size[1];
        ps->size[0] = 1;
        ps->size[1] = (int)window;
        emxEnsureCapacity_real_T(ps, xpageoffset);
        loop_ub = (int)window;
        for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
          ps->data[xpageoffset] = 0.0;
        }
      } else {
        xpageoffset = ps->size[0] * ps->size[1];
        ps->size[0] = 1;
        ps->size[1] = (int)window;
        emxEnsureCapacity_real_T(ps, xpageoffset);
        for (loop_ub = 0; loop_ub < (int)window; loop_ub++) {
          xpageoffset = loop_ub * calclen;
          ps->data[loop_ub] = Timeseries->data[xpageoffset];
          for (k = 2; k <= calclen; k++) {
            ps->data[loop_ub] += Timeseries->data[(xpageoffset + k) - 1];
          }
        }
      }

      rdivide(ps, sum(Timeseries), p);
      power(p, q, ps);
      window = sum(ps);

      /* calculation of Md */
      Md->data[i + Md->size[0] * j] = std::log10(window);

      /* not accounting for q between 0 and 1 */
      if ((q <= 1.0) && (q > 0.0)) {
        xpageoffset = ps->size[0] * ps->size[1];
        ps->size[0] = 1;
        ps->size[1] = p->size[1];
        emxEnsureCapacity_real_T(ps, xpageoffset);
        loop_ub = p->size[0] * p->size[1];
        for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
          ps->data[xpageoffset] = p->data[xpageoffset];
        }

        b_log10(ps);
        xpageoffset = mu->size[0] * mu->size[1];
        mu->size[0] = 1;
        mu->size[1] = p->size[1];
        emxEnsureCapacity_real_T(mu, xpageoffset);
        loop_ub = p->size[0] * p->size[1];
        for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
          mu->data[xpageoffset] = p->data[xpageoffset] * ps->data[xpageoffset];
        }

        Md->data[i + Md->size[0] * j] = sum(mu) / window;
      }

      /* Ma & Mf */
      power(p, q, ps);
      rdivide(ps, window, mu);
      b_log10(p);
      xpageoffset = b_mu->size[0] * b_mu->size[1];
      b_mu->size[0] = 1;
      b_mu->size[1] = mu->size[1];
      emxEnsureCapacity_real_T(b_mu, xpageoffset);
      loop_ub = mu->size[0] * mu->size[1];
      for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
        b_mu->data[xpageoffset] = mu->data[xpageoffset] * p->data[xpageoffset];
      }

      Ma->data[i + Ma->size[0] * j] = sum(b_mu);
      xpageoffset = ps->size[0] * ps->size[1];
      ps->size[0] = 1;
      ps->size[1] = mu->size[1];
      emxEnsureCapacity_real_T(ps, xpageoffset);
      loop_ub = mu->size[0] * mu->size[1];
      for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
        ps->data[xpageoffset] = mu->data[xpageoffset];
      }

      b_log10(ps);
      xpageoffset = b_mu->size[0] * b_mu->size[1];
      b_mu->size[0] = 1;
      b_mu->size[1] = mu->size[1];
      emxEnsureCapacity_real_T(b_mu, xpageoffset);
      loop_ub = mu->size[0] * mu->size[1];
      for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
        b_mu->data[xpageoffset] = mu->data[xpageoffset] * ps->data[xpageoffset];
      }

      Mf->data[i + Mf->size[0] * j] = sum(b_mu);
    }

    /* looping through scales */
    /*         %% regression part */
    loop_ub = Ma->size[1];
    xpageoffset = mu->size[0] * mu->size[1];
    mu->size[0] = 1;
    mu->size[1] = loop_ub;
    emxEnsureCapacity_real_T(mu, xpageoffset);
    for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
      mu->data[mu->size[0] * xpageoffset] = Ma->data[i + Ma->size[0] *
        xpageoffset];
    }

    fitting(muScale, mu, &window, &q);
    loop_ub = Mf->size[1];
    xpageoffset = mu->size[0] * mu->size[1];
    mu->size[0] = 1;
    mu->size[1] = loop_ub;
    emxEnsureCapacity_real_T(mu, xpageoffset);
    for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
      mu->data[mu->size[0] * xpageoffset] = Mf->data[i + Mf->size[0] *
        xpageoffset];
    }

    fitting(muScale, mu, &b_Mf, &R2_Mf);
    loop_ub = Md->size[1];
    xpageoffset = mu->size[0] * mu->size[1];
    mu->size[0] = 1;
    mu->size[1] = loop_ub;
    emxEnsureCapacity_real_T(mu, xpageoffset);
    for (xpageoffset = 0; xpageoffset < loop_ub; xpageoffset++) {
      mu->data[mu->size[0] * xpageoffset] = Md->data[i + Md->size[0] *
        xpageoffset];
    }

    fitting(muScale, mu, &b_Md, &R2_Md);
    alpha->data[i] = window;
    falpha->data[i] = b_Mf;
    Dq->data[i] = b_Md / (qValues->data[i] - 1.0);
    if ((qValues->data[i] <= 1.0) && (qValues->data[i] > 0.0)) {
      Dq->data[i] = b_Md;
    }

    Rsqr_alpha->data[i] = q;
    Rsqr_falpha->data[i] = R2_Mf;
    Rsqr_Dq->data[i] = R2_Md;
    i++;
  }

  emxFree_real_T(&b_mu);
  emxFree_real_T(&mu);
  emxFree_real_T(&p);
  emxFree_real_T(&ps);

  /* looping through qValues */
}

/* End of code generation (ChhabraJensen_Yuj_w0.cpp) */
