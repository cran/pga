#include "pga.h"
//-------------------------------------------------------------------
//  onegen
//      Function for generating the next generation according to current
//      generation
//
//      curr: current generation
//      yR:   data matrix y
//      XR:   data matrix x
//      ncol: col(x)
//      nrow: row(x)
//      m:    population size
//      newGen: the matrix that holds the new generation that will be returned
//---------------------------------------------------------------------

// changed declaration, Mu Zhu, Apr 08
//void onegen(int **curr, SEXP yR, SEXP XR, int *ncol, int* nrow, int *m, double *mutation, int **newGen, double *prevBest, double *prevAvg, SEXP rho, SEXP fn)
void onegen(int **curr, SEXP yR, SEXP XR, int *ncol, int* nrow, int *m, double *mutation, int **newGen, double *prevBest, double *prevAvg, SEXP rho)
{  
    int i,j;
    int min;
    double tempScore;
    int temp;
    double *score;
    int* index =(int*)R_alloc((*m), sizeof(int));
    double* mean;
    int* left = (int*)R_alloc(1, sizeof(int));
    int* right= (int*)R_alloc(1, sizeof(int));
    *left = 0;
    *right = (*m)-1;

    // calculate the fitness score for the m population
    // orig.score <- fitness(curr, y, X, m)
    // score = (double*)fitness(curr, yR, XR, ncol, nrow, m, rho, fn);
    // changed here by Mu Zhu, Apr 08
    score = (double*)fitness(curr, yR, XR, ncol, nrow, m, rho);
    
    // survived <- (1:m)[order(orig.score)][(1:(m/2))]
    // order the population according to their scores
    for (i=0; i<(*m);i++)
    { index[i] = i;
    }
 

    /*
    // sorting the score using selection sort with O(n^2), return the index of 
    // the scores from the smallest to largest
    for( i=0 ; i<(*m)-1; i++)
    {  min = i;
       for( j = i+1; j<(*m); j++)
       { if(score[j] <score[min])
	 { min = j;
	 }
       }
       tempScore = score[i];
       score[i] = score[min];
       score[min] = tempScore;

       temp = index[i];
       index[i] = index[min];
       index[min] = temp;
    }
    */
    // sorting the score using quicksort, return the index of the scores from the smallest to largest
    quicksort(score, index, left, right); 

    // new <- curr[survived,]
    for (i= 0; i<(*m)/2; i++)
    {  for(j=0; j<(*ncol); j++)
       { newGen[i][j] = curr[index[i]][j];
       }
    }


    //offspring <- get.offspring(new, p, m=m/2, mutation)
    getOffspring(newGen, ncol, (*m)/2, mutation);
    
    //return(list(prev.best=min(orig.score),prev.avg=mean(orig.score), new.gen=combo))
    *prevBest = score[0];
     mean =  (double*)getMean(score, m);
    *prevAvg  = *mean;

}


 
