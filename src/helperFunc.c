
#include "pga.h"

/*these are the helper functions used*/

//generate a number in [1, range]
int sample(int range)
{  int r = 1+(int)((range*rand()/(RAND_MAX+1.0)));
   return r;
}

//get the minimum value in the arrange of given length
double* getMin(double* array, int *length)
{  double* min =  (double*)R_alloc(1, sizeof(double));
   *min =array[0];
   int i;
   for( i=0; i<(*length); i++)
   { if(*min > array[i])
     { *min = array[i];
     }
   }

   return(min);
}
 
//get the average of the values in the array of given length
double* getMean(double* array, int *length)
{  int i;
   double* mean=(double*)R_alloc(1, sizeof(double));
   *mean =0;
   for (i =0; i<(*length); i++)
   { *mean  += array[i];
   }
   *mean = *mean/(double)(*length);
   return mean;
}

// A helper function for quicksort
int* partition(double* array, int* index, int* left, int* right, int* pivotIndex)
{   double pivotValue = array[(*pivotIndex)];
    int storeIndex = (*left)-1;
    int* storeIndexPlus = (int*) R_alloc(1, sizeof(int));
    
    int i;
    double temp;
    int tempIndex;
 
    for(i=(*left); i<(*right); i++)
    {   if(array[i] <= pivotValue)
	{  storeIndex++;
           //swap values at storeIndex and i
           temp = array[storeIndex];
	   array[storeIndex] = array[i];
	   array[i] = temp;

	   tempIndex = index[storeIndex];
	   index[storeIndex] = index[i];
	   index[i] = tempIndex;
	}
    }
    // swap values at soreIndex+1 and right
    temp = array[storeIndex+1];
    array[storeIndex+1]=array[(*right)];
    array[(*right)]= temp;

    tempIndex = index[storeIndex+1];
    index[storeIndex+1] = index[(*right)];
    index[(*right)] = tempIndex;
    
    *storeIndexPlus = storeIndex +1;
    return storeIndexPlus;
}



//quicksort for an array
void quicksort(double* array, int* index, int* left, int* right)
{  int* pivotNewIndex = (int*) R_alloc(1, sizeof(int));
   int* pMinus = (int*)R_alloc(1, sizeof(int));
   int* pPlus = (int*) R_alloc(1, sizeof(int));
   if((*right)>(*left))
   {  pivotNewIndex = (int*) partition(array, index, left, right, right);
      *pMinus = (*pivotNewIndex)-1;
      *pPlus = (*pivotNewIndex)+1;
      quicksort(array,index, left, pMinus);
      quicksort(array,index,  pPlus, right);
   }

}

/*These print functions are for debugging purpose*/

void printMatrixDouble(double** mat, int *xcol, int *xrow)
{   int i, j; 
    Rprintf("printing matrix: \n");
    for(i=0; i<(*xrow); i++)
    {  for (j = 0 ; j<(*xcol); j++)
       { Rprintf("%f ", mat[i][j]);
       }
       Rprintf("\n");
    }
} 

void printMatrixInt(int** mat, int *xcol, int *xrow)
{   int i, j; 
   Rprintf("printing matrix: \n");
    for(i=0; i<(*xrow); i++)
    {  for (j = 0 ; j<(*xcol); j++)
       {  Rprintf("%d ", mat[i][j]);
       }
      Rprintf("\n");
    }
} 

void printArrayInt(int* mat, int *length)
{   int i, j; 
    Rprintf("printing array: \n");
    
      for (j = 0 ; j<(*length); j++)
       { Rprintf("%d ", mat[j]);
       }
       Rprintf("\n");
    
} 

void printArrayDouble(double* mat, int *length)
{   int i, j; 
    Rprintf("printing array: \n");
    
      for (j = 0 ; j<(*length); j++)
       {  Rprintf("%f ", mat[j]);
       }
   Rprintf("\n");
    
} 

