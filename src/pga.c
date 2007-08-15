#include "pga.h"

//--------------------------------------------------------------------
// pga - Parallel Genetic Algorithm for Variable Selection
//       mR:          population size
//       NR:          number of generations per path
//       BR:          number of parallel paths
//       mutationR:   mutation rate
//       startR:      starting population
//       priorR:      controls the density of 1's in the initial population
//--------------------------------------------------------------------


SEXP pga(SEXP yR, SEXP XR, SEXP xcolR, SEXP xrowR, SEXP mR, SEXP NR, SEXP BR, SEXP mutationR, SEXP startR, SEXP priorR,  SEXP rho)
{    int i,xcol,B,b;
     //parameters for sga
     SEXP checkConvg;
     SEXP thresh;
     SEXP result; 
     SEXP temp;
     double *rst;
     SEXP dim;
     SEXP combo;
     
     //set up default values for sga
     PROTECT(checkConvg = allocVector(LGLSXP, 1));
     INTEGER(checkConvg)[0] = 0;
     PROTECT(thresh = allocVector(REALSXP, 1));
     REAL(thresh)[0]= 0.05;
     
     xcol = INTEGER(xcolR)[0];
     B = INTEGER(BR)[0];
     PROTECT(result = allocVector(REALSXP, B*xcol)); 
     rst = REAL(result);

     Rprintf("Starting PGA...\n");
     b = 0;

     while(b<(B))
     {  Rprintf(" %d\n",b);
        temp =(SEXP)sga(yR, xcolR, XR, xcolR, xrowR, mR, NR, startR, mutationR, priorR, checkConvg, thresh, rho);
	combo = (SEXP)getListElement(temp, "combo.gene");
        //rslt[b,] <- tmp$combo.gene	 
	for(i=0; i<INTEGER(xcolR)[0]; i++)
	{ rst[b+B*i] = REAL(combo)[i];
	}
       
        b +=1;
     }
     //set up dimension for the resulting matrix
     PROTECT(dim = allocVector(INTSXP,2));
     INTEGER(dim)[0]=B;
     INTEGER(dim)[1]=xcol;
     setAttrib(result, R_DimSymbol, dim);

     UNPROTECT(4);
     return result;
}     
