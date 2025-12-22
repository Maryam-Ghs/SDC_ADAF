#include "lp.h"

extern int     *bndmark;
extern double  *ub;

void initxyr(m, n, a, ia, ka, at, iat, kat,
	b, c, x, y, r, s, t, bndmark, ub, dwork)
    int             m, n, *ia, *ka, *iat, *kat, *bndmark;
    double         *a, *at, *b, *c, *x, *y, *r, *s, *t, *ub, *dwork;
{
    int             i, j, k;
    double          asum, beta, dotprod();

    for (j = 0; j < n; j++) {
	asum = 0.0e0;
	for (k = ka[j]; k < ka[j + 1]; k++)
	    asum = asum + a[k] * a[k];
	x[j] = 1.0e0 / (sqrt(asum) + 1.0);
    }
    smx(m, n, a, ka, ia, x, dwork);
    beta = (sqrt(dotprod(b, b, m)) + 1.0e0)
	/ (sqrt(dotprod(dwork, dwork, m)) + 1.0e0);
    for (j = 0; j < n; j++) {
	x[j] = 10.0 * beta * x[j];
	if (x[j] > ub[j] / 2.0)
	    x[j] = ub[j] / 2.0;
	t[j] = ub[j] - x[j];
	if (x[j] < 1.0e0)
	    x[j] = 1.0e0;
	if (t[j] < 1.0e0)
	    t[j] = 1.0e0;
    }

    for (i = 0; i < m; i++)
	y[i] = 0.0e0;
    for (j = 0; j < n; j++) {
	if (bndmark[j] == 2) {
	    if (c[j] < 0.0) {
		s[j] = -c[j] + 1.0e0;
		r[j] = 1.0e0;
	    } else {
		r[j] = c[j] + 1.0e0;
		s[j] = 1.0e0;
	    }
	} else {
	    s[j] = 0.0;
	    if (c[j] < 1.0e0) {
		r[j] = 1.0e0;
	    } else {
		r[j] = c[j];
	    }
	}
    }
}
