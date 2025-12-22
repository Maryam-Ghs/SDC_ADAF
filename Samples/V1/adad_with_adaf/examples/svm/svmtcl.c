/* $Id$ */
#include "athena.h"
#include "svm.h"

/* ********************************************************************** */
static Tcl_HashTable *_modtab = 0;
static int _modnum = 0;

#define	DEBUG	    0

typedef struct {
    char	    *name;
    int		    npar;
    svm_node	    *store;
    svm_model	    *model;
    svm_parameter   param;
} svmmodel;
/* ********************************************************************** */
static char *New_Mod_Name() {
    static char name[32];
    assert(_modtab);
    while (1) {
	sprintf(name, "SvmMod%d", _modnum++);
	if (Tcl_FindHashEntry(_modtab, name) == 0) break;
    }
    return(strdup(&(name[0])));
}
/* ********************************************************************** */
static svmmodel *make_model(char *name) {
    int		ncoef;
    svmmodel	*M;
    Tcl_HashEntry *ent;
    M = (svmmodel *) malloc(sizeof(svmmodel));
    M->name = (name == NULL) ? New_Mod_Name() : strdup(name);
    M->npar = 0;
    M->model = NULL;
/* set parameter defaults */
    M->param.svm_type = C_SVC;
    M->param.kernel_type = RBF;
    M->param.degree = 3;
    M->param.gamma = 0;
    M->param.coef0 = 0;
    M->param.nu = 0.5;
    M->param.cache_size = 100;
    M->param.C = 1;
    M->param.eps = 1e-3;
    M->param.p = 0.1;
    M->param.shrinking = 1;
    M->param.probability = 0;
    M->param.nr_weight = 0;
    M->param.weight_label = NULL;
    M->param.weight = NULL;
/* look it up and delete old one if it exists */
    if ((ent = Tcl_FindHashEntry(_modtab, M->name))) {
	svmmodel *N;
	N = (svmmodel *) Tcl_GetHashValue(ent);
	if (N->model) svm_destroy_model(N->model);
	if (N->store) free((char *) N->store);
	free((char *) N->name);
	free((char *) N);
	Tcl_SetHashValue(ent, M);
    } else {
	ent = Tcl_CreateHashEntry(_modtab, M->name, &ncoef);
	Tcl_SetHashValue(ent, M);
    }
    return(M);
}
/* ********************************************************************** */
static int delete_model(Tcl_Interp *p, svmmodel *N) {
    Tcl_HashEntry  *ent;
    if (_modtab && (ent = Tcl_FindHashEntry(_modtab, N->name))) {
	Tcl_DeleteHashEntry(ent);
	if (N->model) svm_destroy_model(N->model);
	if (N->store) free((char *) N->store);
	free((char *) N->name);
	free((char *) N);
    }
    return(TCL_OK);
}
/* ********************************************************************** */
static int build_model(Tcl_Interp *p, matrix *X, vector *Y, vector *YHAT, vector *RES) {
    svmmodel	    *M;
    svm_problem	    PROB;
    svm_node	    **PSX, *SX;
    char	    *error_message;
    int i, j, k, Npar = Mat_Ncol(X), Nobs = Mat_Nrow(X);

    if (Nobs != Vec_Dim(Y)) {
	sprintf(p->result, "Y vector is not of size %d", Nobs);
	return (TCL_ERROR);
    }
    if (Nobs != Vec_Dim(YHAT)) {
	sprintf(p->result, "YHAT vector is not of size %d", Nobs);
	return (TCL_ERROR);
    }
    if (Nobs != Vec_Dim(RES)) {
	sprintf(p->result, "RES vector is not of size %d", Nobs);
	return (TCL_ERROR);
    }
    if (_modtab == 0) {
	_modtab = (Tcl_HashTable *) malloc(sizeof(Tcl_HashTable));
	Tcl_InitHashTable(_modtab, TCL_STRING_KEYS);
    }
/* create model */
    M = make_model(NULL);
    M->npar = Npar;
/* make the svm_node array */
    PSX = (svm_node **) malloc(Nobs * sizeof(svm_node *));
    SX = (svm_node *) malloc((Npar+1)*Nobs * sizeof(svm_node));
    PROB.y = (double *) malloc(Nobs*sizeof(double));
/* copy the data into it */
    k = 0;
    for (i=0; i<Nobs; i++) {
	PROB.y[i] = Vec_Value(Y)[i];
	PSX[i] = &(SX[k]);
	for (j=0; j<Npar; j++) {
	    SX[k].index = j+1;
	    SX[k].value = Mat_Value(X)[i][j];
	    ++k;
	}
	SX[k].index = -1;
	SX[k].value = 0.0;
	++k;
    }
/* initialize problem structure */
    PROB.l = Nobs;
    PROB.x = PSX;
    M->param.gamma = 1.0/Npar;
/* check the data */
    error_message = (char *) svm_check_parameter(&PROB, &(M->param));
    if (error_message) {
	fprintf(stderr, "Error: %s\n", error_message);
	exit(1);
    }
/* call the training routine, and store the output in the model pointer */
    M->model = svm_train(&PROB, &(M->param));
/* need to evaluate the model on all the original data in order to populate
   the YHAT and RES vectors */
/* first allocate a parameter vector */
    M->store = (svm_node *) malloc((Npar+1) * sizeof(svm_node));
/* loop over all observations */
    for (i=0; i<Nobs; i++) {
	for (j=0; j<Npar; j++) {
	    M->store[j].index = j+1;
	    M->store[j].value = Mat_Value(X)[i][j];
	}
	M->store[Npar].index = -1;
	Vec_Value(YHAT)[i] = svm_predict(M->model, M->store);
	Vec_Value(RES)[i] = Vec_Value(YHAT)[i] - Vec_Value(Y)[i];
    }
/* done */
    Tcl_SetResult(p, M->name, TCL_STATIC);
    return(TCL_OK);
}
/* ********************************************************************** */
static int evaluate_model(Tcl_Interp *p, svmmodel *M, vector *Z) {
    int	    i;
    double  y;
    static char    str[MAXSTR];
/* check length of X */
    if (Vec_Dim(Z) != M->npar) {
	sprintf(str, "vector is not of size %d", M->npar);
	Tcl_AppendResult(p, str, NULL);
	return (TCL_ERROR);
    }
/* evaluate the model */
    for (i=0; i<M->npar; i++) {
	M->store[i].index = i+1;
	M->store[i].value = Vec_Value(Z)[i];
    }
    M->store[M->npar].index = -1;
    y = svm_predict(M->model, M->store);
/* done */
    Tcl_PrintDouble(p, y, str);
    Tcl_SetResult(p, str, TCL_STATIC);
    return(TCL_OK);
}
/* ********************************************************************** */
static int info_model(Tcl_Interp *p, svmmodel *M) {
    char	buf[MAXSTR];
/* return information */
    Tcl_ResetResult(p);
    Tcl_AppendResult(p, "{ name ", M->name, " } ", NULL);
    sprintf(buf, "%d", M->npar);
    Tcl_AppendResult(p, "{ npar ", buf, " } ", NULL);
    Tcl_AppendResult(p, "} ", NULL);
    return(TCL_OK);
}
/* ********************************************************************** */
static int tcl_svm(void *dummy, Tcl_Interp *p, int argc, char **argv) {
    svmmodel *M;
    matrix *X;
    vector *Y, *Yhat, *Res;
    Tcl_HashEntry  *ent;
    int i;
    Tcl_ResetResult(p);
    for (i=1; i<argc; i++) {
	if (STREQL(argv[i], "-build")) {
	    ++i;
	    if (! (X = GetMatrix(p, argv[i]))) {
		sprintf(p->result, "no such matrix \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    ++i;
	    if (! (Y = GetVector(p, argv[i]))) {
		sprintf(p->result, "no such vector \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    ++i;
	    if (! (Yhat = GetVector(p, argv[i]))) {
		sprintf(p->result, "no such vector \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    ++i;
	    if (! (Res = GetVector(p, argv[i]))) {
		sprintf(p->result, "no such vector \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    return(build_model(p, X, Y, Yhat, Res));
	}
	if (STREQL(argv[i], "-eval")) {
	    ++i;
	    if ((ent = Tcl_FindHashEntry(_modtab, argv[i]))) {
		M = (svmmodel *) Tcl_GetHashValue(ent);
	    } else {
		sprintf(p->result, "no such model \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    ++i;
	    if (! (Y = GetVector(p, argv[i]))) {
		sprintf(p->result, "no such vector \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    return(evaluate_model(p, M, Y));
	}
	if (STREQL(argv[i], "-delete")) {
	    ++i;
	    if (_modtab && (ent = Tcl_FindHashEntry(_modtab, argv[i]))) {
		M = (svmmodel *) Tcl_GetHashValue(ent);
	    } else {
		sprintf(p->result, "no such model \"%s\"", argv[i]);
		return (TCL_ERROR);
	    }
	    return(delete_model(p, M));
	}
	Tcl_AppendResult(p, "usage: ",
		     argv[0], " -build <X-data-matrix> <Y-vector> <Y-hat> <Residuals>\n",
		     argv[0], "-eval <model> <X-vector>\n",
		     argv[0], "-delete <model>\n", NULL);
	return (TCL_ERROR);
    }
    return (TCL_OK);
}
/* ********************************************************************** */
int Svm_Init(Tcl_Interp * p) {
    Tcl_CreateCommand(p, "svm", (Tcl_CmdProc *) tcl_svm, (ClientData) NULL, (Tcl_CmdDeleteProc *) NULL);
    return (TCL_OK);
}
