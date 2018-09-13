/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgeqp3.cpp
 *
 * Code generation for function 'xgeqp3'
 *
 */

/* Include files */
#include <cmath>
#include "rt_nonfinite.h"
#include "ChhabraJensen_Yuj_w0.h"
#include "xgeqp3.h"
#include "xnrm2.h"
#include "xscal.h"

/* Function Declarations */
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = b * std::sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * std::sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

void xgeqp3(emxArray_real_T *A, double tau_data[], int tau_size[1], int jpvt[2])
{
  int m;
  int mn;
  int i1;
  int k;
  int j;
  int i;
  double work[2];
  double smax;
  double vn2[2];
  int i_i;
  int mmi;
  double vn1[2];
  int itemp;
  int ix;
  int pvt;
  double atmp;
  double d2;
  double s;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int exitg1;
  m = A->size[0];
  mn = A->size[0];
  if (!(mn < 2)) {
    mn = 2;
  }

  tau_size[0] = mn;
  for (i1 = 0; i1 < 2; i1++) {
    jpvt[i1] = 1 + i1;
  }

  if (A->size[0] != 0) {
    k = 1;
    for (j = 0; j < 2; j++) {
      work[j] = 0.0;
      smax = xnrm2(m, A, k);
      vn2[j] = smax;
      k += m;
      vn1[j] = smax;
    }

    for (i = 0; i < mn; i++) {
      i_i = i + i * m;
      mmi = (m - i) - 1;
      if (2 - i < 1) {
        itemp = 0;
      } else {
        itemp = 1;
        if (2 - i > 1) {
          ix = i;
          smax = std::abs(vn1[i]);
          for (k = 2; k <= 2 - i; k++) {
            ix++;
            s = std::abs(vn1[ix]);
            if (s > smax) {
              itemp = k;
              smax = s;
            }
          }
        }
      }

      pvt = (i + itemp) - 1;
      if (pvt + 1 != i + 1) {
        ix = m * pvt;
        j = m * i;
        for (k = 1; k <= m; k++) {
          smax = A->data[ix];
          A->data[ix] = A->data[j];
          A->data[j] = smax;
          ix++;
          j++;
        }

        itemp = jpvt[pvt];
        jpvt[pvt] = jpvt[i];
        jpvt[i] = itemp;
        vn1[pvt] = vn1[i];
        vn2[pvt] = vn2[i];
      }

      if (i + 1 < m) {
        atmp = A->data[i_i];
        d2 = 0.0;
        if (!(1 + mmi <= 0)) {
          smax = xnrm2(mmi, A, i_i + 2);
          if (smax != 0.0) {
            s = rt_hypotd_snf(A->data[i_i], smax);
            if (A->data[i_i] >= 0.0) {
              s = -s;
            }

            if (std::abs(s) < 1.0020841800044864E-292) {
              itemp = 0;
              do {
                itemp++;
                xscal(mmi, 9.9792015476736E+291, A, i_i + 2);
                s *= 9.9792015476736E+291;
                atmp *= 9.9792015476736E+291;
              } while (!(std::abs(s) >= 1.0020841800044864E-292));

              s = rt_hypotd_snf(atmp, xnrm2(mmi, A, i_i + 2));
              if (atmp >= 0.0) {
                s = -s;
              }

              d2 = (s - atmp) / s;
              xscal(mmi, 1.0 / (atmp - s), A, i_i + 2);
              for (k = 1; k <= itemp; k++) {
                s *= 1.0020841800044864E-292;
              }

              atmp = s;
            } else {
              d2 = (s - A->data[i_i]) / s;
              smax = 1.0 / (A->data[i_i] - s);
              xscal(mmi, smax, A, i_i + 2);
              atmp = s;
            }
          }
        }

        tau_data[i] = d2;
        A->data[i_i] = atmp;
      } else {
        tau_data[i] = 0.0;
      }

      if (i + 1 < 2) {
        atmp = A->data[i_i];
        A->data[i_i] = 1.0;
        if (tau_data[0] != 0.0) {
          lastv = mmi + 1;
          itemp = i_i + mmi;
          while ((lastv > 0) && (A->data[itemp] == 0.0)) {
            lastv--;
            itemp--;
          }

          lastc = 1 - i;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            itemp = (m + (lastc - 1) * m) + 1;
            k = itemp;
            do {
              exitg1 = 0;
              if (k <= (itemp + lastv) - 1) {
                if (A->data[k - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  k++;
                }
              } else {
                lastc--;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc != 0) {
            for (j = 1; j <= lastc; j++) {
              work[j - 1] = 0.0;
            }

            j = 0;
            i1 = (m + m * (lastc - 1)) + 1;
            itemp = 1 + m;
            while ((m > 0) && (itemp <= i1)) {
              ix = i_i;
              smax = 0.0;
              pvt = (itemp + lastv) - 1;
              for (k = itemp; k <= pvt; k++) {
                smax += A->data[k - 1] * A->data[ix];
                ix++;
              }

              work[j] += smax;
              j++;
              itemp += m;
            }
          }

          if (!(-tau_data[0] == 0.0)) {
            itemp = m;
            pvt = 0;
            for (j = 1; j <= lastc; j++) {
              if (work[pvt] != 0.0) {
                smax = work[pvt] * -tau_data[0];
                ix = i_i;
                i1 = lastv + itemp;
                for (k = itemp; k < i1; k++) {
                  A->data[k] += A->data[ix] * smax;
                  ix++;
                }
              }

              pvt++;
              itemp += m;
            }
          }
        }

        A->data[i_i] = atmp;
      }

      for (j = i + 1; j + 1 < 3; j++) {
        if (vn1[j] != 0.0) {
          smax = std::abs(A->data[i + A->size[0] * j]) / vn1[j];
          smax = 1.0 - smax * smax;
          if (smax < 0.0) {
            smax = 0.0;
          }

          s = vn1[j] / vn2[j];
          s = smax * (s * s);
          if (s <= 1.4901161193847656E-8) {
            if (i + 1 < m) {
              vn1[j] = xnrm2(mmi, A, (i + m * j) + 2);
              vn2[j] = vn1[j];
            } else {
              vn1[j] = 0.0;
              vn2[j] = 0.0;
            }
          } else {
            vn1[j] *= std::sqrt(smax);
          }
        }
      }
    }
  }
}

/* End of code generation (xgeqp3.cpp) */
