pga <- function(y, X, m, N, B=100, mutation=1/ncol(X), start=NULL, prior = 0.35, ...)
{
# performs parallel genetic algorithm for variable selection

# Inputs:

# m        = population size, default set to roughly ncol(X)
# N        = number of generations per path
# B        = number of parallel paths
# mutation = mutation rate, default set to roughly 1/m
# start    = starting population, pretty much useless
# prior    = controls the density of 1s in the initial population

    if (missing(m)) {
      tmp = ncol(X)
      m <- ifelse(tmp%%2==0, tmp, tmp+1)
    }

    y <- data.matrix(y);
    X <- data.matrix(X);
   
    result <- .Call("pga", y,
              as.double(X),
              as.integer(ncol(X)),
              as.integer(nrow(X)),
              as.integer(m),
              as.integer(N),
              as.integer(B), 
              as.double(mutation),
              as.integer(start),
              as.double(prior),
              environment(lsfit), PACKAGE="pga"
              )
    return(result)
             
}
	
