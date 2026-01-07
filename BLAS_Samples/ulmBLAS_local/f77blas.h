# 0 "f77blas.h.in"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4

# 1 "/usr/include/stdc-predef.h" 3 4
/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */




/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
# 56 "/usr/include/stdc-predef.h" 3 4
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
# 0 "<command-line>" 2
# 1 "f77blas.h.in"





 
# 6 "f77blas.h.in"
#ifndef ULMBLAS_F77BLAS_H
#define ULMBLAS_F77BLAS_H 1

#ifdef __cplusplus
extern "C" {
#endif

//
//  Declaration of BLAS functions currently implemented in ulmBLAS
//
void
sasum_sub_(const int *n_,
                   const float *x,
                   const int *incX_,
                   float *result_);

void
dasum_sub_(const int *n_,
                   const double *x,
                   const int *incX_,
                   double *result_);

void
saxpy_(const int *n_,
               const float *alpha_,
               const float *x,
               const int *incX_,
               float *y,
               int *incY_);
void
daxpy_(const int *n_,
               const double *alpha_,
               const double *x,
               const int *incX_,
               double *y,
               int *incY_);

void
scopy_(const int *n_,
               const float *x,
               const int *incX_,
               float *y,
               const int *incY_);

void
dcopy_(const int *n_,
               const double *x,
               const int *incX_,
               double *y,
               const int *incY_);

void
sscal_(const int *n_,
               const float *alpha_,
               float *x,
               const int *incX_);

void
dscal_(const int *n_,
               const double *alpha_,
               double *x,
               const int *incX_);

void
sswap_(const int *n_,
               float *x,
               const int *incX_,
               float *y,
               const int *incY_);

void
dswap_(const int *n_,
               double *x,
               const int *incX_,
               double *y,
               const int *incY_);

void
sdot_sub_(const int *n_,
                  const float *x,
                  const int *incX_,
                  const float *y,
                  const int *incY_,
                  float *result_);

void
ddot_sub_(const int *n_,
                  const double *x,
                  const int *incX_,
                  const double *y,
                  const int *incY_,
                  double *result_);

void
isamax_sub_(const int *n_,
                    const float *x,
                    const int *incX_,
                    int *result_);

void
idamax_sub_(const int *n_,
                    const double *x,
                    const int *incX_,
                    int *result_);

void
snrm2_sub_(const int *n_,
                   const float *x,
                   const int *incX_,
                   float *result_);

void
dnrm2_sub_(const int *n_,
                   const double *x,
                   const int *incX_,
                   double *result_);

void
srot_(const int *n_,
              float *x,
              const int *incX_,
              float *y,
              const int *incY_,
              const float *c_,
              const float *s_);

void
drot_(const int *n_,
              double *x,
              const int *incX_,
              double *y,
              const int *incY_,
              const double *c_,
              const double *s_);

void
srotg_(float *a,
               float *b,
               float *c,
               float *s);

void
drotg_(double *a,
               double *b,
               double *c,
               double *s);

void
dger_(const int *m_,
              const int *n_,
              const double *alpha_,
              const double *x,
              const int *incX_,
              const double *y,
              const int *incY_,
              double *A,
              const int *ldA_);

void
dgemv_(const char *transA_,
               const int *m_,
               const int *n_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               const double *x,
               const int *incX_,
               const double *beta_,
               double *y,
               const int *incY_);

void
dsymv_(const char *upLo_,
               const int *n_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               const double *x,
               const int *incX_,
               const double *beta_,
               double *y,
               const int *incY_);

void
dtrmv_(const char *upLo_,
               const char *transA_,
               const char *diag_,
               const int *n_,
               const double *A,
               const int *ldA_,
               double *x,
               const int *incX_);

void
dtrsv_(const char *upLo_,
               const char *transA_,
               const char *diag_,
               const int *n_,
               const double *A,
               const int *ldA_,
               double *x,
               const int *incX_);

void
dgemm_(const char *transA_,
               const char *transB_,
               const int *m_,
               const int *n_,
               const int *k_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               const double *B,
               const int *ldB_,
               const double *beta_,
               double *C,
               const int *ldC_);

void
dsymm_(const char *side_,
               const char *upLo_,
               const int *m_,
               const int *n_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               const double *B,
               const int *ldB_,
               const double *beta_,
               double *C,
               const int *ldC_);

void
dtrmm_(const char *side_,
               const char *upLo_,
               const char *transA_,
               const char *diag_,
               const int *m_,
               const int *n_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               double *B,
               const int *ldB_);

void
dtrsm_(const char *side_,
               const char *upLo_,
               const char *transA_,
               const char *diag_,
               const int *m_,
               const int *n_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               double *B,
               const int *ldB_);

void
dsyrk_(const char *upLo_,
               const char *trans_,
               const int *n_,
               const int *k_,
               const double *alpha_,
               const double *A,
               const int *ldA_,
               const double *beta_,
               double *C,
               const int *ldC_);

void
dsyr2k_(const char *upLo_,
                const char *trans_,
                const int *n_,
                const int *k_,
                const double *alpha_,
                const double *A,
                const int *ldA_,
                const double *B,
                const int *ldB_,
                const double *beta_,
                double *C,
                const int *ldC_);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
