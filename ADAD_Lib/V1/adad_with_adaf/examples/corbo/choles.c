#include "lp.h"

#define EPSSOL 1.0e-5			   /* Zero tolerance for consistent
					    * eqns w/dep rows */
#define NOREORD 0
#define MD  1
#define MLF 2

static void     lltnum(), adat();
static void     qksort(), swap();
static void     hrise(), hfall(), hcheck(), lfcheck();

static int     *kaat, *iaat, *mark, *perm, *iperm;
static double  *aat, *aatd;

void            inv_sym(m, n, ka, ia, kat, iat, v)
    int             m, n, *ka, *ia, *kat, *iat, v;
{
    register int    kk, tag, lf, deg, nbr_deg, nbr, nbr2, nbr3;

    int             i, k, kkk, row, col, node, i2, ii, iii, cnt, nz, ni,
                    nd, aatnz, lnz, memfree = 0, heapnum, cur, method = MLF;

    register int  **nbrs, *degree, *spc, *locfil, *iwork, *iwork2;

    int            *node_nbrs, *nbr_nbrs, *dst, *hkey, *heap, *iheap;

    double          nadat, narth;

    /*---------------------------------------------------------+
    | allocate space for perm and iperm.                      */

    INTEGER(perm, m);
    INTEGER(iperm, m);

    /*---------------------------------------------------------+
    | allocate space for work arrays.                         */

    INTEGER(degree, m);
    INTEGER(dst, m);
    INTEGER(spc, m);
    INTEGER(locfil, m);
    INTEGER(hkey, m);
    INTEGER(heap, m);
    INTEGER(iheap, m);
    INTEGER(iwork, m);
    INTEGER(iwork2, m);

    heap--;				   /* so that indexing starts from 1 */

    /*---------------------------------------------------------+
    | count number of neighbors for each node in the graph     |
    | of AAt                                                  */

    for (i = 0; i < m; i++) {
	iwork[i] = -1;
	degree[i] = 0;
    }
    for (i = 0; i < m; i++) {
	for (k = kat[i]; k < kat[i + 1]; k++) {
	    col = iat[k];
	    for (kk = ka[col]; kk < ka[col + 1]; kk++) {
		row = ia[kk];
		if (row > i)
		    if (iwork[row] < i) {
			iwork[row] = i;

			degree[i]++;
			degree[row]++;
		    }
	    }
	}
    }

    /*---------------------------------------------------------+
    | calculate the number of nonzeros in AAt.                */

    aatnz = 0;
    for (i = 0; i < m; i++)
	aatnz += degree[i];
    aatnz = aatnz / 2;
    lnz = aatnz;

    /*---------------------------------------------------------+
    | allocate enough space to store AAt (without any fillin) */

    INTEGER(kaat, m + 1);
    INTEGER(iaat, aatnz);

    if ((nbrs = (int **) malloc((unsigned) m * sizeof(int *))) == NULL) {
	printf("cannot allocate space for %d bytes\n", (int) m*sizeof(int *));
	exit(10);
    }
    for (i = 0; i < m; i++) {
	spc[i] = degree[i];
	INTEGER(nbrs[i], spc[i]);
    }

    /*---------------------------------------------------------+
    | initialize nbrs to contain the adjacency structure of    |
    | AAt.                                                    */

    for (i = 0; i < m; i++) {
	iwork[i] = -1;
	degree[i] = 0;
    }
    for (i = 0; i < m; i++) {
	for (k = kat[i]; k < kat[i + 1]; k++) {
	    col = iat[k];
	    for (kk = ka[col]; kk < ka[col + 1]; kk++) {
		row = ia[kk];
		if (row > i)
		    if (iwork[row] < i) {
			iwork[row] = i;

			nbrs[row][degree[row]] = i;
			degree[row]++;

			nbrs[i][degree[i]] = row;
			degree[i]++;
		    }
	    }
	}
    }

    /*---------------------------------------------------------+
    | miscellaneous initializations.                          */

    for (i = 0; i < m; i++) {
	iperm[i] = -1;
	iwork[i] = 0;
	iwork2[i] = -1;
    }

    tag = 0;
    nz = 0;
    i = 0;
    kaat[0] = 0;

    /*---------------------------------------------------------+
    |  compute local fill for each node			  */

    if (method == MLF) {
	for (node = 0; node < m; node++) {
	    deg = degree[node];
	    lf = 0;
	    node_nbrs = nbrs[node];
	    for (k = 0; k < deg; k++) {
		nbr = node_nbrs[k];
		nbr_nbrs = nbrs[nbr];
		nbr_deg = degree[nbr];
		tag++;
		for (kk = 0; kk < nbr_deg; kk++) {
		    iwork[nbr_nbrs[kk]] = tag;
		}
		for (kk = k + 1; kk < deg; kk++) {
		    if (iwork[node_nbrs[kk]] != tag)
			lf++;
		}
	    }
	    locfil[node] = lf;
	}
    }
    /*---------------------------------------------------------+
    | hkey encodes the tie-breaking rule - currently the rule  |
    | is somewhat random.  to make it first occuring minimum,  |
    | change the formula to:                                   |
    |       hkey[node] = degree[node]*m + node;                |
    | warning: with this definition of hkey, there is the      |
    | possibility of integer overflow on moderately large      |
    | problems.                                                |
    |                                                         */

    for (node = 0; node < m; node++) {
	if (method == MLF)
	    hkey[node] = locfil[node];
	else if (method == MD)
	    hkey[node] = degree[node];
	else
	    hkey[node] = node;
    }

    /*---------------------------------------------------------+
    | set up heap structure for quickly accessing minimum.    */

    heapnum = m;
    for (node = m - 1; node >= 0; node--) {
	cur = node + 1;
	iheap[node] = cur;
	heap[cur] = node;
	hfall(heapnum, hkey, iheap, heap, cur);
    }

    /*---------------------------------------------------------+
    | the min degree ordering loop                             |
    | (modified to perform mass elimination of                 |
    | indistinguishable nodes).                               */

    while (i < m) {

	/* compute min degree and find node achieving the min */

	node = heap[1];
	deg = degree[node];

	/* mark nodes for elimination: the min degree node and any node
	 * 'indistinguishable' from it */

	perm[i] = node;
	iperm[node] = i;

	nd = 0;
	i2 = i + 1;
	node_nbrs = nbrs[node];
	for (k = 0; k < deg; k++)
	    iperm[node_nbrs[k]] = i;
	for (k = 0; k < deg; k++) {
	    nbr = node_nbrs[k];
	    if (degree[nbr] == deg) {
		nbr_nbrs = nbrs[nbr];
		for (kk = 0; kk < deg; kk++)
		    if (iperm[nbr_nbrs[kk]] < i)
			break;
		if (kk == deg) {
		    perm[i2] = nbr;
		    iperm[nbr] = i2;
		    i2++;
		} else {
		    dst[nd] = nbr;
		    nd++;
		}
	    } else {
		dst[nd] = nbr;
		nd++;
	    }
	}

	/* reallocate space for iaat as necessary */

	ni = i2 - i - 1;		   /* number of indistinguishable
					    * nodes */

	cnt = nz + (deg * (deg + 1) - (deg - ni - 1) * (deg - ni)) / 2;
	if (cnt > lnz) {
	    lnz = cnt;
	    REINTEGER(iaat, lnz);
	}
	/* copy adjacency lists in iaat, kaat */

	for (ii = i; ii < i2; ii++) {
	    kaat[ii + 1] = kaat[ii] + deg;

	    for (iii = ii + 1; iii < i2; iii++) {
		iaat[nz] = perm[iii];
		nz++;
	    }
	    for (k = 0; k < nd; k++) {
		iaat[nz] = dst[k];
		nz++;
	    }
	    deg--;
	}

	/* decrement degrees for each distinguishable neighbor of 'node'
	 * corresponding to the removal of 'node' and the indistinguishable
	 * neighbors */

	ni = i2 - i;			   /* number of indistinguishable
					    * nodes */

	node = perm[i];
	for (k = 0; k < nd; k++) {
	    nbr = dst[k];
	    nbr_nbrs = nbrs[nbr];
	    degree[nbr]--;
	    nbr_deg = degree[nbr];
	    for (kk = 0; nbr_nbrs[kk] != node; kk++);
	    for (; kk < nbr_deg; kk++)
		nbr_nbrs[kk] = nbr_nbrs[kk + 1];
	}
	if (i2 > i + 1) {
	    for (k = 0; k < nd; k++) {
		nbr = dst[k];
		nbr_nbrs = nbrs[nbr];
		nbr_deg = degree[nbr];
		cnt = 0;
		for (kk = 0; kk < nbr_deg; kk++) {
		    if (iperm[nbr_nbrs[kk]] > i)
			cnt++;
		    else
			nbr_nbrs[kk - cnt] = nbr_nbrs[kk];
		}
		degree[nbr] -= cnt;
	    }
	}
	for (ii = i; ii < i2; ii++) {
	    int             okey;

	    node = perm[ii];

	    cur = iheap[node];
	    okey = hkey[heap[cur]];
	    heap[cur] = heap[heapnum];
	    iheap[heap[cur]] = cur;
	    heapnum--;
	    if (okey < hkey[heap[cur]])
		hfall(heapnum, hkey, iheap, heap, cur);
	    else
		hrise(hkey, iheap, heap, cur);

	    FREE(nbrs[node]);
	    memfree += spc[node];
	}

	/* add links: between each pair of distinguishable nodes adjacent to
	 * min-deg node which don't already have a link */

	if (method != MLF || locfil[perm[i]] > 0) {
	    if (nd > 1)
		cnt = memfree / (nd * (nd - 1));
	    for (k = 0; k < nd; k++) {
		nbr = dst[k];
		nbr_deg = degree[nbr];
		nbr_nbrs = nbrs[nbr];
		tag++;
		for (kk = 0; kk < nbr_deg; kk++) {
		    iwork[nbr_nbrs[kk]] = tag;
		}
		for (kk = k + 1; kk < nd; kk++) {
		    nbr2 = dst[kk];
		    if (iwork[nbr2] != tag) {
			int             ne, cnt2;

			if (method == MLF) {
			    cnt2 = 0;
			    ne = degree[nbr2];
			    for (kkk = 0; kkk < ne; kkk++) {
				nbr3 = nbrs[nbr2][kkk];
				if (iwork[nbr3] == tag) {
				    locfil[nbr3]--;
				    hkey[nbr3] = locfil[nbr3];
				    hrise(hkey, iheap, heap, iheap[nbr3]);
				    cnt2++;
				}
			    }
			    locfil[nbr] += degree[nbr] - cnt2;
			    locfil[nbr2] += degree[nbr2] - cnt2;
			}
			ne = degree[nbr];
			if (ne >= spc[nbr]) {
			    spc[nbr] += cnt + 1;
			    memfree -= cnt;
			    REINTEGER(nbrs[nbr], spc[nbr]);
			}
			nbrs[nbr][ne] = nbr2;
			degree[nbr]++;
			if (method == MLF)
			    iwork[nbr2] = tag;

			ne = degree[nbr2];
			if (ne >= spc[nbr2]) {
			    spc[nbr2] += cnt + 1;
			    memfree -= cnt;
			    REINTEGER(nbrs[nbr2], spc[nbr2]);
			}
			nbrs[nbr2][ne] = nbr;
			degree[nbr2]++;
		    }
		}
	    }
	}
	/* adjust heap */

	for (k = 0; k < nd; k++) {
	    nbr = dst[k];
	    if (method == MLF) {
		locfil[nbr] -= ni * (degree[nbr] - nd + 1);
		hkey[nbr] = locfil[nbr];
	    } else if (method == MD) {
		hkey[nbr] = degree[nbr];
	    } else {
		hkey[nbr] = nbr;
	    }
	    hrise(hkey, iheap, heap, iheap[nbr]);
	    hfall(heapnum, hkey, iheap, heap, iheap[nbr]);
	}

	i = i2;
    }

    heap++;
    FREE(degree);
    FREE(dst);
    FREE(spc);
    FREE(locfil);
    FREE(hkey);
    FREE(heap);
    FREE(iheap);
    FREE(iwork);
    FREE(iwork2);
    FREE(nbrs);

    for (k = 0; k < kaat[m]; k++)
	iaat[k] = iperm[iaat[k]];

    for (i = 0; i < m; i++)
	qksort(iaat, kaat[i], kaat[i + 1] - 1);

    /*---------------------------------------------------------+
    | calculate and print statistics.                         */

    nadat = 0.0e0;
    for (i = 0; i < n; i++) {
	k = ka[i + 1] - ka[i];
	nadat += k * k;
    }
    nadat = nadat + 2 * ka[n];

    narth = 0.0e0;
    for (i = 0; i < m; i++) {
	k = kaat[i + 1] - kaat[i];
	narth += (double) k *k;
    }
    narth = narth + 3 * kaat[m] + m;

    lnz = kaat[m];
    if (v) {
	printf(" nonzeros in ADAt        : %18d\n", aatnz);
	printf(" nonzeros in L           : %18d\n", lnz);
	printf(" arith ops to form ADAt  : %18.0f\n", nadat);
	printf(" arith ops to factor ADAt: %18.0f\n\n", narth);
	fflush(stdout);
    }
    /*---------------------------------------------------------+
    | allocate remaining storage.                             */

    DOUBLE(aat, lnz);
    DOUBLE(aatd, m);
    INTEGER(mark, m);
}

void            inv_num(m, ka, ia, a, d2, kat, iat, at, v)
    int             m, *ka, *ia, *kat, *iat, v;
    double         *a, *d2, *at;
{
    int             i, ndep;

    /*----------------------------------------------+
    |               2 t        t                    |
    | calculate   AD A   = LD'L                     |
    |                                              */

    adat(m, ka, ia, a, d2, kat, iat, at);
    for (i = 0; i < m; i++)
	mark[i] = TRUE;
    lltnum(m, iaat, kaat, aat, aatd, mark, &ndep);
    if (v && ndep > 0)
	printf("     dependent  rows:    %d\n", ndep);
}

int             solve(m, y)
    int             m;
    double         *y;
{
    register int    i, consistent = TRUE;
    register int    k, row;
    register double beta, *dwork;

    DOUBLE(dwork, m);

    for (i = 0; i < m; i++)
	dwork[i] = y[i];
    for (i = 0; i < m; i++)
	y[iperm[i]] = dwork[i];

    /*------------------------------------------------------+
    |                                                       |
    |               -1                                      |
    |       y  <-  L  y                                     |
    |                                                      */

    for (i = 0; i < m; i++) {
	if (mark[i]) {
	    y[i] = y[i] / aatd[i];
	    beta = y[i];
	    for (k = kaat[i]; k < kaat[i + 1]; k++) {
		row = iaat[k];
		y[row] -= aat[k] * beta;
	    }
	} else {
	    if (fabs(y[i]) > EPSSOL)
		consistent = FALSE;
	}
    }

    /*------------------------------------------------------+
    |                                                       |
    |                t -1                                   |
    |       y  <-  (L )  y                                  |
    |                                                      */

    for (i = m - 1; i >= 0; i--) {
	if (mark[i]) {
	    beta = y[i];
	    for (k = kaat[i]; k < kaat[i + 1]; k++) {
		beta -= aat[k] * y[iaat[k]];
	    }
	    y[i] = beta / aatd[i];
	} else {
	    if (fabs(y[i]) > EPSSOL)
		consistent = FALSE;
	}
    }

    for (i = 0; i < m; i++)
	dwork[i] = y[i];
    for (i = 0; i < m; i++)
	y[perm[i]] = dwork[i];

    FREE(dwork);

    return (consistent);
}

static void     adat(m, ka, ia, a, d2, kat, iat, at)
    int             m, *ka, *ia, *kat, *iat;
    double         *a, *d2, *at;
{
    register int    i, kkk, kk, k, col, row1, row2;
    register int   *imark;
    double          diag, beta;

    INTEGER(imark, m);

    for (k = 0; k < kaat[m]; k++)
	aat[k] = 0.0e0;

    for (i = 0; i < m; i++) {
	row1 = iperm[i];
	diag = 0.0e0;
	for (kkk = kaat[row1]; kkk < kaat[row1 + 1]; kkk++)
	    imark[iaat[kkk]] = kkk;
	for (k = kat[i]; k < kat[i + 1]; k++) {
	    col = iat[k];
	    beta = at[k] * d2[col];
	    diag = diag + at[k] * beta;
	    for (kk = ka[col]; kk < ka[col + 1]; kk++) {
		row2 = iperm[ia[kk]];
		if (row2 > row1) {
		    kkk = imark[row2];
		    aat[kkk] += a[kk] * beta;
		}
	    }
	}
	aatd[iperm[i]] = diag;
    }
    FREE(imark);

}

static void     lltnum(m, iaat, kaat, aat, aatd, mark, pndep)
    int             m, *pndep;
    register int   *iaat;
    int            *kaat, *mark;
    register double *aat;
    double         *aatd;
{
    int            *first, *link, i, j, newj, k, k_bgn, row;
    register int    kk, k_end;
    register double lij, *temp;
    double          diag;

    /*------------------------------------------------------+
    |                            2                          |
    | the input is the matrix  AD A  stored sparsely in     |
    |       kaat,iaat,aat.                                  |
    | the output is the lower triangular matrix  L          |
    |       stored sparsely in  kaat,iaat,aat  and          |
    |       a diagonal matrix  D'  stored in aatd.          |
    |                                                       |
    |         2         t                                   |
    |       AD A  = LD'L                                    |
    |                                                       |
    +------------------------------------------------------*/

    /*------------------------------------------------------+
    | initialize constants                                 */

    *pndep = 0;

    DOUBLE0(temp, m);
    INTEGER(first, m);
    INTEGER(link, m);
    for (i = 0; i < m; i++)
	link[i] = -1;

    /*------------------------------------------------------+
    | begin main loop                                      */

    for (i = 0; i < m; i++) {
	diag = 0.0;
	for (j = link[i]; j != -1; j = newj) {
	    newj = link[j];
	    k = first[j];
	    lij = aat[k];
	    diag += lij * lij;
	    k_bgn = k + 1;
	    k_end = kaat[j + 1];
	    if (k_bgn < k_end) {
		first[j] = k_bgn;
		row = iaat[k_bgn];
		link[j] = link[row];
		link[row] = j;
		for (kk = k_bgn; kk < k_end; kk++)
		    temp[iaat[kk]] += lij * aat[kk];
	    }
	}
	diag = aatd[i] - diag;
	if (diag <= 0.0) {
	    (*pndep)++;
	    mark[i] = 0;
	    diag = 0.0;
	}
	diag = sqrt(diag);
	aatd[i] = diag;
	k_bgn = kaat[i];
	k_end = kaat[i + 1];
	if (k_bgn < k_end) {
	    first[i] = k_bgn;
	    row = iaat[k_bgn];
	    link[i] = link[row];
	    link[row] = i;
	    for (kk = k_bgn; kk < k_end; kk++) {
		row = iaat[kk];
		if (mark[i])
		    aat[kk] = (aat[kk] - temp[row]) / diag;
		else
		    aat[kk] = 0.0;
		temp[row] = 0.0;
	    }
	}
    }
    FREE(link);
    FREE(first);
    FREE(temp);
}

void            inv_clo()
{
    FREE(perm);
    FREE(iperm);
    FREE(iaat);
    FREE(kaat);
    FREE(mark);
    FREE(aat);
    FREE(aatd);
}

/*  *** qksort: sort v[left]...v[right] into increasing order ***
	reference: The C Programming Language,
		   Kernighan and Ritchie
		   2nd. edition, page 87.  */

static void     qksort(v, left, right)
    int            *v, left, right;
{
    int             i, last;

    if (left >= right)
	return;				   /* do nothing if array contains
					    * fewer than two elements */

    swap(v, left, (left + right) / 2);	   /* move partition elem */
    last = left;			   /* to v[left] */
    for (i = left + 1; i <= right; i++)	   /* partition */
	if (v[i] < v[left])
	    swap(v, ++last, i);
    swap(v, left, last);		   /* restore partition elem */
    qksort(v, left, last - 1);
    qksort(v, last + 1, right);
}

/*  *** swap: interchange v[i] and v[j] */

static void     swap(v, i, j)
    int            *v, i, j;
{
    int             temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

static void     hfall(heapnum, key, iheap, heap, cur)
    int             heapnum, *key, *iheap, *heap, cur;
{
    int             child;

    child = 2 * cur;
    while (child <= heapnum) {
	if (child < heapnum &&
	    key[heap[child + 1]] < key[heap[child]])
	    child++;
	if (key[heap[cur]] > key[heap[child]]) {
	    swap(heap, cur, child);
	    swap(iheap, heap[cur], heap[child]);
	    cur = child;
	    child = 2 * cur;
	} else
	    break;
    }
}

static void     hrise(key, iheap, heap, cur)
    int            *key, *iheap, *heap, cur;
{
    int             parent;

    parent = cur / 2;
    while (parent > 0) {
	if (key[heap[parent]] > key[heap[cur]]) {
	    swap(heap, cur, parent);
	    swap(iheap, heap[cur], heap[parent]);
	    cur = parent;
	    parent = cur / 2;
	} else
	    break;
    }
}

static void     hcheck(cnt, heapnum, key, iheap, heap)
    int             cnt, heapnum, *key, *iheap, *heap;
{
    int             cur, parent;

    for (cur = heapnum; cur > 1; cur--) {
	parent = cur / 2;
	if (key[heap[cur]] < key[heap[parent]]) {
	    printf("%d: key[heap[%d]] = %d, key[heap[%d]] = %d\n",
		   cnt, cur, key[heap[cur]],
		   parent, key[heap[parent]]);
	}
    }
    for (cur = 1; cur <= heapnum; cur++) {
	if (iheap[heap[cur]] != cur) {
	    printf("%d: heap[%d] = %d, iheap[%d] = %d\n",
		   cnt, cur, heap[cur],
		   heap[cur], iheap[heap[cur]]);
	}
    }
}

static void     lfcheck(cnt, m, heapnum, locfil, heap, nbrs, degree)
    int             cnt, m, heapnum, *locfil, *heap, **nbrs, *degree;
{
    int             cur, deg, node, lf, k, nbr, nbr_deg, tag, kk;
    int            *node_nbrs, *nbr_nbrs, *iwork;

    INTEGER0(iwork, m);
    tag = 0;
    for (cur = 1; cur <= heapnum; cur++) {
	node = heap[cur];
	deg = degree[node];
	lf = 0;
	node_nbrs = nbrs[node];
	for (k = 0; k < deg; k++) {
	    nbr = node_nbrs[k];
	    nbr_nbrs = nbrs[nbr];
	    nbr_deg = degree[nbr];
	    tag++;
	    for (kk = 0; kk < nbr_deg; kk++) {
		iwork[nbr_nbrs[kk]] = tag;
	    }
	    for (kk = k + 1; kk < deg; kk++) {
		if (iwork[node_nbrs[kk]] != tag)
		    lf++;
	    }
	}
	if (lf != locfil[node])
	    printf("%4d: node = %4d lf = %4d locfil = %4d\n",
		   cnt, node, lf, locfil[node]);
    }

    FREE(iwork);
}

/*  DEBUG CODE FOR MIN LOC FIL *******************
for (cur=1; cur<=heapnum; cur++) {
	node = heap[cur];
	printf("node=%3d; degree=%3d; locfil=%3d nbrs=",
		node,degree[node],locfil[node]);
	for (k=0; k<degree[node]; k++) printf("%3d  ",nbrs[node][k]);
	printf("\n"); fflush(stdout);
}
 *************************************** */
