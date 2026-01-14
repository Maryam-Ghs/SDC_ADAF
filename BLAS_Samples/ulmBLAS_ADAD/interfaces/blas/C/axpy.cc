#include BLAS_HEADER
#include <complex>
#include <ulmblas/ulmblas.h>
#include "../../ADAD_Lib/V1/adad_with_adaf/FI_Lib.h"

extern "C" {

void
ULMBLAS(saxpy)(int           n,
               float         alpha,
               const float   *x,
               int           incX,
               float         *y,
               int           incY)
{
    if (incX<0) {
        x -= incX*(n-1);
    }
    if (incY<0) {
        y -= incY*(n-1);
    }

    // TODO: this makes no use of adaf_array functionality, so it cannot detect out of bounds accesses
    //
    // the reinterpret_cast works here because adaf is a class with only a float member,
    // which has the same memory layout as just a float
    auto xadaf = reinterpret_cast<const adaf*>(x);
    auto yadaf = reinterpret_cast<adaf*>(y);
    ulmBLAS::axpy<int, adaf, adaf, adaf>(n, alpha, xadaf, incX, yadaf, incY);
}


void
ULMBLAS(daxpy)(int           n,
               double        alpha,
               const double  *x,
               int           incX,
               double        *y,
               int           incY)
{
    if (incX<0) {
        x -= incX*(n-1);
    }
    if (incY<0) {
        y -= incY*(n-1);
    }
    //ulmBLAS::axpy(n, alpha, x, incX, y, incY);
    auto xadaf = reinterpret_cast<const adafd*>(x);
    auto yadaf = reinterpret_cast<adafd*>(y);
    ulmBLAS::axpy<int, adafd, adafd, adafd>(n, alpha, xadaf, incX, yadaf, incY);
}

void
ULMBLAS(caxpy)(int           n,
               const float   *alpha_,
               const float   *x_,
               int           incX,
               float         *y_,
               int           incY)
{
    typedef std::complex<float> fcomplex;
    fcomplex       alpha = fcomplex(alpha_[0], alpha_[1]);
    const fcomplex *x    = reinterpret_cast<const fcomplex *>(x_);
    fcomplex       *y    = reinterpret_cast<fcomplex *>(y_);

    if (incX<0) {
        x -= incX*(n-1);
    }
    if (incY<0) {
        y -= incY*(n-1);
    }
    ulmBLAS::axpy(n, alpha, x, incX, y, incY);
}

void
ULMBLAS(zaxpy)(int           n,
               const double  *alpha_,
               const double  *x_,
               int           incX,
               double        *y_,
               int           incY)
{
    typedef std::complex<double> dcomplex;
    dcomplex       alpha = dcomplex(alpha_[0], alpha_[1]);
    const dcomplex *x    = reinterpret_cast<const dcomplex *>(x_);
    dcomplex       *y    = reinterpret_cast<dcomplex *>(y_);

    if (incX<0) {
        x -= incX*(n-1);
    }
    if (incY<0) {
        y -= incY*(n-1);
    }
    ulmBLAS::axpy(n, alpha, x, incX, y, incY);
}

void
CBLAS(saxpy)(int           n,
             float         alpha,
             const float   *x,
             int           incX,
             float         *y,
             int           incY)
{
    ULMBLAS(saxpy)(n, alpha, x, incX, y, incY);
}

void
CBLAS(daxpy)(int           n,
             double        alpha,
             const double  *x,
             int           incX,
             double        *y,
             int           incY)
{
    ULMBLAS(daxpy)(n, alpha, x, incX, y, incY);
}

void
CBLAS(caxpy)(int           n,
             const float   *alpha,
             const float   *x,
             int           incX,
             float         *y,
             int           incY)
{
    ULMBLAS(caxpy)(n, alpha, x, incX, y, incY);
}

void
CBLAS(zaxpy)(int           n,
             const double  *alpha,
             const double  *x,
             int           incX,
             double        *y,
             int           incY)
{
    ULMBLAS(zaxpy)(n, alpha, x, incX, y, incY);
}

} // extern "C"
