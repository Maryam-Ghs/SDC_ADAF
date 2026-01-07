#include "lp.h"

static void     hrise(), hfall(), swap();
static int      colcmp();

main(argc, argv)
    int             argc;
    char           *argv[];
{
    CORBO          *kp, *openlp();

    kp = openlp();
    if (kp == NULL) {
	fprintf(stderr, "cannot open another LP problem\n");
	exit(1);
    }
    argc--;
    argv++;

    readlp(argc, argv, kp);

    colmatch(kp);

    closelp(kp);
}

int             colmatch(kp)
    CORBO          *kp;
{
    int             m, n, nz, *ia, *ka, maxflag, v;
    double         *a, *b, *c, f, *r, *l, *u, *x, *y, *rc, inftol;
    char          **rowlab, **collab;

    int            *heap, *iheap, cur, heapnum;

    int             i, oj, j, k;
    int             nummatches = 0;

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
    v = kp->v;
    collab = kp->collab;
    rowlab = kp->rowlab;

    INTEGER(heap, n);
    INTEGER(iheap, n);

    heap--;

    /*--------------------------------------------------------+
    | initialize heap                                        */

    heapnum = n;
    for (j = n - 1; j >= 0; j--) {
	cur = j + 1;
	iheap[j] = cur;
	heap[cur] = j;
	hfall(heapnum, kp, iheap, heap, cur);
    }

    oj = -1;
    while (heapnum > 0) {
	j = heap[1];

	if (colcmp(oj, j, kp) == 0) {
	    nummatches++;
	    printf("%8s\n          ", collab[oj]);
	    for (k = ka[oj]; k < ka[oj + 1]; k++) {
		printf("%8s  ", rowlab[ia[k]]);
	    }
	    printf("\n");
	    printf("%8s\n          ", collab[j]);
	    for (k = ka[j]; k < ka[j + 1]; k++) {
		printf("%8s  ", rowlab[ia[k]]);
	    }
	    printf("\n\n");
	}
	cur = iheap[j];
	oj = heap[cur];
	heap[cur] = heap[heapnum];
	iheap[heap[cur]] = cur;
	heapnum--;
	if (colcmp(oj, heap[cur], kp) < 0)
	    hfall(heapnum, kp, iheap, heap, cur);
	else
	    hrise(kp, iheap, heap, cur);

	oj = j;
    }
    printf("number of matches = %d\n", nummatches);
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

static void     hfall(heapnum, kp, iheap, heap, cur)
    int             heapnum, *iheap, *heap, cur;
    CORBO          *kp;
{
    int             child;

    child = 2 * cur;
    while (child <= heapnum) {
	if (child < heapnum &&
	    colcmp(heap[child + 1], heap[child], kp) < 0)
	    child++;
	if (colcmp(heap[cur], heap[child], kp) > 0) {
	    swap(heap, cur, child);
	    swap(iheap, heap[cur], heap[child]);
	    cur = child;
	    child = 2 * cur;
	} else
	    break;
    }
}

static void     hrise(kp, iheap, heap, cur)
    CORBO          *kp;
    int            *iheap, *heap, cur;
{
    int             parent;

    parent = cur / 2;
    while (parent > 0) {
	if (colcmp(heap[parent], heap[cur], kp) > 0) {
	    swap(heap, cur, parent);
	    swap(iheap, heap[cur], heap[parent]);
	    cur = parent;
	    parent = cur / 2;
	} else
	    break;
    }
}

static int      colcmp(j1, j2, kp)
    int             j1, j2;
    CORBO          *kp;
{
    int            *ia = kp->ia, *ka = kp->ka;
    double         *a = kp->a, *c = kp->c;

    int             k1, k2, m1, m2;

    double          a1, a2, eps = 1.0e-3;

    if (j1 < 0)
	return (-1);
    if (j2 < 0)
	return (1);

    m1 = ka[j1 + 1] - ka[j1];
    m2 = ka[j2 + 1] - ka[j2];

    if (m1 < m2)
	return (-1);
    if (m1 > m2)
	return (1);

    for (k1 = ka[j1], k2 = ka[j2]; k1 < ka[j1 + 1]; k1++, k2++) {
	if (ia[k1] < ia[k2])
	    return (-1);
	if (ia[k1] > ia[k2])
	    return (1);
    }

    a1 = a[ka[j1]];
    a2 = a[ka[j2]];
    for (k1 = ka[j1] + 1, k2 = ka[j2] + 1; k1 < ka[j1 + 1]; k1++, k2++) {
	if ((a[k1] / a1) / (a[k2] / a2) < 1.0 - eps)
	    return (-1);
	if ((a[k1] / a1) / (a[k2] / a2) > 1.0 + eps)
	    return (1);
    }

    if ((c[j1] / a1) < (c[j2] / a2) - eps)
	return (-1);
    if ((c[j1] / a1) > (c[j2] / a2) + eps)
	return (1);

    return (0);
}
