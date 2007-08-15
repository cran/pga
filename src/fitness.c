
#include "pga.h"

//get the element of a list with specified name str
SEXP getListElement(SEXP list, char* str)
{   SEXP elmt = R_NilValue, names = getAttrib(list, R_NamesSymbol);
    int i;

    for(i=0; i<length(list); i++)
    { if(strcmp(CHAR(STRING_ELT(names, i)), str)==0)
      {  elmt = VECTOR_ELT(list, i);
	 break;
      }
    }
    return elmt;
}

// changed declaration, Mu Zhu, Apr 08
// double* fitness(int** curr, SEXP yR, SEXP XR, int* ncol, int* row, int *mR, SEXP rho, SEXP fn)
double* fitness(int** curr, SEXP yR, SEXP XR, int* ncol, int* row, int *mR, SEXP rho)
{  
   int i,j, s, t;
   SEXP ans;
   if(!isEnvironment(rho)) error("'rho' should be an environment");
   int q; 
//   double ybar;     
// changed this by Mu Zhu, Apr 08
   double* ybar;     
   double temp;
   double* gcvrss;
   SEXP xNewR;
   double* xNew;
   SEXP lsfit;
   double* residuals;
   SEXP R_fcall;
   //gcvrss <- numeric(m)	
   gcvrss = (double*)R_alloc((*mR), sizeof(double));

   for(i=0; i<(*mR); i++)
   {  //q <- sum(curr[i,])
      q=0;
      for(j=0; j<(*ncol);j++)
      { q+= curr[i][j];
      }
      j=0;
      if(q >0)
      {  //set up the X matrix being evaluated  X[,curr[i,]==1]
	 PROTECT(xNewR = allocMatrix(REALSXP, (*row), q));
	 xNew = REAL(xNewR);
	 for(s=0; s<(*ncol); s++)
	 { if(curr[i][s] ==1)
           {  for(t = 0; t<(*row); t++)
	      {  xNew[t+j*(*row)] = REAL(XR)[t+s*(*row)];
	      }
	      j++;
	   }
	 }
         //ls.out <- lsfit(X[,curr[i,]==1], y, intercept=T)
	 PROTECT(R_fcall = lang3(install("lsfit"), xNewR, yR));
	 PROTECT(lsfit = eval(R_fcall, rho));
         
         //get the residuals
         //gcvrss[i]<- sum((ls.out$resid/(1-(q+1)/n))^2)
         residuals = REAL(getListElement(lsfit, "residuals"));
	 temp =0;
	 for(s=0; s<(*row); s++)
	 { temp += pow((residuals[s]/(1.0-((double)q+1.0)/(double)(*row))), 2.0);
	 }
	 gcvrss[i] = temp;
	 UNPROTECT(3);

      }else
      {  //ybar <- mean(y)
         //gcvrss[i]<- sum(((y-ybar)/(1-(q+1)/n))^2)
//	 ybar= getMean(REAL(yR), (row));
// changed this by Mu Zhu, Apr 08, following other usages of getMean by Dandi elsewhere in the package
	 ybar= (double*)getMean(REAL(yR), (row));
	 temp=0; 
	 for(s=0; s<(*row); s++)
//	 { temp+= pow(((REAL(yR)[s] - (ybar))/(1.0-((double)q+1.0)/(double)(*row))),2.0); 
// changed this by Mu Zhu, Apr 08, now that ybar is a pointer
	 { temp+= pow(((REAL(yR)[s] - (*(ybar)))/(1.0-((double)q+1.0)/(double)(*row))),2.0); 
         }
	 gcvrss[i] = temp;
      }

   }
  
   return (gcvrss);
}



