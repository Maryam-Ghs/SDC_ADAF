#include "lp.h"

#define MAXIT  200

static int      optmpsp();
static void     error(), histo();

int             optlp(kp)
    CORBO          *kp;
{
    int             m, n, nz, *ia, *ka, maxflag, sf_req, v, split, method;
    double         *a, *b, *c, f, *r, *l, *u, *x, *y, *rc, inftol;

    int             i, j, k, m2, n2, nz2, mmaxn, row, status;

    m = kp->m;
    n = kp->n;
    nz = kp->nz;
    a = kp->a;
    ia = kp->ia;
    ka = kp->ka;
    b = kp->b;
    c = kp->c;
    f = kp->f;
    r = kp->r;
    l = kp->l;
    u = kp->u;
    x = kp->x;
    y = kp->y;
    rc = kp->rc;
    maxflag = kp->max;
    inftol = kp->inftol;
    sf_req = kp->sf_req;
    v = kp->v;
    split = kp->split;
    method = kp->method;

    mmaxn = MAX(m, n);

    if (method == PRIMAL) {

	m2 = m;
	n2 = m + n;
	nz2 = m + nz;

	if (split > 0) {
	    int             newcols = 0;
	    for (j = 0; j < n; j++)
		newcols += (ka[j + 1] - ka[j]) / split;
	    m2 += newcols;
	    n2 += newcols;
	    nz2 += 2 * newcols;
	}
	DOUBLE(x, n2);
	DOUBLE(y, m2);
	DOUBLE(rc, n2);

	REINTEGER(ia, nz2);
	REINTEGER(ka, n2 + 1);
	REDOUBLE(a, nz2);
	REDOUBLE(b, m2);
	REDOUBLE(c, n2);
	REDOUBLE(r, m2);
	REDOUBLE(l, n2);
	REDOUBLE(u, n2);

	status = optmpsp(m, n, ia, ka, a, b, c, f, r, l, u,	/* input */
			 x, y, rc,	   /* output */
			 maxflag,	   /* max = -1, min = 1 */
			 inftol,	   /* infeasibility requested */
			 sf_req,	   /* significant figures requested */
			 v,		   /* verbosity */
			 split		   /* split columns threshold */
	    );
    } else {
	int            *iat, *kat;
	double         *at, *rd, *ld, *ud, *dwork;

	INTEGER(iat, nz);
	INTEGER(kat, m + 1);
	DOUBLE(at, nz);

	atnum(m, n, ka, ia, a, kat, iat, at);	/* not necessary */
	for (k = 0; k < nz; k++)
	    at[k] = -at[k];
	for (i = 0; i < m; i++)
	    b[i] = -b[i];

	m2 = m + n;
	n2 = n;
	nz2 = nz + n;
	REDOUBLE(at, nz2);
	REINTEGER(iat, nz2);
	REINTEGER(kat, m2 + 1);
	REDOUBLE(b, m2);
	DOUBLE(rd, n2);
	DOUBLE(ld, m2);
	DOUBLE(ud, m2);
	DOUBLE(dwork, mmaxn);

	k = kat[m];
	row = m;
	for (j = 0; j < n; j++) {
	    if (l[j] > -HUGE && u[j] < HUGE) {
		rd[j] = HUGE;
		b[row] = -(u[j] - l[j]);
		kat[row + 1] = kat[row] + 1;
		iat[k] = j;
		at[k] = -1.0e0;
		k++;
		row++;
	    } else if (l[j] > -HUGE || u[j] < HUGE) {
		rd[j] = HUGE;
	    } else {
		rd[j] = 0.0;
		l[j] = 0.0;		   /* to get the fixed adjustment
					    * right */
	    }
	}
	for (i = 0; i < m; i++)
	    if (r[i] == 0.0) {
		ld[i] = -HUGE;
		ud[i] = HUGE;
	    } else if (r[i] == HUGE) {
		ld[i] = 0.0;
		ud[i] = HUGE;
	    } else
		error(9, "");
	for (i = m; i < row; i++) {
	    ld[i] = 0.0;
	    ud[i] = HUGE;
	}

	smx(m, n, a, ka, ia, l, dwork);
	for (i = 0; i < m; i++)
	    b[i] = b[i] + dwork[i];
	f = dotprod(c, l, n);

	nz = kat[row];

	n2 = n;
	m2 = row + n;
	nz2 = nz + n;

	if (split > 0) {
	    int             newcols = 0;
	    for (i = 0; i < m; i++)
		newcols += (kat[i + 1] - kat[i]) / split;
	    m2 += newcols;
	    n2 += newcols;
	    nz2 += 2 * newcols;
	}
	DOUBLE(x, n2);
	DOUBLE(y, m2);
	DOUBLE(rc, m2);

	REINTEGER(iat, nz2);
	REINTEGER(kat, m2 + 1);
	REDOUBLE(at, nz2);
	REDOUBLE(b, m2);
	REDOUBLE(c, n2);
	REDOUBLE(rd, n2);
	REDOUBLE(ld, m2);
	REDOUBLE(ud, m2);

	status = optmpsp(n, row, iat, kat, at, c, b, f, rd, ld, ud,	/* input */
			 y, x, rc,	   /* output */
			 -maxflag,	   /* max = -1, min = 1 */
			 inftol,	   /* infeasibility requested */
			 sf_req,	   /* significant figures requested */
			 v,		   /* verbosity */
			 split		   /* split columns threshold */
	    );

	smx(n, row, at, kat, iat, y, dwork);
	for (j = 0; j < n; j++)
	    rc[j] = c[j] - dwork[j];
	for (i = 0; i < m; i++)
	    y[i] = -y[i];
	for (j = 0; j < n; j++)
	    x[j] = -x[j] + l[j];
    }

    kp->x = x;
    kp->y = y;
    kp->rc = rc;

    switch (status) {
      case 0:
	printf(" OPTIMAL SOLUTION FOUND\n");
	break;
      case 1:
	printf(" SUBOPTIMAL SOLUTION FOUND\n");
	break;
      case 2:
	printf(" ITERATION LIMIT\n");
	break;
      case 3:
	printf(" PRIMAL INFEASIBLE\n");
	break;
      case 4:
	printf(" DUAL INFEASIBLE\n");
	break;
      case 5:
	printf(" PRIMAL and/or DUAL INFEASIBLE\n");
	break;
      case 6:
	printf(" PRIMAL INFEASIBLE (INCONSISTENT EQUATIONS)\n");
	break;
      case 7:
	printf(" PRIMAL UNBOUNDED\n");
	break;
      case 8:
	printf(" DUAL UNBOUNDED\n");
	break;
    }

    return status;
}

static void     error(num, text)
    int             num;
    char           *text;
{
    switch (num) {
      case 2:
	printf("cannot open file %s\n", text);
	break;
      case 3:
	printf("cannot read file %s\n", text);
	break;
      case 4:
	printf("cannot create file %s\n", text);
	break;
      case 5:
	printf("cannot write file %s\n", text);
	break;
      case 6:
	printf("cannot allocate space in output something\n");
	break;
      case 9:
	printf("cannot solve dual as primal when ranges are present\n");
	break;
      case 10:
	printf("dimension conflict in %s\n", text);
	break;
      case 11:
	printf("NAME not found\n");
	break;
      case 26:
	printf("unrecognized section label: \n   %s \n", text);
	break;
    }
    exit(num);
}

/*********  DEBUG CODE  *************************

	printf("m = %d n = %d nz = %d \n",m,n,nz);
	for (i=0; i<m; i++) printf("b = %8.4f \n",b[i]);
	for (i=0; i<m; i++) printf("r = %8.4f \n",r[i]);
	for (j=0; j<n; j++) printf("c = %8.4f \n",c[j]);

	for (j=0; j<=n; j++) printf("ka[%2d] = %2d \n",j,ka[j]);
	for (k=0; k<nz; k++) printf("ia[%2d] = %2d	a[%2d] = %8.5f \n",k,ia[k],k,a[k]);
*************************************************/
/*
{
	double infeas;

	infeas = 0.0;
	for (j=0; j<n; j++) {
		if (x[j] < l[j]) infeas += l[j]-x[j];
	}
	printf("primal lower bound infeas %e\n",infeas);
	infeas = 0.0;
	for (j=0; j<n; j++) {
		if (x[j] > u[j]) infeas += x[j]-u[j];
	}
	printf("primal upper bound infeas %e\n",infeas);
	infeas = 0.0;
	smx(m,n,a,ka,ia,x,dwork);
	for (i=0; i<m; i++) {
		b[i] = -b[i];
		if (dwork[i] < b[i]-r[i]) infeas += b[i]-r[i]-dwork[i];
		if (dwork[i] > b[i]     ) infeas += dwork[i]-b[i];
	}
	printf("primal eq infeas %e\n",infeas);
	printf("primal obj value %e\n",dotprod(c,x,n));
	infeas = 0.0;
	for (k=0; k<nz; k++) at[k] = -at[k];
	smx(n,m,at,kat,iat,y,dwork);
	for (j=0; j<n; j++) {
		if (l[j] == -HUGE && u[j] == HUGE) infeas += ABS(c[j]-dwork[j]);
		else if (u[j] == HUGE) infeas += MAX(0.0, dwork[j]-c[j]);
	}
	printf("dual ineq infeas %e\n",infeas);

}
*/


int             optstd(m, n, nz, ia, ka, a, b, c, f, bndmark, ub,
		                       x, y, r,
		                       maxflag, inftol, sf_req, v, split)
    int             m, n, nz, *ia, *ka, *bndmark, maxflag, sf_req, v, split;
    double         *a, *b, *c, f, *ub, *x, *y, *r, inftol;
{
    int             i, j, k, l, nubs, sigfig, pfeas, dfeas, iter = 1, consistent,
                    switches = 0, newcols = 0, newnz = 0, frebnd = FALSE,
                    freub = FALSE, optstd;

    int            *iat, *kat, *jub, *jj_str;

    double          alphap = 1.0, alphad = 1.0, normb, normc, pres, opres,
                    dres, odres, normr, norms, temp, mu = 0.0, primal_obj,
                    dual_obj;

    double         *dwork, *dx, *dy, *dr, *ds, *dt, *s, *t, *at, *d2, *rho,
                   *sigma, *tau, *gamma, *delta;

    double          maxv(), dotprod();

    static char    *feasflag[] = {"infeasible", "FEASIBLE  "};

    if (v) {
	printf(" m: %6d   n: %8d   nz: %10d\n", m, n, nz);
	fflush(stdout);
    }
    /*---------------------------------------------------------+
    | compute how many new columns and new nonzeros will be    |
    | created if dense columns are split                      */

    if (split > 0) {
	for (j = 0; j < n; j++)
	    newcols += (ka[j + 1] - ka[j]) / split;
	newnz = 2 * newcols;
    }
    /*---------------------------------------------------------+
    | allocate storage for bndmark and ub if not already done  |
    | (for example, in optlp).                                */

    if (bndmark == NULL) {
	INTEGER0(bndmark, n + newcols);
	frebnd = TRUE;
    }
    if (ub == NULL) {
	DOUBLE(ub, n + newcols);
	for (j = 0; j < n; j++)
	    ub[j] = HUGE;
	freub = TRUE;
    }
    /*---------------------------------------------------------+
    | split dense columns.                                     |
    | a column such as:                                        |
    |                    |                                     |
    |                    |                                     |
    |                    |                                     |
    | where each | represents several nonzero elements, gets   |
    | split into:                                              |
    |                    |                                     |
    |                     |                                    |
    |                      |                                   |
    |                    ..                                    |
    |                     ..                                   |
    | where the first . on each new row is a +1 and the second |
    | is a -1.  the right hand side for the new rows is zero.  |
    | the objective coefficients are equal to the original     |
    | coefficient divided by the number of resulting columns. */

    if (split > 0) {
	int             ii, jj, kk;

	INTEGER(jj_str, n + 1);

	for (k = nz - 1, kk = nz + newnz - 1; k >= 0; k--, kk--) {
	    a[kk] = a[k];
	    ia[kk] = ia[k];
	}

	for (j = n, jj = n + newcols; j >= 0; j--, jj--) {
	    ka[jj] = ka[j] + newnz;
	}

	for (j = n - 1, jj = n - 1 + newcols; j >= 0; j--, jj--) {
	    c[jj] = c[j];
	    bndmark[jj] = bndmark[j];
	    ub[jj] = ub[j];
	}

	jj = 0;
	kk = 0;
	k = newnz;
	jj_str[0] = 0;
	for (j = newcols; j < n + newcols; j++) {
	    int             nc;
	    nc = (ka[j + 1] - ka[j]) / split;
	    for (i = 0; i < nc; i++) {
		c[jj] = c[j] / (nc + 1);
		bndmark[jj] = bndmark[j];
		ub[jj] = ub[j];
		for (ii = 0; ii < split; ii++) {
		    a[kk] = a[k];
		    ia[kk] = ia[k];
		    kk++;
		    k++;
		}
		a[kk] = 1.0;
		ia[kk] = m;
		kk++;
		jj++;
		ka[jj] = kk;
		b[m] = 0.0;
		a[kk] = -1.0;
		ia[kk] = m;
		kk++;
		m++;
	    }
	    c[jj] = c[j] / (nc + 1);
	    bndmark[jj] = bndmark[j];
	    ub[jj] = ub[j];
	    while (k < ka[j + 1]) {
		a[kk] = a[k];
		ia[kk] = ia[k];
		kk++;
		k++;
	    }
	    jj++;
	    ka[jj] = kk;
	    jj_str[j - newcols + 1] = jj;
	}
	n += newcols;
	nz += newnz;

	if (v) {
	    printf(" m: %6d   n: %8d   nz: %10d\n", m, n, nz);
	    fflush(stdout);
	}
    }
    if (v) {
	printf("\n");
	fflush(stdout);
    }
    /*---------------------------------------------------------+
    | allocate storage.                                       */

    INTEGER(iat, nz);
    INTEGER(kat, m + 1);
    INTEGER(jub, n);

    DOUBLE(dwork, n);
    DOUBLE(dx, n);
    DOUBLE(dy, m);
    DOUBLE(dr, n);
    DOUBLE(ds, n);
    DOUBLE(dt, n);
    DOUBLE(s, n);
    DOUBLE(t, n);
    DOUBLE(at, nz);
    DOUBLE(d2, n);
    DOUBLE(rho, m);
    DOUBLE(sigma, n);
    DOUBLE(tau, n);
    DOUBLE(gamma, n);
    DOUBLE(delta, n);

    /*---------------------------------------------------------+
    |                                t    t                    |
    | initialize arrays containing  A , AA                     |
    |                                                         */

    atnum(m, n, ka, ia, a, kat, iat, at);
    atnum(n, m, kat, iat, at, ka, ia, a);

    inv_sym(m, n, ka, ia, kat, iat, v);

    /*------------------------------------------------------+
    | initialize parameters.                               */

    normb = sqrt(dotprod(b, b, m));
    normc = sqrt(dotprod(c, c, n));
    pres = HUGE;
    dres = HUGE;

    /*------------------------------------------------------+
    | if prob is a maximization, negate obj function.      */

    if (maxflag == -1) {
	f = -f;
	for (j = 0; j < n; j++)
	    c[j] = -c[j];
    }
    /*------------------------------------------------------+
    | initialize x, y, r                                   */

    initxyr(m, n, a, ia, ka, at, iat, kat,
	    b, c, x, y, r, s, t, bndmark, ub, dwork);

    /*------------------------------------------------------+
    | Compress arrays associated with upper bounds.        */

    nubs = 0;
    for (j = 0; j < n; j++)
	if (bndmark[j] == 2) {
	    jub[nubs] = j;
	    s[nubs] = s[j];
	    t[nubs] = t[j];
	    ub[nubs] = ub[j];
	    nubs++;
	}
    /*------------------------------------------------------+
    | beginning of main loop                               */

    if (v) {
	printf("%s%s \n", " - - - - - - - - - - - - - - - - - ",
	       "- - - - - - - - - - - - - - - - - - -");
	fflush(stdout);
    }
    while (iter <= MAXIT) {

	/*----------------------------------------------+
        | calculate residuals rho   = b - Ax            |
	|                     sigma = c - At y + s - r  |
	|        and          tau   = u - x - t        */

	smx(m, n, a, ka, ia, x, rho);
	for (i = 0; i < m; i++)
	    rho[i] = b[i] - rho[i];
	smx(n, m, at, kat, iat, y, sigma);
	for (j = 0; j < n; j++)
	    sigma[j] = c[j] - sigma[j] - r[j];
	for (l = 0; l < nubs; l++) {
	    j = jub[l];
	    sigma[j] += s[l];
	    tau[l] = ub[l] - x[j] - t[l];
	}

	/*----------------------------------------------+
        | calculate statistics			       */

	opres = pres;
	odres = dres;

	primal_obj = dotprod(c, x, n) + f;
	normr = sqrt(dotprod(rho, rho, m) + dotprod(tau, tau, nubs));
	pres = normr / (normb + 1.0e0);	   /* defined in lp.h */
	pfeas = (pres <= inftol);

	dual_obj = dotprod(b, y, m) - dotprod(ub, s, nubs) + f;
	norms = sqrt(dotprod(sigma, sigma, n));
	dres = norms / (normc + 1.0e0);	   /* defined in lp.h */
	dfeas = (dres <= inftol);

	if (switches == 0 &&
	    (pres > opres + inftol / 10.0 || dres > odres + inftol / 10.0)) {
	    for (j = 0; j < n; j++)
		x[j] = x[j] - dx[j] / alphap;
	    for (j = 0; j < n; j++)
		r[j] = r[j] - dr[j] / alphad;
	    for (i = 0; i < m; i++)
		y[i] = y[i] - dy[i] / alphad;
	    pfeas = (opres <= inftol);
	    dfeas = (odres <= inftol);
	    if (pfeas && dfeas) {
		optstd = 1;
		goto end;		   /* SUBOPTIMAL SOLUTION FOUND */
	    } else if (dfeas) {
		optstd = 3;
		goto end;		   /* PRIMAL INFEASIBLE */
	    } else if (pfeas) {
		optstd = 4;
		goto end;		   /* DUAL INFEASIBLE */
	    } else {
		optstd = 5;
		goto end;		   /* PRIMAL AND/OR DUAL INFEAS */
	    }
	}
	temp = fabs(primal_obj - dual_obj) / (fabs(primal_obj) + 1.0e0);
	sigfig = (int) MAX(-log10(temp + 1.0e-30), 0.0e0);
	/* defined in lp.h */

	/*----------------------------------------------+
        | print statistics                             */

	if (v > 1) {
	    FILE           *fp;
	    char            fname[50];

	    sprintf(fname, "iter.%02d", iter);

	    if ((fp = fopen(fname, "w")) == NULL)
		error(2, fname);
	    for (j = 0; j < n; j++)
		fprintf(fp, "%12.6f\n", x[j]);

	    fclose(fp);
	}
	if (v > 0) {
	    printf("%s%16.9e%s%s%s%9.2e%s\n",
		   " primal:  obj value = ", maxflag * primal_obj,
		   "      ", feasflag[pfeas],
		   " (", pres,
		   " )"
		);
	    printf("%s%16.9e%s%s%s%9.2e%s\n",
		   " dual:    obj value = ", maxflag * dual_obj,
		   "      ", feasflag[dfeas],
		   " (", dres,
		   " )"
		);
	    if (sigfig > 0)
		printf("%s%2d\n",
		       " significant  fig:   ", sigfig);
	}
	/*----------------------------------------------+
        | check stopping rule                          */

	if (pfeas && dfeas && (sigfig >= sf_req)) {
	    if (v) {
		printf(" ______________________\n");
	    }
	    optstd = 0;			   /* OPTIMAL SOLUTION FOUND */
	    goto end;
	}
	if (v) {
	    printf("%s%s \n", " ----------------------------------",
		   "-------------------------------------");
	    printf("%s%3d     ", " Iteration: ", iter);
	    fflush(stdout);
	}
	/*----------------------------------------------+
        | calculate mu                                 */

	mu = (dotprod(r, x, n) + dotprod(s, t, nubs)) / (n + nubs);
	if (primal_obj < dual_obj) {
	    mu = 2.0 * mu;
	} else {
	    mu = 0.1 * mu;
	}
	if (v > 2) {
	    float           mult;
	    printf(" mu = %12.5e, enter multiplier: ", mu);
	    scanf("%f", &mult);
	    mu = mult * mu;
	}
	printf("(mu = %12.5e)\n", mu);
	fflush(stdout);

	/*----------------------------------------------+
	| diagonal matrix D^2 = (R X^-1 + S T^-1)^-1   */

	for (j = 0; j < n; j++)
	    d2[j] = r[j] / x[j];
	for (l = 0; l < nubs; l++)
	    d2[jub[l]] += s[l] / t[l];
	for (j = 0; j < n; j++)
	    d2[j] = 1.0 / d2[j];

	/*----------------------------------------------+
        |               2 t -1                          |
        | calculate  (AD A )                            |
        |                                              */

	inv_num(m, ka, ia, a, d2, kat, iat, at, v);

	/*----------------------------------------------+
        | gamma and delta.                             */

	for (j = 0; j < n; j++)
	    gamma[j] = mu / x[j] - r[j];
	for (l = 0; l < nubs; l++)
	    delta[l] = mu / t[l] - s[l];

	/*----------------------------------------------+
        | compute step direction dy.                   */

	for (j = 0; j < n; j++)
	    dwork[j] = d2[j] * (sigma[j] - gamma[j]);
	for (l = 0; l < nubs; l++) {
	    j = jub[l];
	    dwork[j] += d2[j] * (delta[l] - s[l] * tau[l] / t[l]);
	}
	smx(m, n, a, ka, ia, dwork, dy);
	for (i = 0; i < m; i++)
	    dy[i] = dy[i] + rho[i];
	consistent = solve(m, dy);
	if (iter == 1 && !consistent) {
	    optstd = 6;
	    goto end;			   /* INCONSISTENT EQUATIONS */
	}
	/*----------------------------------------------+
        | compute dx, dt.                              */

	for (j = 0; j < n; j++)
	    dx[j] = -dwork[j];
	smx(n, m, at, kat, iat, dy, dwork);
	for (j = 0; j < n; j++) {
	    dx[j] += d2[j] * dwork[j];
	}
	for (l = 0; l < nubs; l++) {
	    j = jub[l];
	    dt[l] = tau[l] - dx[j];
	}

	/*----------------------------------------------+
        | compute dr, ds.                              */

	for (j = 0; j < n; j++) {
	    dr[j] = gamma[j] - r[j] * dx[j] / x[j];
	}
	for (l = 0; l < nubs; l++) {
	    ds[l] = delta[l] - s[l] * dt[l] / t[l];
	}

	/*----------------------------------------------+
        | compute alphap and alphad.                   */

	alphap = 0.0e0;
	for (j = 0; j < n; j++) {
	    if (alphap < -dx[j] / x[j] && ABS(bndmark[j]) != 1)
		alphap = -dx[j] / x[j];
	}
	for (l = 0; l < nubs; l++) {
	    if (alphap < -dt[l] / t[l])
		alphap = -dt[l] / t[l];
	}
	if (pfeas && alphap == 0.0e0)
	    if (dotprod(c, dx, n) < 0.0e0) {
		optstd = 7;
		goto end;
	    }				   /* PRIMAL UNBOUNDED */
	alphap = alphap / 0.95;
	if (alphap < 1.0e0)
	    alphap = 1.0e0;

	alphad = 0.0e0;
	for (j = 0; j < n; j++) {
	    if (alphad < -dr[j] / r[j])
		alphad = -dr[j] / r[j];
	}
	for (l = 0; l < nubs; l++) {
	    if (alphad < -ds[l] / s[l])
		alphad = -ds[l] / s[l];
	}
	if (dfeas && alphad == 0.0e0)
	    if (dotprod(b, dy, m) > 0.0e0) {
		optstd = 8;
		goto end;
	    }				   /* DUAL UNBOUNDED */
	alphad = alphad / 0.95;
	if (alphad < 1.0e0)
	    alphad = 1.0e0;

	/*----------------------------------------------+
	| step to new interior point                   */

	for (i = 0; i < m; i++)
	    y[i] = y[i] + dy[i] / alphad;
	for (j = 0; j < n; j++)
	    x[j] = x[j] + dx[j] / alphap;
	for (j = 0; j < n; j++)
	    r[j] = r[j] + dr[j] / alphad;
	for (l = 0; l < nubs; l++)
	    s[l] = s[l] + ds[l] / alphad;
	for (l = 0; l < nubs; l++)
	    t[l] = t[l] + dt[l] / alphap;

	/*----------------------------------------------+
	| flip free variables that got small           */

	switches = 0;
	for (j = 0; j < n; j++)
	    if (x[j] < 1.0) {
		if (ABS(bndmark[j]) == 1) {
		    f += 2.0 * c[j];
		    x[j] = 2.0 - x[j];
		    c[j] = -c[j];
		    bndmark[j] = -bndmark[j];
		    for (k = ka[j]; k < ka[j + 1]; k++) {
			b[ia[k]] -= 2.0 * a[k];
			a[k] = -a[k];
		    }
		    switches++;
		}
	    }
	if (switches > 0) {
	    atnum(m, n, ka, ia, a, kat, iat, at);
	    printf("     free variable sign changes: %d\n",
		   switches);
	}
	/*----------------------------------------------+
	| wind up this iteration                       */

	if (v) {
	    printf("%s%s \n", " - - - - - - - - - - - - - - - - - ",
		   "- - - - - - - - - - - - - - - - - - -");
	    fflush(stdout);
	}
	iter = iter + 1;
    }

    /* end of main loop                                     |
     * +------------------------------------------------------ */

    optstd = 2;				   /* ITERATION LIMIT */
end:
    /*----------------------------------------------+
    | put things back the way they were            */

    for (j = 0; j < n; j++) {
	if (bndmark[j] == -1) {
	    x[j] = 2.0 - x[j];
	    c[j] = -c[j];
	    for (k = ka[j]; k < ka[j + 1]; k++) {
		b[ia[k]] -= 2.0 * a[k];
		a[k] = -a[k];
	    }
	}
    }

    inv_clo();

    if (maxflag == -1) {
	f = -f;
	for (j = 0; j < n; j++)
	    c[j] = -c[j];
    }
    if (split > 0) {
	int             jj, kk;

	m -= newcols;
	n -= newcols;
	k = 0;
	for (j = 0; j < n; j++) {
	    jj = jj_str[j];
	    c[j] = c[jj];
	    x[j] = x[jj];
	    r[j] = r[jj];
	    for (jj++; jj < jj_str[j + 1]; jj++) {
		c[j] += c[jj];
		r[j] += r[jj];
	    }
	    for (jj = jj_str[j]; jj < jj_str[j + 1]; jj++) {
		for (kk = ka[jj]; kk < ka[jj + 1]; k++, kk++) {
		    a[k] = a[kk];
		    ia[k] = ia[kk];
		    if (ia[k] >= m)
			k--;
		}
	    }
	}
	FREE(jj_str);
    }
    FREE(iat);
    FREE(kat);
    FREE(jub);
    FREE(dwork);
    FREE(dx);
    FREE(dy);
    FREE(dr);
    FREE(ds);
    FREE(dt);
    FREE(s);
    FREE(t);
    FREE(at);
    FREE(d2);
    FREE(rho);
    FREE(sigma);
    FREE(tau);
    FREE(gamma);
    FREE(delta);
    if (frebnd)
	FREE(bndmark);
    if (freub)
	FREE(ub);

    return (optstd);
}

static int      optmpsp(m, n, ia, ka, a, b, c, f, r, l, u,
			                x, y, rc,
			                maxflag, inftol, sf_req, v, split
)
    int             m, n, *ia, *ka, maxflag, sf_req, v, split;
    double         *a, *b, *c, f, *r, *l, *u, *x, *y, *rc, inftol;
{
    int             i, j, k, m2, n2, nz2, col, status, *bndmark;

    double         *dwork, *ub;

    double          dotprod();

    /*---------------------------------------------------------+
    | this routine converts the LP from MPS form to            |
    | standard form and then calls optstd.                    */

    /*---------------------------------------------------------+
    | allocate storage.                                       */

    n2 = m + n;
    if (split > 0) {
	for (j = 0; j < n; j++)
	    n2 += (ka[j + 1] - ka[j]) / split;
    }
    INTEGER(bndmark, n2);
    DOUBLE(ub, n2);
    DOUBLE(dwork, n2);

    /*---------------------------------------------------------+
    | initialize arrays to mark bound types                    |
    | and to store upper bounds.                              */

    for (j = 0; j < n2; j++) {
	bndmark[j] = 0;
	ub[j] = HUGE;
    }

    /*---------------------------------------------------------+
    | mark bound types and adjust bounds.                     */

    for (j = 0; j < n; j++) {
	if (l[j] <= -HUGE) {
	    l[j] = 0.0e0;
	    bndmark[j] = 1;		   /* free variables */
	} else if (u[j] < HUGE) {
	    ub[j] = u[j] - l[j];
	    bndmark[j] = 2;		   /* finite upper bounds */
	}
    }

    /*---------------------------------------------------------+
    | adjust right-hand side and fixed adjustment              |
    | for lower bound shift.                                  */

    smx(m, n, a, ka, ia, l, dwork);
    for (i = 0; i < m; i++)
	b[i] -= dwork[i];
    f += dotprod(c, l, n);

    /*---------------------------------------------------------+
    | Add slacks for inequality constraints.                  */

    k = ka[n];
    col = n;
    for (i = 0; i < m; i++) {
	if (r[i] != 0.0) {
	    c[col] = 0.0;
	    ub[col] = r[i];
	    if (ub[col] < HUGE)
		bndmark[col] = 2;
	    else
		bndmark[col] = 0;
	    ka[col + 1] = ka[col] + 1;
	    ia[k] = i;
	    a[k] = 1.0e0;
	    k++;
	    col++;
	}
    }

    n2 = col;
    m2 = m;
    nz2 = ka[n2];

    status = optstd(m2, n2, nz2, ia, ka, a, b, c, f, bndmark, ub,	/* input */
		    x, y, rc,		   /* output */
		    maxflag, inftol, sf_req, v, split	/* parameters */
	);

    for (j = 0; j < n; j++) {
	x[j] += l[j];
	if (bndmark[j] == 1)
	    l[j] = -HUGE;
    }
    for (i = 0; i < m; i++)
	b[i] += dwork[i];

    FREE(bndmark);
    FREE(ub);
    FREE(dwork);

    return (status);
}

static void     histo(s, x, n)
    char           *s;
    double         *x;
    int             n;
{
    int             i, j, bucket[25], zeros = 0;

    for (i = 0; i < 25; i++)
	bucket[i] = 0;

    for (j = 0; j < n; j++) {
	if (ABS(x[j]) > 0.0) {
	    i = (int) log10(ABS(x[j]));
	    if (i < -12)
		i = -12;
	    if (i > 12)
		i = 12;
	    bucket[i + 12]++;
	} else {
	    zeros++;
	}
    }
    printf("+------------------------------------");
    printf("-------------------------------------+ \n");
    printf("| %s: \n", s);
    printf("| zeros %5d:", zeros);
    printf("                                ");
    printf("                            | \n");
    printf("| ");
    for (i = 11; i >= 0; i--)
	printf("%5d ", bucket[i]);
    printf("| \n");
    printf("| %5d ", bucket[12]);
    printf("                                 ");
    printf("                                 | \n");
    printf("| ");
    for (i = 13; i < 25; i++)
	printf("%5d ", bucket[i]);
    printf("| \n");
    printf("+------------------------------------");
    printf("-------------------------------------+ \n");
}

int             optdense(m, n, ad, b, c, f,
			                 x, y, rc,
			                 maxflag, inftol, sf_req, v, split)
    int             m, n, maxflag, sf_req, v, split;
    double        **ad, *b, *c, f, *x, *y, *rc, inftol;
{
    int             i, j, nz = 0, *ia, *ka, status;
    double         *a;
    double         *r;
    double         *l;
    double         *u;
    CORBO           xxx, *kp;

    INTEGER(ia, m * n);
    INTEGER(ka, n + 1);
    DOUBLE(a, m * n);
    DOUBLE(r, m);
    DOUBLE(l, n);
    DOUBLE(u, n);

    for (j = 0; j < n; j++) {
	l[j] = 0;
	u[j] = HUGE;
    }
    for (i = 0; i < m; i++)
	r[i] = 0;

    for (j = 0; j < n; j++) {
	ka[j] = nz;
	for (i = 0; i < m; i++) {
	    if (ad[i][j] != 0.0) {
		ia[nz] = i;
		a[nz] = ad[i][j];
		nz++;
	    }
	}
    }
    ka[n] = nz;

    REINTEGER(ia, nz);
    REDOUBLE(a, nz);

    kp = &xxx;

    kp->m = m;
    kp->n = n;
    kp->nz = nz;
    kp->a = a;
    kp->ia = ia;
    kp->ka = ka;
    kp->b = b;
    kp->c = c;
    kp->f = f;
    kp->r = r;
    kp->l = l;
    kp->u = u;

    DOUBLE(kp->x, n);
    DOUBLE(kp->y, m);
    DOUBLE(kp->rc, n);

    kp->max = maxflag;
    kp->inftol = inftol;
    kp->sf_req = sf_req;
    kp->v = v;
    kp->split = split;

    kp->method = PRIMAL;

    printf("m=%d n=%d\n", kp->m, kp->n);

    status = optlp(kp);

    if (status == 0) {
	for (i = 0; i < m; i++)
	    y[i] = kp->y[i];
	for (i = 0; i < n; i++) {
	    rc[i] = kp->rc[i];
	    x[i] = kp->x[i];
	}
    }
    /* status = optstd(m,n,nz,ia,ka,a,b,c,f,bndmark,ub, x,y,r,
     * maxflag,inftol,sf_req,v,split); */

    FREE(kp->x);
    FREE(kp->y);
    FREE(kp->rc);
    FREE(kp->r);
    FREE(kp->l);
    FREE(kp->u);
    FREE(a);
    FREE(ia);
    FREE(ka);

    return status;
}

/*
int 	optdense(m,n,ad,b,c,f,
	       x,y,r,
	       maxflag,inftol,sf_req,v,split)
int m, n, maxflag, sf_req, v, split;
double **ad, *b, *c, f, *x, *y, *r, inftol;
{
	int i, j, nz=0, *ia, *ka, status, *bndmark;
	double *a, *ub;

	INTEGER( bndmark, n );
	DOUBLE(  ub,      n );
	INTEGER( ia, m*n );
	INTEGER( ka, n+1 );
	DOUBLE(   a, m*n );

	for (j=0; j<n; j++) {
		bndmark[j] = 0;
		ub[j]      = HUGE;
	}

	for (j=0; j<n; j++) {
		ka[j] = nz;
		for (i=0; i<m; i++) {
			if ( ad[i][j] != 0.0 ) {
				ia[nz] = i;
				a[nz] = ad[i][j];
				nz++;
			}
		}
	}
	ka[n] = nz;

	REINTEGER( ia, nz );
	REDOUBLE(   a, nz );

	status = optstd(m,n,nz,ia,ka,a,b,c,f,bndmark,ub,
			x,y,r,
			maxflag,inftol,sf_req,v,split);

	FREE(a); FREE(ia); FREE(ka); FREE(bndmark); FREE(ub);

	return status;
}
*/

/*
int 	optstd_(pm,pn,pnz,ia,ka,a,b,c,pf,
		x,y,r,
		pmaxflag,pinftol,psf_req,pv,psplit)
int *pm, *pn, *pnz, *ia, *ka, *pmaxflag, *psf_req, *pv, *psplit;
double *a, *b, *c, *pf, *x, *y, *r, *pinftol;
{
	return optstd(*pm,*pn,*pnz,ia,ka,a,b,c,*pf,
			x,y,r,
			*pmaxflag,*pinftol,*psf_req,*pv,*psplit);
}

int 	optmpsp_(pm,pn,ia,ka,a,b,c,pf,r,l,u,
	       x,y,rc,
	       pmaxflag,pinftol,psf_req,pv,psplit
	       )
int 	*pm,*pn,*ia,*ka,*pmaxflag,*psf_req,*pv,*psplit;
double 	*a,*b,*c,*pf,*r,*l,*u,*x,*y,*rc,*pinftol;
{
	return optmpsp(*pm,*pn,ia,ka,a,b,c,*pf,r,l,u,
	       x,y,rc,
	       *pmaxflag,*pinftol,*psf_req,*pv,*psplit
	       );
}
*/
