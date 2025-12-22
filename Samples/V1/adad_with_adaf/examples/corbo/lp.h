#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

/* #define	HUGE	HUGE_VAL */

#define TRUE 1
#define FALSE 0

#define HEADER 0
#define NAME   1
#define ROWS   2
#define COLS   3
#define RHS    4
#define RNGS   5
#define BNDS   6
#define END    7

#define UNSET  0
#define PRIMAL 1
#define DUAL   2

#define MAX(x,y)  ((x) > (y) ? (x) : (y))
#define MIN(x,y)  ((x) > (y) ? (y) : (x))
#define ABS(x)    ((x) > 0   ? (x) : -(x))
#define INTEGER(name,len) if ( ( (name) = (int *) malloc ( 		\
		(unsigned) (len+1) * sizeof(int) ) ) == NULL ) 		\
		{ printf("cannot allocate space(%d)\n",len*4); exit(10); }
#define DOUBLE(name,len)  if ( ( (name) = (double *) malloc ( 		\
		(unsigned) (len+1) * sizeof(double) ) ) == NULL ) 	\
		{ printf("cannot allocate space(%d)\n",len*8); exit(10); }
#define STRING(name,len)  if ( ( (name) = (char **) malloc ( 		\
		(unsigned) (len+1) * sizeof(char *) ) ) == NULL ) 	\
		{ printf("cannot allocate space(%d)\n",len*4); exit(10); }
#define INTEGER0(name,len) if ( ( (name) = (int *) calloc ( 		\
		(unsigned) (len+1) , sizeof(int) ) ) == NULL ) 		\
		{ printf("cannot allocate space(%d)\n",len*4); exit(10); }
#define DOUBLE0(name,len)  if ( ( (name) = (double *) calloc ( 		\
		(unsigned) (len+1) , sizeof(double) ) ) == NULL ) 	\
		{ printf("cannot allocate space(%d)\n",len*8); exit(10); }
#define REINTEGER(name,len) if ( ( (name) = (int *) realloc ( 		\
		(char *) (name), 					\
		(unsigned) (len) * sizeof(int) ) ) == NULL ) 		\
		{ printf("cannot reallocate space\n"); exit(11); }
#define REDOUBLE(name,len)  if ( ( (name) = (double *) realloc ( 	\
		(char *) (name),					\
		(unsigned) (len) * sizeof(double) ) ) == NULL ) 	\
		{ printf("cannot reallocate space\n"); exit(11); }
#define RESTRING(name,len)  if ( ( (name) = (char **) realloc ( 	\
		(char *) (name),					\
		(unsigned) (len) * sizeof(char *) ) ) == NULL ) 	\
		{ printf("cannot reallocate space\n"); exit(11); }
#define DOUBLE2(name,len)  if ( ( (name) = (double **) malloc ( 	\
		(unsigned) (len) * sizeof(double *) ) ) == NULL ) 	\
		{ printf("cannot allocate space\n"); exit(10); }
#define FREE(name) { free( (char *) (name) ); (name) = NULL; }

struct nlist {			/* table entry */
	struct nlist *next;	      /* next entry in chain */
	char	     *name;	      /* defining label */
	int	     *defn;	      /* pointer to row index */
};

typedef struct nlist NLIST;

#define LP_OPEN_MAX 20 /* max # lp problems open at once */

typedef struct corbo {
	int m;		/* number of rows */
	int n;		/* number of columns */
	int nz;		/* number of nonzeros */
	double *a;	/* pointer to array of nonzero values in A */
	int *ia;	/* pointer to array of corresponding row indices */
	int *ka;	/* pointer to array of indices into a (and ia)
				indicating where each new column of A begins */
	double *b;	/* pointer to array containing right-hand side */
	double *c;	/* pointer to array containing objective function */
	double f;	/* fixed adjustment to objective function */
	double *r;	/* pointer to array containing range vector */
	double *l;	/* pointer to array containing lower bounds */
	double *u;	/* pointer to array containing upper bounds */
	int *varsgn;	/* array indicating which variables were declared to
				be non-positive */
	char **rowlab;	/* array of strings containing row labels */
	char **collab;	/* array of strings containing column labels */

	double *x;	/* pointer to array containing primal solution */
	double *y;	/* pointer to array containing dual solution */
	double *rc;	/* pointer to array containing reduced costs */

	int max;	/* max = -1, min = 1 */
	double inftol;	/* infeasibility tolerance */
	int sf_req;	/* significant figures requested */
	int v;		/* level of verbosity */
	int split;	/* split columns threshold (0=off) */
	int method;	/* either PRIMAL or DUAL */
	char name[15];	/* string containing problem name */
	char obj[11];	/* string containing objective function name */
	char rhs[11];	/* string containing right-hand side name */
	char ranges[11];/* string containing range set name */
	char bounds[11];/* string containing bound set name */

	int flag;	/* 0=unopened, 1 = opened */
} CORBO;

CORBO _lpb[LP_OPEN_MAX];

extern void 	atnum(), smx(), inv_sym(), inv_num(), readlp(), 
		writelp(), writesol(), message(), exit();
extern double 	primalres(), dualres(), dotprod(), maxv();
extern char	*probname(), 
		*strdup();
extern NLIST	*lookup(), *install();
