view.movie <- function(obj, truth=NULL, filename, ...)
{
# make a dynamic bubble plot
# by Mu Zhu
# first version = Jan 2002
# this version  = Aug 2007
#
# Inputs:
# obj      = result from pga()
# truth    = for simulation problems only; true variables are plotted with a different symbol
# filename = can't be NULL for dynamic plots
 
  p <- ncol(obj)
  B <- nrow(obj)
  postscript(file=paste(filename, "-movie", ".ps", sep=""), 
    width=8, height=8, horiz=FALSE)
  j.all<-obj[1,]  

  plot(1:p, j.all, type="n", 
   xlab="Variables", 
   ylab="Importance", 
   main=paste("Using B = 1 Parallel Paths"), 
   cex.lab=1.5,
   cex.main=1.5, 
   ylim=c(0,1),
   ...)

  if (!is.null(truth))
  {
   points((1:p)[-truth], j.all[-truth], pch=4)
   points((1:p)[truth], j.all[truth], pch=1, cex=1.5) 
  }
  else
  {
   points((1:p), j.all, pch=1)
  }

  for (i in 2:B)
  {
   j.all<-apply(obj[1:i,], 2, mean)  

   plot(1:p, j.all, type="n", 
   xlab="Variables", 
   ylab="Importance", 
   main=paste("Using B =", i, "Parallel Paths", sep=" "), 
   cex.lab=1.5,
   cex.main=1.5,
   ylim=c(0,1),
    ...)

   if (!is.null(truth))
   {
    points((1:p)[-truth], j.all[-truth], pch=4)
    points((1:p)[truth], j.all[truth], pch=1, cex=1.5) 
   }
   else
   {
    points((1:p), j.all, pch=1)
   }

  }
  dev.off()
}


