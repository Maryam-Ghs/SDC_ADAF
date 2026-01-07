#include "lp.h"

static int      hashsize, theta;
static NLIST  **hashtab;		   /* pointer table for labels */

static int      newstate(), *intdup();
static void     error(), warn(), identify();
static unsigned hash();

static char    *my_strstr(s, t)
    char           *s, *t;
{
    register char  *p, *q, *r;

    for (p = s; *p != '\0'; p++) {
	for (q = p, r = t; *r != '\0' && *q == *r; q++, r++);
	if (r != t && *r == '\0')
	    return p;
    }
    return (char *) NULL;
}

CORBO          *openlp()
{
    CORBO          *kp;

    for (kp = _lpb; kp < _lpb + LP_OPEN_MAX; kp++) {
	if (kp->flag == 0) {
	    kp->flag = 1;
	    kp->name[0] = '\0';
	    kp->obj[0] = '\0';
	    kp->rhs[0] = '\0';
	    kp->bounds[0] = '\0';
	    kp->ranges[0] = '\0';

	    return kp;
	}
    }
    return NULL;
}

void            closelp(kp)
    CORBO          *kp;
{
    kp->flag = 0;
}

void            readlp(argc, argv, kp)
    int             argc;
    char           *argv[];
    CORBO          *kp;
{
    int             m, n, nz, *ia, *ka, maxflag, sf_req, v, split, method,
                   *varsgn;
    double         *a, *b, *c, f = 0.0, *r, *l, *u, inftol;
    char          **rowlab, **collab;
    static char     name[15] = "", obj[11] = "", rhs[11] = "", bounds[11] = "", ranges[11] = "";

    int             row, i, j, k, kk, argno;
    FILE           *fp;
    NLIST          *np;
    char            line[80], str[12], s[2][11];
    char           *type, *label0, *label1, *label2, *valstr1, *valstr2;
    int             len = 0, state = HEADER;
    int             m2, n2, nz2;
    int            *mark, *iat, *kat;
    double          value;
    double         *at;

    int             nkeys = 12;
    static char    *key_word[] = {"MAX", "SIGFIG", "INFTOL", "MIN",
	"OBJ", "RHS", "RANGES", "BOUNDS",
	"DUAL", "PRIMAL", "VERBOSE",
    "SPLIT"};
    static char    *label[] = {
	"Maximize (MAX)",
	"Significant digits (SIGFIG).................",
	"Feasibility tolerance (INFTOL)..............",
	"Minimize (MIN)",
	"Objective vector (OBJ)......................",
	"Right hand side (RHS).......................",
	"Ranges (RANGES).............................",
	"Bounds (BOUNDS).............................",
	"Solve dual as primal (DUAL)",
	"Solve primal as primal (PRIMAL)",
	"Verbosity level (VERBOSE)...................",
	"Split Columns Threshold (SPLIT)............."
    };

    char           *fmt = "%s \n", *fmts = "%s %s \n", *fmte = "%s %e \n", *fmtd = "%s %d \n";

    /* initialize parameters */

    m = 0;
    n = 0;
    nz = 0;
    maxflag = 1;			   /* max = -1,   min = 1 */
    method = UNSET;
    sf_req = 8;				   /* significant figures requested */
    v = 1;				   /* verbosity level */
    split = 0;				   /* split columns threshold (0=off) */
    inftol = 1.0e-6;			   /* infeasibility requested */

    /*---------------------------------------------------------+
    |	compute number of bytes in input files            */

    for (argno = 0; argno < argc; argno++) {
	struct stat     buf;
	if (stat(argv[argno], &buf) != NULL)
	    error(2, argv[argno]);
	len = len + buf.st_size;
    }

    hashsize = len / 17;
    theta = 0.3874576628 * hashsize;
    m2 = len / 100 + 1;
    n2 = len / 100 + 1;
    nz2 = len / 100 + 1;
    if ((hashtab = (NLIST **) calloc((unsigned) hashsize, sizeof(*hashtab)))
	== NULL) {
	printf("Cannot allocate %d bytes for hash-table\n", hashsize*sizeof(*hashtab));
	error(6, "");
}

    INTEGER(mark, m2);
    INTEGER(ia, nz2);
    INTEGER(ka, n2);
    DOUBLE(a, nz2);
    DOUBLE(r, m2);
    STRING(rowlab, m2);
    STRING(collab, n2);

    type = line + 1;
    label0 = line + 4;
    label1 = line + 14;
    valstr1 = line + 24;
    label2 = line + 39;
    valstr2 = line + 49;
    s[0][10] = '\0';
    s[1][10] = '\0';
    line[79] = '\0';

    for (argno = 0; argno < argc; argno++) {
	if ((fp = fopen(argv[argno], "r")) == NULL)
	    error(2, argv[argno]);

	while (fgets(line, 80, fp) != NULL) {

	    len = strlen(line);
	    for (j = len - 1; j < 79; j++)
		line[j] = ' ';
	    if (state != HEADER) {
		line[3] = '\0';
		line[12] = '\0';
		line[22] = '\0';
		line[36] = '\0';
		line[47] = '\0';
		line[61] = '\0';
	    }
	    switch (state) {
	      case HEADER:
		sscanf(line, "%s%s", s[0], s[1]);
		if (strncmp(s[0], "NAME", 4) == 0) {
		    strncpy(name, s[1], 10);
		    state = NAME;
		} else {
		    for (i = 0; i < nkeys; ++i) {
			if (strncmp(s[0], key_word[i], 3) == 0) {
			    switch (i) {
			      case 0:
				maxflag = -1;
				printf(fmt, label[0]);
				fflush(stdout);
				break;
			      case 1:
				sf_req = atoi(s[1]);
				printf(fmtd, label[1], sf_req);
				fflush(stdout);
				break;
			      case 2:
				inftol = atof(s[1]);
				printf(fmte, label[2], inftol);
				fflush(stdout);
				break;
			      case 3:
				maxflag = 1;
				printf(fmt, label[3]);
				fflush(stdout);
				break;
			      case 4:
				strncpy(obj, s[1], 10);
				printf(fmts, label[4], obj);
				fflush(stdout);
				break;
			      case 5:
				strncpy(rhs, s[1], 10);
				printf(fmts, label[5], rhs);
				fflush(stdout);
				break;
			      case 6:
				strncpy(ranges, s[1], 10);
				printf(fmts, label[6], ranges);
				fflush(stdout);
				break;
			      case 7:
				strncpy(bounds, s[1], 10);
				printf(fmts, label[7], bounds);
				fflush(stdout);
				break;
			      case 8:
				method = DUAL;
				printf(fmt, label[8]);
				fflush(stdout);
				break;
			      case 9:
				method = PRIMAL;
				printf(fmt, label[9]);
				fflush(stdout);
				break;
			      case 10:
				v = atoi(s[1]);
				if (v == 9)
				    identify();
				printf(fmtd, label[10], v);
				fflush(stdout);
				break;
			      case 11:
				split = atoi(s[1]);
				printf(fmtd, label[11], split);
				fflush(stdout);
				break;
			    }
			}
		    }
		}
		break;
	      case NAME:
		if (strcmp(line, "ROW") == 0)
		    state = ROWS;
		else
		    warn(20, line);
		break;
	      case ROWS:
		if (line[0] != ' ') {
		    if (strcmp(line, "COL") == 0) {
			state = COLS;
			DOUBLE0(b, m);
		    } else
			warn(21, type);
		} else {
		    switch (type[0] == ' ' ? type[1] : type[0]) {
		      case 'L':
			r[m] = HUGE;
			mark[m] = 0;
			break;
		      case 'E':
			r[m] = 0.0;
			mark[m] = 0;
			break;
		      case 'G':
			r[m] = HUGE;
			mark[m] = 1;
			break;
		      case 'N':
			if (obj[0] == '\0')
			    strncpy(obj, label0, 10);
			if (my_strstr(label0, obj) != NULL)
			    strncpy(obj, label0, 10);
			mark[m] = 2;
		    }

		    rowlab[m] = strdup(label0);
		    strcpy(str, label0);
		    strcat(str, "R");
		    install(str, m);
		    m++;
		    if (m >= m2) {
			m2 = 2 * m2;
			REDOUBLE(r, m2);
			REINTEGER(mark, m2);
			RESTRING(rowlab, m2);
		    }
		}
		break;

	      case COLS:

		if (line[0] != ' ') {
		    DOUBLE0(c, n);
		    DOUBLE0(l, n);
		    DOUBLE(u, n);
		    INTEGER(varsgn, n);

		    for (j = 0; j < n; j++)
			u[j] = HUGE;
		    for (j = 0; j < n; j++)
			varsgn[j] = 1;

		    state = newstate(line);
		} else {
		    strcpy(str, label0);
		    strcat(str, "C");
		    np = lookup(str);
		    if (np != NULL) {	   /* seen this col before */
			/* check to see if agrees with previous col */
		    } else {		   /* new col label */
			ka[n] = nz;
			collab[n] = strdup(label0);
			install(str, n);
			n++;
			if (n >= n2) {
			    n2 = 2 * n2;
			    REINTEGER(ka, n2);
			    RESTRING(collab, n2);
			}
		    }

		    if (len >= 50) {
			value = atof(valstr2);
			if (value != 0.0) {
			    strcpy(str, label2);
			    strcat(str, "R");
			    np = lookup(str);
			    if (np != NULL) {
				i = *(np->defn);
				ia[nz] = i;
				a[nz] = value;
				nz++;
				if (nz >= nz2) {
				    nz2 = 2 * nz2;
				    REINTEGER(ia, nz2);
				    REDOUBLE(a, nz2);
				}
			    } else
				warn(30, label2);
			}
		    }
		    value = atof(valstr1);
		    if (value != 0.0) {
			strcpy(str, label1);
			strcat(str, "R");
			np = lookup(str);
			if (np != NULL) {
			    i = *(np->defn);
			    ia[nz] = i;
			    a[nz] = value;
			    nz++;
			    if (nz >= nz2) {
				nz2 = 2 * nz2;
				REINTEGER(ia, nz2);
				REDOUBLE(a, nz2);
			    }
			} else
			    warn(30, label1);
		    }
		}
		break;

	      case RHS:

		if (line[0] != ' ') {
		    state = newstate(line);
		} else {
		    if (rhs[0] == '\0')
			strncpy(rhs, label0, 10);
		    if (my_strstr(label0, rhs) != NULL) {
			if (len >= 50) {
			    value = atof(valstr2);
			    if (value != 0.0) {
				strcpy(str, label2);
				strcat(str, "R");
				np = lookup(str);
				if (np != NULL) {
				    i = *(np->defn);
				    b[i] = value;
				} else
				    warn(31, label2);
			    }
			}
			value = atof(valstr1);
			if (value != 0.0) {
			    strcpy(str, label1);
			    strcat(str, "R");
			    np = lookup(str);
			    if (np != NULL) {
				i = *(np->defn);
				b[i] = value;
			    } else
				warn(31, label1);
			}
		    }
		}
		break;

	      case RNGS:

		if (line[0] != ' ') {
		    state = newstate(line);
		} else {
		    if (ranges[0] == '\0')
			strncpy(ranges, label0, 10);
		    if (my_strstr(label0, ranges) != NULL) {
			if (len >= 50) {
			    value = atof(valstr2);
			    if (value != 0.0) {
				strcpy(str, label2);
				strcat(str, "R");
				np = lookup(str);
				if (np != NULL) {
				    i = *(np->defn);
				    r[i] = value;
				} else
				    warn(32, label2);
			    }
			}
			value = atof(valstr1);
			if (value != 0.0) {
			    strcpy(str, label1);
			    strcat(str, "R");
			    np = lookup(str);
			    if (np != NULL) {
				i = *(np->defn);
				r[i] = value;
			    } else
				warn(32, label1);
			}
		    }
		}
		break;

	      case BNDS:

		if (line[0] != ' ') {
		    state = newstate(line);
		} else {
		    if (bounds[0] == '\0')
			strncpy(bounds, label0, 10);
		    if (my_strstr(label0, bounds) != NULL) {
			value = atof(valstr1);
			strcpy(str, label1);
			strcat(str, "C");
			np = lookup(str);
			if (np != NULL) {
			    j = *(np->defn);
			    if (strcmp(type, "LO") == 0) {
				l[j] = value;
			    } else if (strcmp(type, "UP") == 0) {
				u[j] = value;
			    } else if (strcmp(type, "FX") == 0) {
				l[j] = value;
				u[j] = value;
			    } else if (strcmp(type, "FR") == 0) {
				l[j] = -HUGE;
			    } else if (strcmp(type, "PL") == 0) {
				l[j] = 0.0;
				u[j] = HUGE;
			    } else if (strcmp(type, "MI") == 0) {
				l[j] = 0.0;
				u[j] = HUGE;
				for (k = ka[j]; k < ka[j + 1]; k++)
				    a[k] = -a[k];
				varsgn[j] = -1;
			    } else
				warn(27, type);
			} else
			    warn(33, label1);
		    }
		}
		break;
	    }
	}
	fclose(fp);
    }
    if (name[0] == '\0')
	error(11, "");
    if (state != END)
	warn(41, "");

    ka[n] = nz;

    INTEGER(iat, nz);
    INTEGER(kat, m + 1);
    DOUBLE(at, nz);

    atnum(m, n, ka, ia, a, kat, iat, at);

    /*-----------------------------------------------------------+
    |	transfer objective function to c[]                  */

    strcpy(str, obj);
    strcat(str, "R");
    np = lookup(str);
    if (np != NULL) {
	i = *(np->defn);
	if (mark[i] == 2)
	    for (k = kat[i]; k < kat[i + 1]; k++)
		c[iat[k]] = at[k];
	else
	    warn(40, obj);
    } else
	warn(40, obj);

    /*-----------------------------------------------------------+
    |	negate G rows                                       */

    for (i = 0; i < m; i++) {
	if (mark[i] == 1) {
	    for (k = kat[i]; k < kat[i + 1]; k++) {
		at[k] = -at[k];
	    }
	    b[i] = -b[i];
	}
    }

    /*-----------------------------------------------------------+
    |	remove unconstrained rows                           */

    k = 0;
    row = 0;
    for (i = 0; i < m; i++) {
	if (mark[i] != 2) {
	    for (kk = kat[i]; kk < kat[i + 1]; kk++) {
		iat[k] = iat[kk];
		at[k] = at[kk];
		k++;
	    }
	}
    }
    for (i = 0; i < m; i++) {
	if (mark[i] != 2) {
	    kat[row + 1] = kat[row] + kat[i + 1] - kat[i];
	    b[row] = b[i];
	    r[row] = r[i];
	    mark[row] = mark[i];
	    row++;
	}
    }
    m = row;

    atnum(n, m, kat, iat, at, ka, ia, a);

    /*----------------------------------------------------+
    | Select method (primal or dual)                     */

    {
	double          dense, fraction;
	int             pfillin, dfillin, rngflag = FALSE;

	fraction = 1.0e0;
	for (j = 0; j < n; j++) {
	    dense = (double) (ka[j + 1] - ka[j]) / m;
	    fraction = fraction * (1.0e0 - dense * dense);
	}
	pfillin = (int) m *m * (1.0e0 - fraction) / 2.0;
	if (v)
	    printf(" primal fillin estimate: %10d\n", pfillin);

	fraction = 1.0e0;
	for (i = 0; i < m; i++) {
	    dense = (double) (kat[i + 1] - kat[i]) / n;
	    fraction = fraction * (1.0e0 - dense * dense);
	}
	dfillin = (int) n *n * (1.0e0 - fraction) / 2.0;
	if (v)
	    printf(" dual   fillin estimate: %10d\n\n", dfillin);

	for (i = 0; i < m; i++)
	    if (r[i] != 0.0 && r[i] != HUGE) {
		rngflag = TRUE;
		goto hell;
	    }
hell:	if (method == UNSET) {
	    if (pfillin <= 2 * dfillin || rngflag || maxflag == -1) {
		method = PRIMAL;
	    } else {
		method = DUAL;
		printf(" Solving DUAL as PRIMAL\n");
	    }
	}
    }

    nz = ka[n];

    RESTRING(rowlab, m);
    RESTRING(collab, n);

    FREE(mark);
    FREE(hashtab);

    FREE(at);
    FREE(iat);
    FREE(kat);

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
    kp->varsgn = varsgn;
    kp->rowlab = rowlab;
    kp->collab = collab;
    kp->max = maxflag;
    kp->inftol = inftol;
    kp->sf_req = sf_req;
    kp->v = v;
    kp->split = split;
    kp->method = method;
    strcpy(kp->name, name);
    strcpy(kp->obj, obj);
    strcpy(kp->rhs, rhs);
    strcpy(kp->ranges, ranges);
    strcpy(kp->bounds, bounds);
}

void            writelp(fname)
    char           *fname;
{
/*
	int i,j,k,ii;
	FILE *fp;
	
	if ( ( fp = fopen(fname,"w") ) == NULL ) error(2,fname);
	fprintf(fp,"NAME          %8s\n",name);
	fprintf(fp,"ROWS\n");
	fprintf(fp," N  %8s\n",obj);
	for (i=0; i<m; i++) {
	    if (r[i] == 0.0) {
		fprintf(fp," E  %8s\n",rowlab[i]);
	    } else {
		fprintf(fp," L  %8s\n",rowlab[i]);
	    }
	}
	fprintf(fp,"COLUMNS\n");
	for (j=0; j<n; j++) {
	    for (k=ka[j]; k<ka[j+1]-1; k+=2) {
		fprintf(fp,"    %8s  %8s%14f   %8s%14f\n",
			collab[j],rowlab[ia[k]],a[k],rowlab[ia[k+1]],a[k+1]);
		
	    }
	    if ( k<ka[j+1] )
		fprintf(fp,"    %8s  %8s%14f\n",collab[j],rowlab[ia[k]],a[k]);
	    if ( c[j] != 0.0 )
		fprintf(fp,"    %8s  %8s%14f\n",collab[j],obj,c[j]);
	}

	fprintf(fp,"RHS\n");
	ii = 0;
	for (i=0; i<m; i++) {
	    if ( b[i] != 0.0 ) {
		if (ii%2 == 0) {
		    fprintf(fp,"    %8s  %8s%14f",rhs,rowlab[i],b[i]);
		} else {
		    fprintf(fp,"   %8s%14f\n",rowlab[i],b[i]);
		}
		ii++;
	    }
	}
	if (ii%2 != 0) fprintf(fp,"\n");

	fprintf(fp,"BOUNDS\n");
	fprintf(fp,"RANGES\n");
	fprintf(fp,"ENDATA\n");
	fclose(fp);
*/
}

void            writesol(kp, fname)
    CORBO          *kp;
    char            fname[];
{
    int             m, n, *varsgn;
    double         *x, *y, *rc;
    char          **rowlab, **collab;

    int             i, j;
    FILE           *fp;

    m = kp->m;
    n = kp->n;
    varsgn = kp->varsgn;
    rowlab = kp->rowlab;
    collab = kp->collab;
    x = kp->x;
    y = kp->y;
    rc = kp->rc;

    for (j = 0; j < n; j++) {
	x[j] = varsgn[j] * x[j];
	rc[j] = varsgn[j] * rc[j];
    }
    if ((fp = fopen(fname, "w")) == NULL)
	error(2, fname);
    fprintf(fp, "COLUMNS SECTION\n");
    fprintf(fp, "   index       label primal_value reduced cost\n");
    for (j = 0; j < n; j++)
	fprintf(fp, "%8d  %10s  %10.3e  %10.3e \n",
		j, collab[j], x[j], rc[j]);
    fprintf(fp, "ROWS SECTION\n");
    fprintf(fp, "   index       label  dual_value  \n");
    for (i = 0; i < m; i++)
	fprintf(fp, "%8d  %10s  %10.3e \n",
		i, rowlab[i], y[i]);
    fclose(fp);
}

static int      newstate(line)
    char           *line;
{
    if (strcmp(line, "RHS") == 0)
	return RHS;
    else if (strcmp(line, "RAN") == 0)
	return RNGS;
    else if (strcmp(line, "BOU") == 0)
	return BNDS;
    else if (strcmp(line, "END") == 0)
	return END;
    else
	error(26, line);
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
	printf("cannot allocate space in iolp\n");
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

static void     warn(num, text)
    int             num;
    char           *text;
{
    switch (num) {
      case 20:
	printf("expected ROWS after NAME instead of %s\n",
	       text);
	break;
      case 21:
	printf("expected L, E, G, N, or COLUMNS instead of %s\n",
	       text);
	break;
      case 27:
	printf("unrecognized bound type %s \n", text);
	break;
      case 30:
	printf("row label %s from COLUMNS section missing in ROWS section\n", text);
	break;
      case 31:
	printf("row label %s from RHS section missing in ROWS section\n", text);
	break;
      case 32:
	printf("row label %s from RANGES section missing in ROWS section\n", text);
	break;
      case 33:
	printf("col label %s from BOUNDS section missing in COLUMNS section\n", text);
	break;
      case 40:
	printf("objective function %s not found \n", text);
	break;
      case 41:
	printf("ENDATA not found \n");
	break;
    }
}

static void     identify()
{
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
	   "Code developed by:",
	   "  Robert J. Vanderbei",
	   "  Rm 2C-124",
	   "  AT&T Bell Labs",
	   "  600 Mountain Ave.",
	   "  Murray Hill, NJ 07974",
	   "  (201) 582-7589"
    );
    exit(0);
}

/* hash:  form hash value for string s */
static unsigned hash(s)
    char           *s;
{
    unsigned        hashval;

    for (hashval = 0; *s != '\0'; s++)
	hashval = *s + theta * hashval;
    return hashval % hashsize;
}

/* lookup: look for s in hashtab */
NLIST          *lookup(s)
    char           *s;
{
    NLIST          *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	if (strcmp(s, np->name) == 0)
	    return np;			   /* found it  */
    return NULL;			   /* not found */
}

/* install: put (name, defn) in hashtab */
NLIST          *install(s, num)
    char           *s;
    int             num;
{
    NLIST          *np;
    unsigned        hashval;

    if ((np = lookup(s)) == NULL) {	   /* not found */
	np = (NLIST *) malloc(sizeof(*np));
	if (np == NULL || (np->name = strdup(s)) == NULL)
	    return NULL;
	hashval = hash(s);
	np->next = hashtab[hashval];
	hashtab[hashval] = np;
    } else {				   /* already there */
	free((char *) np->defn);	   /* free previous defn */
    }
    if ((np->defn = intdup(num)) == NULL)
	return NULL;
    return np;
}

static int     *intdup(num)
    int             num;
{
    int            *ptr;

    ptr = (int *) malloc(sizeof(int));
    if (ptr != NULL)
	*ptr = num;
    return ptr;
}
