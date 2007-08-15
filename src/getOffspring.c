#include "pga.h"

//---------------------------------------------------------------
//  getOffSpring
//      function for obtaining the second half of the next generation
//      p:  number of genes per individual
//      halfm: half of the total population size in a generation
//      newGen: the matrix of current generation, kept in the order of their scores from max to min
//      mutation: mutation rate
//--------------------------------------------------------------------   
void getOffspring(int** newGen, int *p, int halfm, double *mutation)
{    
    int i,j;
    int* temp;
    int father;
    int mother;
    int breakpt;
    double u;
    int pos;

    for(i=0; i<halfm; i++)
    { father = sample(halfm)-1;    // father<- sample(1:m, size=1), here father <-[0. halfm-1]
      mother = sample(halfm)-1;    // mother <- sample(1:m, size=1), here mother<-[0, halfm-1]
      breakpt = sample((*p))-1;      // breakpt <- sample(1:p, size=1), here breakpt<- [0, p-1]

      // tmp <- as.vector(c(X[father,][1:breakpt],X[mother,][(breakpt+1):p]))
      // breakpt here = breakpt -1 in R code
      for(j=0; j<breakpt+1; j++)
      { newGen[i+(halfm)][j] = newGen[father][j];
      }
      for(j=breakpt+1; j<(*p); j++)
      { newGen[i+(halfm)][j]= newGen[mother][j];
      }

      u =  rand()/(RAND_MAX+1.0); //runif(1, 0,1)

      // pos <- sample(1:p, size=1)
      // tmp[pos] <- 1 - tmp[pos]
      if (u < (*mutation))
      { pos = sample(*p)-1;
        newGen[i+(halfm)][pos] = 1- newGen[i+(halfm)][pos];
      }
    }
}
