int sample(int range);
double* getMin(double* array, int *length);
double* getMean(double* array, int *length);
int* partition(double* array, int* index, int* left, int* right, int* pivotIndex);
void quicksort(double* array, int* index, int* left, int* right);
void printMatrixDouble(double** mat, int *xcol, int *xrow);
void printMatrixInt(int** mat, int *xcol, int *xrow);
void printArrayInt(int* mat, int *length);
void printArrayDouble(double* mat, int *length);
SEXP getListElement(SEXP list, char* str);
double* fitness(int** curr, SEXP yR, SEXP XR, int* ncol, int* row, int *mR, SEXP rho);
void getOffspring(int** newGen, int *p, int halfm, double *mutation);
void onegen(int **curr, SEXP yR, SEXP XR, int *ncol, int* nrow, int *m, double *mutation, int **newGen, double *prevBest, double *prevAvg, SEXP rho);
SEXP sga(SEXP yR, SEXP lengthYR, SEXP XR, SEXP xcolR, SEXP xrowR, SEXP mR, SEXP NR, SEXP startR, SEXP mutationR, SEXP priorR, SEXP checkConvgR, SEXP threshR, SEXP rho);


