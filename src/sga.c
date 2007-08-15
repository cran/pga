#include "pga.h"

//----------------------------------------------------------------
//   sga - Single-Path Genetic Algorithm for Variable Selection 
//       mR:           population size in a generation
//       NR:           number of generation per path
//       startR:       the starting population
//       mutationR:    muatation rate
//       priorR:       controls the density of 1's in the initial population
//       checkConvgR:  whether to calculate the number of generation needed for convergence
//       threshR:      a prespecified threshold that indicates convergence
//       rho:          environment
//-----------------------------------------------------------------

SEXP sga(SEXP yR, SEXP lengthYR, SEXP XR, SEXP xcolR, SEXP xrowR, SEXP mR, SEXP NR, SEXP startR, SEXP mutationR, SEXP priorR, SEXP checkConvgR, SEXP threshR, SEXP rho)

{   int i,j, s, t;
    SEXP convg;
    SEXP perfi;
    SEXP iR, bestR, optivalR;
    SEXP comboR;
    SEXP ansR;
    SEXP popnR;
    SEXP names;
    SEXP iNameR, popnNameR, comboNameR;

    double* entro;
    int* currtemp;
    double* mutationMatrix;
    int** curr;
    int* popn;
    double ranNum;

    double* prevBest;
    double* prevAvg;
    double* pp;
    double* qq;
    double* lp;
    double* lq;
    int** newGen;
    double entropy;
    double tempMean;
    int sum;
    int minIndex;
    double* min;
    double* mean;
    
    //temperary values for parameters
    int* lengthY= INTEGER(lengthYR);
    int* xcol = INTEGER(xcolR);
    int* xrow = INTEGER(xrowR);
    int* m = INTEGER(mR);
    int* N = INTEGER(NR);
    double* prior= REAL(priorR);
    int* checkConvg = INTEGER(checkConvgR);
    double* thresh = REAL(threshR);
    double* finalScore;

    // added by Mu Zhu, Apr 08
    SEXP finalScoreR;
    // end additio by Mu Zhu, Apr 08

     // change m to even number if m is odd
     if( div((*m), 2).rem ==1)
     { (*m) = (*m) +1;
     }
       

     //R objects creation which will be returned to R functions
     PROTECT(convg=allocVector(REALSXP, INTEGER(NR)[0]+1));
     PROTECT(perfi=allocVector(REALSXP, INTEGER(NR)[0]+1));
     PROTECT(iR=allocVector(INTSXP, 1));
     PROTECT(bestR=allocVector(INTSXP, (*xcol)));
     PROTECT(optivalR=allocVector(REALSXP, 1));
     PROTECT(comboR=allocVector(REALSXP, (*xcol)));
     PROTECT(popnR=allocMatrix(INTSXP, (*m), (*xcol)));
    

     //C objects existing only in this method
     prevBest = (double*) R_alloc(1, sizeof(double));
     prevAvg = (double*)R_alloc(1, sizeof(double));
    
     //set up entro array, one entropy value for each generation
     if((*checkConvg) ==  1)
     { //Rprintf("set up entro if checkConvg is true");
       entro = (double*)R_alloc((*N), sizeof(double));
       pp = (double*)R_alloc((*xcol), sizeof(double));
       qq = (double*) R_alloc((*xcol), sizeof(double));
       lp = (double*) R_alloc((*xcol), sizeof(double));
       lq = (double*) R_alloc((*xcol), sizeof(double));
     }
   

    
     // the matrix that contains the next generation in this path
     newGen = (int**)R_alloc((*m), sizeof(int*));
     for(i =0; i<(*m); i++)
     {   newGen[i]= (int*)R_alloc((*xcol), sizeof(int));
     }

  
    /* allocate space for the curr matrix*/
    curr = (int**)R_alloc((*m), sizeof(int*));
    for( i = 0; i<(*m); i++)
    {   curr[i] =(int*) R_alloc((*xcol),sizeof(int));
    }
    
 
    mutationMatrix = (double*)R_alloc((*N), sizeof(double));
    /*possible to use a different mutation rate for each generation*/
    if(LENGTH(mutationR)!=(*N))
    {  // mutation <- rep(mutation[1], N)
       for(i = 0 ;i<(*N); i++)
      { mutationMatrix[i] = REAL(mutationR)[0]; 
	
      }
    }else
    {   for(i=0; i<(*N); i++)
       { mutationMatrix[i] = REAL(mutationR)[i];
       }
    }

    //generate curr if start is null
    if(LENGTH(startR)==0)
    { // curr <- matrix(sample(0:1, size=(m*p), prob=c((1-prior), prior), replace=T),m,p)
      for( i = 0; i<(*m); i++)
      { 
        for(j=0; j<(*xcol); j++)
        { ranNum = rand()/(RAND_MAX+1.0);
	  if(ranNum <=(*prior))
	  {  curr[i][j] = 1;
	  }else
	  {  curr[i][j] = 0;
	  }
        }
      }
    }else
    { 
      for(i = 0; i<(*m); i++)
      {  for(j =0; j<(*xcol); j++)
	 { curr[i][j]= INTEGER(startR)[i+j*(*m)];
	 }
      }	 
      
    }
	   
   //printMatrixInt(curr, xcol, m);


    // added by Mu Zhu, Apr 08, for debugging purposes, check small changes made to fitness 
    if ((*N) == 0) 
    {
     finalScore = (double*)fitness(curr, yR, XR,xcol, xrow, m, rho);
    }else
    {
    // end addition by Mu Zhu, Apr 08


    /*evolve N number of generations*/  
    for( i = 0; i<(*N); i++)
    {  
       // Rprintf("%d\n", i);
       // rslt <- onegen(curr, y, X, m, mutation[i])
       onegen(curr, yR, XR, xcol, xrow,  m,  &mutationMatrix[i], newGen, prevBest, prevAvg, rho );
       // curr <- rslt$new.gen
       for(s=0; s<(*m);s++)
       {  for(t=0; t<(*xcol); t++)
	    { curr[s][t] = newGen[s][t];
	    }
       }
        // printMatrixInt(curr, xcol, m);
        if((*checkConvg) ==1)
        { 
	  // pp contains the mean for each column of curr    
          // pp <- apply(curr,2,mean)
	  
	  for(s=0; s<(*xcol); s++)
	  {  pp[s] =0.0;
	     for (t=0; t<(*m); t++)
	     { 
	       pp[s]= pp[s] + (double)(curr[t][s]);
	      
	     }
	     pp[s] = pp[s]/(double)(*m);
	  }
        

          //lp <- ifelse(pp==0, 0, log10(pp,base=2))
          for(s = 0; s<(*xcol);s++)
          {  qq[s] = 1.0-pp[s];
             if(pp[s]==0.0)
	     { lp[s] = 0.0;
	     }else
	     { lp[s] = log(pp[s])/log(2.0);
	     } 
	  }
          //lq <- ifelse(qq==0, 0, log(qq,base=2))  
	  for(s = 0; s<(*xcol);s++)
          { 
             if(qq[s]==0.0)
	     { lq[s] = 0.0;
	     }else
	     { lq[s] = log(qq[s])/log(2.0);
	     } 
	  }
	  
          // entro[i]<-entropy <- mean(-(pp*lp+qq*lq))
	  entropy=0;
	  for(s= 0; s<(*xcol); s++)
	  { entropy += (-1)*(pp[s]*lp[s]+qq[s]*lq[s]);
          }
          entropy= entropy/(double)(*xcol);	  
	  entro[i] = entropy;
	  Rprintf("%f\n", entro[i]);

          //if (i > 5 && mean(entro[(i-5):i]) < thresh) break
	  tempMean = 0;
	  if(i>5)
	  {   for( s= i; s>i-6; s--)
	      { tempMean += entro[s];
	      }
	      tempMean = tempMean/6.0;
	      if(tempMean <(*thresh))
	      { break;
	      }
	  }
	}/* finish checking convergence*/
	  
	REAL(convg)[i]  = (*prevBest);
	REAL(perfi)[i] = (*prevAvg);
    }
    /*finish evolving*/
    
    finalScore = (double*)fitness(curr, yR, XR,xcol, xrow, m, rho);

    }  // end if, added by Mu Zhu, Apr 08


    // addition by Mu Zhu, Apr 08
    if ((*N) == 0)
    {
           PROTECT(finalScoreR=allocVector(REALSXP, (*m)));
           for(s=0; s<(*m);s++)   
           {
            REAL(finalScoreR)[s] = finalScore[s];
           }
           PROTECT(ansR=allocVector(VECSXP, 1));
           SET_VECTOR_ELT(ansR, 0, finalScoreR);
           //set up the names
           PROTECT(names=allocVector(STRSXP, 1));
           SET_STRING_ELT(names, 0, mkChar("scores"));
           setAttrib(ansR, R_NamesSymbol, names);
           UNPROTECT(10);
    }else
    {
    // end addition by Mu Zhu, Apr 08

    // convg[N+1] <- min(final.score)
    // perf[N+1] <- mean(final.score)
    min =(double*) getMin(finalScore, m);
    REAL(convg)[(*N)] = *(min);
    REAL(optivalR)[0] = REAL(convg)[(*N)];
    
    mean = (double*)getMean(finalScore, m);
    REAL(perfi)[(*N)] = *mean;
     
    /*set up popn = curr*/
    popn = INTEGER(popnR);
    for(s=0; s<(*m);s++)
    { 
	    for(t=0; t<(*xcol); t++)
	    { popn[s+(*m)*t]=curr[s][t];
	    }
    }
     
    /*combo.gene=apply(curr,2,mean)*/
    for (s=0; s<(*xcol);s++)
    {   sum = 0;
       	for (t=0; t<(*m); t++)
	{ sum += curr[t][s];
   	}
	REAL(comboR)[s] = ((double)sum)/(double)(*m);
    }
    if(*checkConvg==1)
    {     
          Rprintf("Convergence achieved with %d generations...\n", i);
         /*return(list(ans=i, popn=curr, combo.gene=apply(curr,2,mean)))*/
	  PROTECT(ansR=allocVector(VECSXP,3));
	  INTEGER(iR)[0]=i;
	  SET_VECTOR_ELT(ansR, 0, iR);
	  SET_VECTOR_ELT(ansR, 1, popnR);
	  SET_VECTOR_ELT(ansR, 2, comboR);
          //set up the names
	  PROTECT(names=allocVector(STRSXP, 3));
	  SET_STRING_ELT(names, 0, mkChar("ans"));
	  SET_STRING_ELT(names, 1, mkChar("popn"));
	  SET_STRING_ELT(names, 2, mkChar("combo.gene"));
	  setAttrib(ansR, R_NamesSymbol, names);

    }else
    {
         /*  return(list(popn=curr, combo.gene=apply(curr,2,mean),
              best=curr[order(final.score),][1,],
               optval=min(final.score),
               convg, perf))
	  */
	 
           PROTECT(ansR=allocVector(VECSXP, 6));
           SET_VECTOR_ELT(ansR, 0, popnR);
	   SET_VECTOR_ELT(ansR, 1, comboR);
	   //set up bestR
	   minIndex = 0;
           for( i=1 ; i<(*m); i++)
          {  
             if(finalScore[i] <finalScore[minIndex])
	       { minIndex = i;
	       }
            
	  }
	   for(i=0; i<(*xcol);i++)
	   { INTEGER(bestR)[i] = curr[minIndex][i];
	   }
	   SET_VECTOR_ELT(ansR, 2, bestR);
	   SET_VECTOR_ELT(ansR, 3, optivalR);
	   SET_VECTOR_ELT(ansR, 4, convg);
	   SET_VECTOR_ELT(ansR, 5, perfi);

	    //set up the names
	  PROTECT(names=allocVector(STRSXP, 6));
	  SET_STRING_ELT(names, 0, mkChar("popn"));
	  SET_STRING_ELT(names, 1, mkChar("combo.gene"));
	  SET_STRING_ELT(names, 2, mkChar("best"));
	  SET_STRING_ELT(names, 3, mkChar("optval"));
	  SET_STRING_ELT(names, 4, mkChar("convg"));
	  SET_STRING_ELT(names, 5, mkChar("perf"));
	  setAttrib(ansR, R_NamesSymbol, names);
    }   
	 
    UNPROTECT(9);
    } // end if, added by Mu Zhu, Apr 08  

    return (ansR);

}    



