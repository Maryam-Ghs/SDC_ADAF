# 0 "cblas.h.in"
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
# 1 "cblas.h.in"





 
# 6 "cblas.h.in"
#ifndef ULMBLAS_CBLAS_H
#define ULMBLAS_CBLAS_H 1

#ifdef __cplusplus
extern "C" {
#endif


//
//  CBLAS/ATLAS Constants
//
enum CBLAS_ORDER {
    CblasRowMajor = 101,
    CblasColMajor = 102
};

enum CBLAS_TRANSPOSE {
    CblasNoTrans = 111,
    CblasTrans = 112,
    CblasConjTrans = 113,
    AtlasConj = 114
};

enum CBLAS_UPLO {
    CblasUpper = 121,
    CblasLower = 122
};

enum CBLAS_DIAG {
    CblasNonUnit = 131,
    CblasUnit = 132
};

enum CBLAS_SIDE {
    CblasLeft = 141,
    CblasRight = 142
};

//
//  Declaration of CBLAS functions currently implemented in ulmBLAS
//

void
cblas_xerbla(int info, const char *rout, const char *form, ...);

//
//  Level 1
//
float
cblas_sasum(int n,
             const float *x,
             int incX);

double
cblas_dasum(int n,
             const double *x,
             int incX);

float
cblas_scasum(int n,
              const float *x,
              int incX);

double
cblas_dzasum(int n,
              const double *x,
              int incX);

void
cblas_saxpy(int n,
             float alpha,
             const float *x,
             int incX,
             float *y,
             int incY);

void
cblas_daxpy(int n,
             double alpha,
             const double *x,
             int incX,
             double *y,
             int incY);

void
cblas_caxpy(int n,
             const float *alpha,
             const float *x,
             int incX,
             float *y,
             int incY);

void
cblas_zaxpy(int n,
             const double *alpha,
             const double *x,
             int incX,
             double *y,
             int incY);

void
cblas_scopy(int n,
             const float *x,
             int incX,
             float *y,
             int incY);

void
cblas_dcopy(int n,
             const double *x,
             int incX,
             double *y,
             int incY);

float
cblas_sdot(int n,
            const float *x,
            int incX,
            const float *y,
            int incY);

double
cblas_ddot(int n,
            const double *x,
            int incX,
            const double *y,
            int incY);

void
cblas_cdotc_sub(int n,
                 const float *x,
                 int incX,
                 const float *y,
                 int incY,
                 float *dotc);

void
cblas_zdotc_sub(int n,
                 const double *x,
                 int incX,
                 const double *y,
                 int incY,
                 double *dotc);

void
cblas_cdotu_sub(int n,
                 const float *x,
                 int incX,
                 const float *y,
                 int incY,
                 float *dotc);

void
cblas_zdotu_sub(int n,
                 const double *x,
                 int incX,
                 const double *y,
                 int incY,
                 double *dotc);

int
cblas_isamax(int n,
              const float *x,
              int incX);

int
cblas_idamax(int n,
              const double *x,
              int incX);

float
cblas_snrm2(int n,
             const float *x,
             int incX);

double
cblas_dnrm2(int n,
             const double *x,
             int incX);

float
cblas_scnrm2(int n,
              const float *x,
              int incX);

double
cblas_dznrm2(int n,
              const double *x,
              int incX);

void
cblas_srot(const int n,
            float *x,
            const int incX,
            float *y,
            const int incY,
            const float c,
            const float s);

void
cblas_drot(const int n,
            double *x,
            const int incX,
            double *y,
            const int incY,
            const double c,
            const double s);

void
cblas_srotg(float *a,
             float *b,
             float *c,
             float *s);

void
cblas_drotg(double *a,
             double *b,
             double *c,
             double *s);

void
cblas_sscal(const int n,
             const float alpha,
             float *x,
             const int incX);

void
cblas_dscal(const int n,
             const double alpha,
             double *x,
             const int incX);

void
cblas_sswap(const int n,
             float *x,
             const int incX,
             float *y,
             const int incY);

void
cblas_dswap(const int n,
             double *x,
             const int incX,
             double *y,
             const int incY);

void
cblas_cswap(const int n,
             float *x,
             const int incX,
             float *y,
             const int incY);

void
cblas_zswap(const int n,
             double *x,
             const int incX,
             double *y,
             const int incY);

void
cblas_zdotu_sub(const int N,
                 const double *X,
                 const int incX,
                 const double *Y,
                 const int incY,
                 double *dotu);

void
cblas_zdotc_sub(const int N,
                 const double *X,
                 const int incX,
                 const double *Y,
                 const int incY,
                 double *dotc);

float
cblas_scasum(int n,
              const float *x,
              int incX);

double
cblas_dzasum(int N,
              const double *X,
              int incX);

int
cblas_icamax(int N,
              const float *X,
              int incX);

int
cblas_izamax(int N,
              const double *X,
              int incX);

void
cblas_zswap(const int N,
             double *X,
             const int incX,
             double *Y,
             const int incY);

void
cblas_zcopy(const int N,
             const double *X,
             const int incX,
             double *Y,
             const int incY);

void
cblas_zaxpy(int N,
             const double *alpha,
             const double *X,
             int incX,
             double *Y,
             int incY);

void
cblas_cscal(const int n,
             const float *alpha,
             float *x,
             const int incX);

void
cblas_zscal(const int N,
              const double *alpha,
              double *X,
              const int incX);

void
cblas_csscal(const int n,
              const float alpha,
              float *x,
              const int incX);

void
cblas_zdscal(const int N,
             const double alpha,
             double *X,
             const int incX);

double
cblas_dznrm2(int n,
              const double *x,
              int incX);


//
//  Level 2
//

void
cblas_sgbmv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             int kl,
             int ku,
             float alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             float beta,
             float *y,
             int incY);

void
cblas_dgbmv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             int kl,
             int ku,
             double alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             double beta,
             double *y,
             int incY);

void
cblas_cgbmv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             int kl,
             int ku,
             const float *alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             const float *beta,
             float *y,
             int incY);

void
cblas_zgbmv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             int kl,
             int ku,
             const double *alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             const double *beta,
             double *y,
             int incY);

void
cblas_sgemv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             float alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             float beta,
             float *y,
             int incY);

void
cblas_dgemv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             double alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             double beta,
             double *y,
             int incY);

void
cblas_cgemv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             const float *alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             const float *beta,
             float *y,
             int incY);

void
cblas_zgemv(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             int m,
             int n,
             const double *alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             const double *beta,
             double *y,
             int incY);

void
cblas_sger(enum CBLAS_ORDER order,
            int m,
            int n,
            float alpha,
            const float *x,
            int incX,
            const float *y,
            int incY,
            float *A,
            int ldA);

void
cblas_dger(enum CBLAS_ORDER order,
            int m,
            int n,
            double alpha,
            const double *x,
            int incX,
            const double *y,
            int incY,
            double *A,
            int ldA);

void
cblas_cgeru(enum CBLAS_ORDER order,
             int m,
             int n,
             const float *alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A,
             int ldA);

void
cblas_zgeru(enum CBLAS_ORDER order,
             int m,
             int n,
             const double *alpha,
             const double *x,
             int incX,
             const double *y,
             int incY,
             double *A,
             int ldA);

void
cblas_cgerc(enum CBLAS_ORDER order,
             int m,
             int n,
             const float *alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A,
             int ldA);

void
cblas_zgerc(enum CBLAS_ORDER order,
             int m,
             int n,
             const double *alpha,
             const double *x,
             int incX,
             const double *y,
             int incY,
             double *A,
             int ldA);

void
cblas_ssymm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             float alpha,
             const float *A,
             int ldA,
             float *B,
             int ldB,
             float beta,
             float *C,
             int ldC);

void
cblas_ssymv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             float alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             float beta,
             float *y,
             int incY);

void
cblas_dsymv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             double alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             double beta,
             double *y,
             int incY);

void
cblas_chemv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const float *alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             const float *beta,
             float *y,
             int incY);

void
cblas_zhemv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const double *alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             const double *beta,
             double *y,
             int incY);

void
cblas_strmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_dtrmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_ctrmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_ztrmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_strsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_dtrsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_ztrsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_ssyr(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            float alpha,
            const float *x,
            int incX,
            float *A,
            int ldA);

void
cblas_dsyr(const enum CBLAS_ORDER order,
            const enum CBLAS_UPLO Uplo,
            int N,
            double alpha,
            const double *X,
            int incX,
            double *A,
            int lda);

void
cblas_cher(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            float alpha,
            const float *x,
            int incX,
            float *A,
            int ldA);

void
cblas_zher(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            double alpha,
            const double *x,
            int incX,
            double *A,
            int ldA);

void
cblas_ssyr2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             float alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A,
             int ldA);

void
cblas_dsyr2(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const int N,
             const double alpha,
             const double *X,
             const int incX,
             const double *Y,
             const int incY,
             double *A,
             const int lda);

void
cblas_cher2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const float *alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A,
             int ldA);

void
cblas_zher2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const double *alpha,
             const double *x,
             int incX,
             const double *y,
             int incY,
             double *A,
             int ldA);

void
cblas_stbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_dtbmv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const enum CBLAS_TRANSPOSE TransA,
             const enum CBLAS_DIAG Diag,
             const int N,
             const int K,
             const double *A,
             const int lda,
             double *X,
             const int incX);

void
cblas_ctbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_ztbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_stbsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_dtbsv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const enum CBLAS_TRANSPOSE TransA,
             const enum CBLAS_DIAG Diag,
             const int N,
             const int K,
             const double *A,
             const int lda,
             double *X,
             const int incX);

void
cblas_ctbsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_ctbsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const float *A,
             int ldA,
             float *x,
             int incX);

void
cblas_ztbsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_ssbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             int k,
             float alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             float beta,
             float *y,
             int incY);

void
cblas_dsbmv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const int N,
             const int K,
             const double alpha,
             const double *A,
             const int lda,
             const double *X,
             const int incX,
             const double beta,
             double *Y,
             const int incY);

void
cblas_chbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             int k,
             const float *alpha,
             const float *A,
             int ldA,
             const float *x,
             int incX,
             const float *beta,
             float *y,
             int incY);

void
cblas_zhbmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             int k,
             const double *alpha,
             const double *A,
             int ldA,
             const double *x,
             int incX,
             const double *beta,
             double *y,
             int incY);

void
cblas_ztbsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             int k,
             const double *A,
             int ldA,
             double *x,
             int incX);

void
cblas_sspmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             float alpha,
             const float *A,
             const float *x,
             int incX,
             float beta,
             float *y,
             int incY);

void
cblas_dspmv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const int N,
             const double alpha,
             const double *Ap,
             const double *X,
             const int incX,
             const double beta,
             double *Y,
             const int incY);

void
cblas_chpmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const float *alpha,
             const float *AP,
             const float *x,
             int incX,
             const float *beta,
             float *y,
             int incY);

void
cblas_zhpmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const double *alpha,
             const double *AP,
             const double *x,
             int incX,
             const double *beta,
             double *y,
             int incY);

void
cblas_stpmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             float *x,
             int incX);

void
cblas_dtpmv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const enum CBLAS_TRANSPOSE TransA,
             const enum CBLAS_DIAG Diag,
             const int N,
             const double *Ap,
             double *X,
             const int incX);

void
cblas_ctpmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             float *x,
             int incX);

void
cblas_ztpmv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             double *x,
             int incX);

void
cblas_stpsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             float *x,
             int incX);

void
cblas_dtpsv(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const enum CBLAS_TRANSPOSE TransA,
             const enum CBLAS_DIAG Diag,
             const int N,
             const double *Ap,
             double *X,
             const int incX);

void
cblas_ctpsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const float *A,
             float *x,
             int incX);

void
cblas_ztpsv(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             enum CBLAS_DIAG diag,
             int n,
             const double *A,
             double *x,
             int incX);

void
cblas_sspr(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            float alpha,
            const float *x,
            int incX,
            float *A);

void
cblas_dspr(const enum CBLAS_ORDER order,
            const enum CBLAS_UPLO Uplo,
            const int N,
            const double alpha,
            const double *X,
            const int incX,
            double *Ap);

void
cblas_chpr(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            float alpha,
            const float *x,
            int incX,
            float *A);

void
cblas_zhpr(enum CBLAS_ORDER order,
            enum CBLAS_UPLO upLo,
            int n,
            double alpha,
            const double *x,
            int incX,
            double *A);

void
cblas_sspr2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             float alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A);

void
cblas_dspr2(const enum CBLAS_ORDER order,
             const enum CBLAS_UPLO Uplo,
             const int N,
             const double alpha,
             const double *X,
             const int incX,
             const double *Y,
             const int incY,
             double *A);

void
cblas_chpr2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const float *alpha,
             const float *x,
             int incX,
             const float *y,
             int incY,
             float *A);

void
cblas_zhpr2(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             int n,
             const double *alpha,
             const double *x,
             int incX,
             const double *y,
             int incY,
             double *A);

//
//  Level 3
//
void
cblas_sgemm(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_TRANSPOSE transB,
             int m,
             int n,
             int k,
             float alpha,
             const float *A,
             int ldA,
             const float *B,
             int ldB,
             float beta,
             float *C,
             int ldC);

void
cblas_dgemm(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_TRANSPOSE transB,
             int m,
             int n,
             int k,
             double alpha,
             const double *A,
             int ldA,
             const double *B,
             int ldB,
             double beta,
             double *C,
             int ldC);

void
cblas_zgemm(enum CBLAS_ORDER order,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_TRANSPOSE transB,
             int m,
             int n,
             int k,
             const double *alpha,
             const double *A,
             int ldA,
             const double *B,
             int ldB,
             const double *beta,
             double *C,
             int ldC);

void
cblas_dsymm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             double alpha,
             const double *A,
             int ldA,
             double *B,
             int ldB,
             double beta,
             double *C,
             int ldC);

void
cblas_csymm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             const float *alpha,
             const float *A,
             int ldA,
             float *B,
             int ldB,
             const float *beta,
             float *C,
             int ldC);

void
cblas_zsymm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             const double *alpha,
             const double *A,
             int ldA,
             double *B,
             int ldB,
             const double *beta,
             double *C,
             int ldC);

void
cblas_chemm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             float *alpha,
             const float *A,
             int ldA,
             float *B,
             int ldB,
             float *beta,
             float *C,
             int ldC);

void
cblas_zhemm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             int m,
             int n,
             double *alpha,
             const double *A,
             int ldA,
             double *B,
             int ldB,
             double *beta,
             double *C,
             int ldC);

void
cblas_ssyr2k(enum CBLAS_ORDER order,
              enum CBLAS_UPLO upLo,
              enum CBLAS_TRANSPOSE trans,
              int n,
              int k,
              float alpha,
              const float *A,
              int ldA,
              const float *B,
              int ldB,
              float beta,
              float *C,
              int ldC);

void
cblas_dsyr2k(enum CBLAS_ORDER order,
              enum CBLAS_UPLO upLo,
              enum CBLAS_TRANSPOSE trans,
              int n,
              int k,
              double alpha,
              const double *A,
              int ldA,
              const double *B,
              int ldB,
              double beta,
              double *C,
              int ldC);

void
cblas_zsyr2k(enum CBLAS_ORDER order,
              enum CBLAS_UPLO upLo,
              enum CBLAS_TRANSPOSE trans,
              int n,
              int k,
              const double *alpha,
              const double *A,
              int ldA,
              const double *B,
              int ldB,
              const double *beta,
              double *C,
              int ldC);

void
cblas_cher2k(enum CBLAS_ORDER order,
              enum CBLAS_UPLO upLo,
              enum CBLAS_TRANSPOSE trans,
              int n,
              int k,
              float *alpha,
              const float *A,
              int ldA,
              const float *B,
              int ldB,
              float beta,
              float *C,
              int ldC);

void
cblas_zher2k(enum CBLAS_ORDER order,
              enum CBLAS_UPLO upLo,
              enum CBLAS_TRANSPOSE trans,
              int n,
              int k,
              double *alpha,
              const double *A,
              int ldA,
              const double *B,
              int ldB,
              double beta,
              double *C,
              int ldC);

void
cblas_ssyrk(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             int n,
             int k,
             float alpha,
             const float *A,
             int ldA,
             float beta,
             float *C,
             int ldC);

void
cblas_dsyrk(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             int n,
             int k,
             double alpha,
             const double *A,
             int ldA,
             double beta,
             double *C,
             int ldC);

void
cblas_zsyrk(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             int n,
             int k,
             const double *alpha,
             const double *A,
             int ldA,
             const double *beta,
             double *C,
             int ldC);

void
cblas_cherk(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             int n,
             int k,
             float alpha,
             const float *A,
             int ldA,
             float beta,
             float *C,
             int ldC);

void
cblas_zherk(enum CBLAS_ORDER order,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE trans,
             int n,
             int k,
             double alpha,
             const double *A,
             int ldA,
             double beta,
             double *C,
             int ldC);

void
cblas_strmm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             float alpha,
             const float *A,
             int ldA,
             float *B,
             const int ldB);

void
cblas_dtrmm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             double alpha,
             const double *A,
             int ldA,
             double *B,
             const int ldB);

void
cblas_ctrmm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             const float *alpha,
             const float *A,
             int ldA,
             float *B,
             const int ldB);

void
cblas_ztrmm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             const double *alpha,
             const double *A,
             int ldA,
             double *B,
             const int ldB);

void
cblas_strsm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             float alpha,
             const float *A,
             int ldA,
             float *B,
             int ldB);

void
cblas_dtrsm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             double alpha,
             const double *A,
             int ldA,
             double *B,
             int ldB);

void
cblas_ctrsm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             const float *alpha,
             const float *A,
             int ldA,
             float *B,
             int ldB);

void
cblas_ztrsm(enum CBLAS_ORDER order,
             enum CBLAS_SIDE side,
             enum CBLAS_UPLO upLo,
             enum CBLAS_TRANSPOSE transA,
             enum CBLAS_DIAG diag,
             int m,
             int n,
             const double *alpha,
             const double *A,
             int ldA,
             double *B,
             int ldB);

//
//  Level 1
//
float
ulmblas_sasum(int n,
               const float *x,
               int incX);

double
ulmblas_dasum(int n,
               const double *x,
               int incX);

float
ulmblas_scasum(int n,
                const float *x_,
                int incX);

double
ulmblas_dzasum(int n,
                const double *x_,
                int incX);

void
ulmblas_saxpy(int n,
               float alpha,
               const float *x,
               int incX,
               float *y,
               int incY);

void
ulmblas_daxpy(int n,
               double alpha,
               const double *x,
               int incX,
               double *y,
               int incY);

void
ulmblas_caxpy(int n,
               const float *alpha_,
               const float *x_,
               int incX,
               float *y_,
               int incY);

void
ulmblas_zaxpy(int n,
               const double *alpha_,
               const double *x_,
               int incX,
               double *y_,
               int incY);

void
ulmblas_scopy(int n,
               const float *x,
               int incX,
               float *y,
               int incY);

void
ulmblas_dcopy(int n,
               const double *x,
               int incX,
               double *y,
               int incY);

float
ulmblas_sdot(int n,
              const float *x,
              int incX,
              const float *y,
              int incY);

double
ulmblas_ddot(int n,
              const double *x,
              int incX,
              const double *y,
              int incY);

void
ulmblas_cdotc_sub(int n,
                   const float *x_,
                   int incX,
                   const float *y_,
                   int incY,
                   float *dotc_);

void
ulmblas_zdotc_sub(int n,
                   const double *x_,
                   int incX,
                   const double *y_,
                   int incY,
                   double *dotc_);

void
ulmblas_cdotu_sub(int n,
                   const float *x_,
                   int incX,
                   const float *y_,
                   int incY,
                   float *dotu_);

void
ulmblas_zdotu_sub(int n,
                   const double *x_,
                   int incX,
                   const double *y_,
                   int incY,
                   double *dotu_);

int
ulmblas_isamax(int n,
                const float *x,
                int incX);

int
ulmblas_idamax(int n,
                const double *x,
                int incX);

int
ulmblas_icamax(int n,
                const float *x_,
                int incX);

int
ulmblas_izamax(int n,
                const double *x_,
                int incX);

float
ulmblas_snrm2(int n,
               const float *x,
               int incX);

double
ulmblas_dnrm2(int n,
               const double *x,
               int incX);

float
ulmblas_scnrm2(int n,
                const float *x_,
                int incX);

double
ulmblas_dznrm2(int n,
                const double *x_,
                int incX);

void
ulmblas_drot(int n,
              double *x,
              int incX,
              double *y,
              int incY,
              double c,
              double s);

void
ulmblas_drotg(double *a,
               double *b,
               double *c,
               double *s);

void
ulmblas_sscal(const int n,
               const float alpha,
               float *x,
               const int incX);

void
ulmblas_dscal(const int n,
               const double alpha,
               double *x,
               const int incX);

void
ulmblas_cscal(const int n,
               const float *alpha_,
               float *x_,
               const int incX);

void
ulmblas_zscal(const int n,
               const double *alpha_,
               double *x_,
               const int incX);

void
cblas_csscal(const int n,
              const float alpha,
              float *x,
              const int incX);

void
cblas_zdscal(const int n,
              const double alpha,
              double *x,
              const int incX);

void
ulmblas_sswap(const int n,
               float *x,
               const int incX,
               float *y,
               const int incY);

void
ulmblas_dswap(const int n,
               double *x,
               const int incX,
               double *y,
               const int incY);

void
ulmblas_cswap(const int n,
               float *x_,
               const int incX,
               float *y_,
               const int incY);

void
ulmblas_zswap(const int n,
               double *x_,
               const int incX,
               double *y_,
               const int incY);


//
//  Level 2
//

void
ulmblas_sgbmv(enum CBLAS_TRANSPOSE transA,
               int m,
               int n,
               int kl,
               int ku,
               float alpha,
               const float *A,
               int ldA,
               const float *x,
               int incX,
               float beta,
               float *y,
               int incY);

void
ulmblas_dgbmv(enum CBLAS_TRANSPOSE transA,
               int m,
               int n,
               int kl,
               int ku,
               double alpha,
               const double *A,
               int ldA,
               const double *x,
               int incX,
               double beta,
               double *y,
               int incY);

void
ulmblas_cgbmv(enum CBLAS_TRANSPOSE transA_,
               int m,
               int n,
               int kl,
               int ku,
               const float *alpha_,
               const float *A_,
               int ldA,
               const float *x_,
               int incX,
               const float *beta_,
               float *y_,
               int incY);

void
ulmblas_zgbmv(enum CBLAS_TRANSPOSE transA_,
               int m,
               int n,
               int kl,
               int ku,
               const double *alpha_,
               const double *A_,
               int ldA,
               const double *x_,
               int incX,
               const double *beta_,
               double *y_,
               int incY);

void
ulmblas_sgemv(enum CBLAS_TRANSPOSE transA,
               int m,
               int n,
               float alpha,
               const float *A,
               int ldA,
               const float *x,
               int incX,
               float beta,
               float *y,
               int incY);

void
ulmblas_dgemv(enum CBLAS_TRANSPOSE transA,
               int m,
               int n,
               double alpha,
               const double *A,
               int ldA,
               const double *x,
               int incX,
               double beta,
               double *y,
               int incY);

void
ulmblas_cgemv(enum CBLAS_TRANSPOSE transA_,
               int m,
               int n,
               const float *alpha_,
               const float *A_,
               int ldA,
               const float *x_,
               int incX,
               const float *beta_,
               float *y_,
               int incY);

void
ulmblas_zgemv(enum CBLAS_TRANSPOSE transA_,
               int m,
               int n,
               const double *alpha_,
               const double *A_,
               int ldA,
               const double *x_,
               int incX,
               const double *beta_,
               double *y_,
               int incY);

void
ulmblas_sger(int m,
              int n,
              float alpha,
              const float *x,
              int incX,
              const float *y,
              int incY,
              float *A,
              int ldA);

void
ulmblas_dger(int m,
              int n,
              double alpha,
              const double *x,
              int incX,
              const double *y,
              int incY,
              double *A,
              int ldA);

void
ulmblas_cgeru(int m,
               int n,
               const float *alpha_,
               const float *x_,
               int incX,
               const float *y_,
               int incY,
               float *A_,
               int ldA);

void
ulmblas_zgeru(int m,
               int n,
               const double *alpha,
               const double *x,
               int incX,
               const double *y,
               int incY,
               double *A,
               int ldA);

void
ulmblas_cgerc(int m,
               int n,
               const float *alpha_,
               const float *x_,
               int incX,
               const float *y_,
               int incY,
               float *A_,
               int ldA);

void
ulmblas_zgerc(int m,
               int n,
               const double *alpha,
               const double *x,
               int incX,
               const double *y,
               int incY,
               double *A,
               int ldA);
void
ulmblas_ssymm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               float alpha,
               const float *A,
               int ldA,
               float *B,
               int ldB,
               float beta,
               float *C,
               int ldC);

void
ulmblas_ssymv(enum CBLAS_UPLO upLo,
               int n,
               float alpha,
               const float *A,
               int ldA,
               const float *x,
               int incX,
               float beta,
               float *y,
               int incY);

void
ulmblas_dsymv(enum CBLAS_UPLO upLo,
               int n,
               double alpha,
               const double *A,
               int ldA,
               const double *x,
               int incX,
               double beta,
               double *y,
               int incY);

void
ulmblas_chemv(enum CBLAS_UPLO upLo,
               int n,
               const float *alpha_,
               const float *A_,
               int ldA,
               const float *x_,
               int incX,
               const float *beta,
               float *y_,
               int incY);

void
ulmblas_zhemv(enum CBLAS_UPLO upLo,
               int n,
               const double *alpha_,
               const double *A_,
               int ldA,
               const double *x_,
               int incX,
               const double *beta,
               double *y_,
               int incY);

void
ulmblas_strmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_dtrmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_ctrmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               const float *A_,
               int ldA,
               float *x_,
               int incX);

void
ulmblas_ztrmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               const double *A_,
               int ldA,
               double *x_,
               int incX);

void
ulmblas_strsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_dtrsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_ctrsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_ztrsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_ssyr(enum CBLAS_UPLO upLo,
              int n,
              float alpha,
              const float *x,
              int incX,
              float *A,
              int ldA);

void
ulmblas_dsyr(const enum CBLAS_UPLO upLo,
              int N,
              double alpha,
              const double *X,
              int incX,
              double *A,
              int lda);

void
ulmblas_cher(const enum CBLAS_UPLO upLo,
              int N,
              float alpha,
              const float *X,
              int incX,
              float *A,
              int lda);

void
ulmblas_zher(const enum CBLAS_UPLO upLo,
              int N,
              double alpha,
              const double *X,
              int incX,
              double *A,
              int lda);

void
ulmblas_ssyr2(enum CBLAS_UPLO upLo,
               int n,
               float alpha,
               const float *x,
               int incX,
               const float *y,
               int incY,
               float *A,
               int ldA);

void
ulmblas_dsyr2(enum CBLAS_UPLO upLo,
               int n,
               double alpha,
               const double *x,
               int incX,
               const double *y,
               int incY,
               double *A,
               int ldA);

void
ulmblas_cher2(enum CBLAS_UPLO upLo,
               int n,
               const float *alpha_,
               const float *x_,
               int incX,
               const float *y_,
               int incY,
               float *A_,
               int ldA);

void
ulmblas_zher2(enum CBLAS_UPLO upLo,
               int n,
               const double *alpha_,
               const double *x_,
               int incX,
               const double *y_,
               int incY,
               double *A_,
               int ldA);

void
ulmblas_stbmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_dtbmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_ctbmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const float *A_,
               int ldA,
               float *x_,
               int incX);

void
ulmblas_ctbmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const float *A_,
               int ldA,
               float *x_,
               int incX);

void
ulmblas_ztbmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const double *A_,
               int ldA,
               double *x_,
               int incX);

void
ulmblas_ssbmv(enum CBLAS_UPLO upLo,
               int n,
               int k,
               float alpha,
               const float *A,
               int ldA,
               const float *x,
               int incX,
               float beta,
               float *y,
               int incY);

void
ulmblas_dsbmv(enum CBLAS_UPLO upLo,
               int n,
               int k,
               double alpha,
               const double *A,
               int ldA,
               const double *x,
               int incX,
               double beta,
               double *y,
               int incY);

void
ulmblas_chbmv(enum CBLAS_UPLO upLo,
               int n,
               int k,
               const float *alpha_,
               const float *A_,
               int ldA,
               const float *x_,
               int incX,
               const float *beta_,
               float *y_,
               int incY);
void
ulmblas_zhbmv(enum CBLAS_UPLO upLo,
               int n,
               int k,
               const double *alpha_,
               const double *A_,
               int ldA,
               const double *x_,
               int incX,
               const double *beta_,
               double *y_,
               int incY);

void
ulmblas_dtbsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_ctbsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_ztbsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const double *A,
               int ldA,
               double *x,
               int incX);

void
ulmblas_sspmv(enum CBLAS_UPLO upLo,
               int n,
               float alpha,
               const float *A,
               const float *x,
               int incX,
               float beta,
               float *y,
               int incY);

void
ulmblas_dspmv(enum CBLAS_UPLO upLo,
               int n,
               double alpha,
               const double *A,
               const double *x,
               int incX,
               double beta,
               double *y,
               int incY);

void
ulmblas_chpmv(enum CBLAS_UPLO upLo,
               int n,
               const float *alpha_,
               const float *AP_,
               const float *x_,
               int incX,
               const float *beta_,
               float *y_,
               int incY);

void
ulmblas_zhpmv(enum CBLAS_UPLO upLo,
               int n,
               const double *alpha_,
               const double *AP_,
               const double *x_,
               int incX,
               const double *beta_,
               double *y_,
               int incY);

void
ulmblas_stbsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               int k,
               const float *A,
               int ldA,
               float *x,
               int incX);

void
ulmblas_stpmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               float *x,
               int incX);

void
ulmblas_dtpmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               double *x,
               int incX);

void
ulmblas_ctpmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               const float *AP_,
               float *x_,
               int incX);

void
ulmblas_ztpmv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA_,
               enum CBLAS_DIAG diag,
               int n,
               const double *AP_,
               double *x_,
               int incX);

void
ulmblas_stpsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               float *x,
               int incX);

void
ulmblas_dtpsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               double *x,
               int incX);

void
ulmblas_ctpsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const float *A,
               float *x,
               int incX);

void
ulmblas_ztpsv(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               enum CBLAS_DIAG diag,
               int n,
               const double *A,
               double *x,
               int incX);

void
ulmblas_sspr(enum CBLAS_UPLO upLo,
              int n,
              float alpha,
              const float *x,
              int incX,
              float *A);

void
ulmblas_dspr(enum CBLAS_UPLO upLo,
              int n,
              double alpha,
              const double *x,
              int incX,
              double *A);

void
ulmblas_chpr(enum CBLAS_UPLO upLo,
              int n,
              float alpha,
              const float *x_,
              int incX,
              float *A_);

void
ulmblas_zhpr(enum CBLAS_UPLO upLo,
              int n,
              double alpha,
              const double *x_,
              int incX,
              double *A_);

void
ulmblas_sspr2(enum CBLAS_UPLO upLo,
               int n,
               float alpha,
               const float *x,
               int incX,
               const float *y,
               int incY,
               float *A);

void
ulmblas_dspr2(enum CBLAS_UPLO upLo,
               int n,
               double alpha,
               const double *x,
               int incX,
               const double *y,
               int incY,
               double *A);

void
ulmblas_chpr2(enum CBLAS_UPLO upLo,
               int n,
               const float *alpha,
               const float *x,
               int incX,
               const float *y,
               int incY,
               float *A);


void
ulmblas_zhpr2(enum CBLAS_UPLO upLo,
               int n,
               const double *alpha,
               const double *x,
               int incX,
               const double *y,
               int incY,
               double *A);

//
//  Level 3
//
void
ulmblas_sgemm(enum CBLAS_TRANSPOSE transA,
               enum CBLAS_TRANSPOSE transB,
               int m,
               int n,
               int k,
               float alpha,
               const float *A,
               int ldA,
               const float *B,
               int ldB,
               float beta,
               float *C,
               int ldC);

void
ulmblas_dgemm(enum CBLAS_TRANSPOSE transA,
               enum CBLAS_TRANSPOSE transB,
               int m,
               int n,
               int k,
               double alpha,
               const double *A,
               int ldA,
               const double *B,
               int ldB,
               double beta,
               double *C,
               int ldC);

void
ulmblas_cgemm(enum CBLAS_TRANSPOSE transA,
               enum CBLAS_TRANSPOSE transB,
               int m,
               int n,
               int k,
               const float *alpha_,
               const float *A_,
               int ldA,
               const float *B_,
               int ldB,
               const float *beta_,
               float *C_,
               int ldC);

void
ulmblas_zgemm(enum CBLAS_TRANSPOSE transA,
               enum CBLAS_TRANSPOSE transB,
               int m,
               int n,
               int k,
               const double *alpha,
               const double *A,
               int ldA,
               const double *B,
               int ldB,
               const double *beta,
               double *C,
               int ldC);

void
ulmblas_dsymm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               double alpha,
               const double *A,
               int ldA,
               double *B,
               int ldB,
               double beta,
               double *C,
               int ldC);

void
ulmblas_csymm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               const float *alpha_,
               const float *A_,
               int ldA,
               float *B_,
               int ldB,
               const float *beta_,
               float *C_,
               int ldC);

void
ulmblas_zsymm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               const double *alpha_,
               const double *A_,
               int ldA,
               double *B_,
               int ldB,
               const double *beta_,
               double *C_,
               int ldC);

void
ulmblas_chemm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               float *alpha_,
               const float *A_,
               int ldA,
               float *B_,
               int ldB,
               float *beta_,
               float *C_,
               int ldC);

void
ulmblas_zhemm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               int m,
               int n,
               double *alpha_,
               const double *A_,
               int ldA,
               double *B_,
               int ldB,
               double *beta_,
               double *C_,
               int ldC);

void
ulmblas_ssyr2k(enum CBLAS_UPLO upLo,
                enum CBLAS_TRANSPOSE trans,
                int n,
                int k,
                float alpha,
                const float *A,
                int ldA,
                const float *B,
                int ldB,
                float beta,
                float *C,
                int ldC);

void
ulmblas_dsyr2k(enum CBLAS_UPLO upLo,
                enum CBLAS_TRANSPOSE trans,
                int n,
                int k,
                double alpha,
                const double *A,
                int ldA,
                const double *B,
                int ldB,
                double beta,
                double *C,
                int ldC);

void
ulmblas_zsyr2k(enum CBLAS_UPLO upLo,
                enum CBLAS_TRANSPOSE trans,
                int n,
                int k,
                const double *alpha_,
                const double *A_,
                int ldA,
                const double *B_,
                int ldB,
                const double *beta_,
                double *C_,
                int ldC);

void
ulmblas_cher2k(enum CBLAS_UPLO upLo,
                enum CBLAS_TRANSPOSE trans,
                int n,
                int k,
                float *alpha_,
                const float *A_,
                int ldA,
                const float *B_,
                int ldB,
                float beta,
                float *C_,
                int ldC);

void
ulmblas_zher2k(enum CBLAS_UPLO upLo,
                enum CBLAS_TRANSPOSE trans,
                int n,
                int k,
                double *alpha_,
                const double *A_,
                int ldA,
                const double *B_,
                int ldB,
                double beta,
                double *C_,
                int ldC);

void
ulmblas_ssyrk(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               int n,
               int k,
               float alpha,
               const float *A,
               int ldA,
               float beta,
               float *C,
               int ldC);

void
ulmblas_dsyrk(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               int n,
               int k,
               double alpha,
               const double *A,
               int ldA,
               double beta,
               double *C,
               int ldC);

void
ulmblas_zsyrk(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               int n,
               int k,
               const double *alpha_,
               const double *A_,
               int ldA,
               const double *beta_,
               double *C_,
               int ldC);

void
ulmblas_cherk(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               int n,
               int k,
               float alpha,
               const float *A_,
               int ldA,
               float beta,
               float *C_,
               int ldC);

void
ulmblas_zherk(enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE trans,
               int n,
               int k,
               double alpha,
               const double *A_,
               int ldA,
               double beta,
               double *C_,
               int ldC);

void
ulmblas_strmm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               float alpha,
               const float *A,
               int ldA,
               float *B,
               int ldB);

void
ulmblas_dtrmm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               double alpha,
               const double *A,
               int ldA,
               double *B,
               int ldB);

void
ulmblas_ctrmm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               const float *alpha_,
               const float *A_,
               int ldA,
               float *B_,
               int ldB);

void
ulmblas_ztrmm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               const double *alpha_,
               const double *A_,
               int ldA,
               double *B_,
               int ldB);

void
ulmblas_strsm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               float alpha,
               const float *A,
               int ldA,
               float *B,
               int ldB);

void
ulmblas_dtrsm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               double alpha,
               const double *A,
               int ldA,
               double *B,
               int ldB);

void
ulmblas_ctrsm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               const float *alpha_,
               const float *A_,
               int ldA,
               float *B_,
               int ldB);

void
ulmblas_ztrsm(enum CBLAS_SIDE side,
               enum CBLAS_UPLO upLo,
               enum CBLAS_TRANSPOSE transA,
               enum CBLAS_DIAG diag,
               int m,
               int n,
               const double *alpha_,
               const double *A_,
               int ldA,
               double *B_,
               int ldB);

//
//  Functions NOT implemented
//

#ifdef __cplusplus
} // extern "C"
#endif

#endif
