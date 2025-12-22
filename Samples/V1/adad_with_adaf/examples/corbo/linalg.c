#include "lp.h"

double          dotprod(x, y, n)	   /* inner product between n-vectors
					    * x and y */
    double         *x, *y;
    int             n;
{
    int             i;
    double          dotprod = 0.0e0;

    for (i = 0; i < n; i++)
	dotprod += x[i] * y[i];

    return (dotprod);
}

void            smx(m, n, a, ka, ia, x, y) /* y = sparse matrix (a,ka,ia)
					    * times x */
    int             m, n, *ka, *ia;
    double         *a, *x, *y;
{
    int             i, j, k;

    for (i = 0; i < m; i++)
	y[i] = 0.0e0;
    for (j = 0; j < n; j++)
	for (k = ka[j]; k < ka[j + 1]; k++)
	    y[ia[k]] += a[k] * x[j];
}

void            atnum(m, n, ka, ia, a,	   /* (kat,iat,at) = transpose of
					    * (ka,ia,a) */
		                      kat, iat, at
)
    int             m, n, *ka, *ia, *kat, *iat;
    double         *a, *at;
{
    int             i, j, k, row, addr;
    int            *iwork;

    INTEGER0(iwork, m);

    for (k = 0; k < ka[n]; k++) {
	row = ia[k];
	iwork[row]++;
    }
    kat[0] = 0;
    for (i = 0; i < m; i++) {
	kat[i + 1] = kat[i] + iwork[i];
	iwork[i] = 0;
    }
    for (j = 0; j < n; j++) {
	for (k = ka[j]; k < ka[j + 1]; k++) {
	    row = ia[k];
	    addr = kat[row] + iwork[row];
	    iwork[row]++;
	    iat[addr] = j;
	    at[addr] = a[k];
	}
    }
    FREE(iwork);
}

double          maxv(x, n)		   /* compute componentwise maximum
					    * of n-vector x */
    double         *x;
    int             n;
{
    int             i;
    double          maxv = 0.0e0;

    for (i = 0; i < n; i++)
	maxv = MAX(maxv, fabs(x[i]));

    return (maxv);
}
