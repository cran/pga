sga <- function(y, X, m, N, start=NULL, mutation=1/ncol(X), prior=0.35, check.convg=FALSE, thresh=0.05)
{
# performs single genetic algorithm for variable selection

     y <- data.matrix(y);
     X <- data.matrix(X);
 
    if (missing(m)) {
      tmp = ncol(X)
      m <- ifelse(tmp%%2==0, tmp, tmp+1)
    }
     
     ans<- .Call("sga", 
      y,
      as.integer(length(y)),
      as.double(X), 
      as.integer(ncol(X)),
      as.integer(nrow(X)),
      as.integer(m), 
      as.integer(N), 
      as.integer(start), 
      as.double(mutation), 
      as.double(prior),
      as.logical(check.convg),
      as.double(thresh),
      environment(lsfit), PACKAGE="pga")
   
    
     return (ans)


} 
	
