view.bubble <- function(obj, truth=NULL, grid=F, filename=NULL, ...)
{
# make a bubble plot
# by Mu Zhu
# first version = Jan 2002
# this version  = Aug 2007
#
# Inputs:
# obj      = result from pga()
# truth    = for simulation only; true variables plotted w/ different symbol
# filename = if NULL, plot to standard R graphics window
# grid     = whether horizontal grid is turned on or not in the plot

 if (!is.null(filename)) {
  postscript(file=paste(filename, "-bubble", ".ps", sep=""), 
   width=8, height=8, horiz=FALSE)
 }

 p = ncol(obj)          # number of candidate variables
 j = apply(obj,2,mean)
 num = nrow(obj)        # number of parallel paths

 plot(1:p, j, type="n", 
  xlab="Variables", 
  ylab="Importance", 
  main=paste("Bubble Plot: B =", num, "Parallel Paths", sep=" "), 
  cex.lab=1.5,
  cex.main=1.5,
    ...)
 if (grid) abline(h=(1:9)/10, col="red", lty=2)
 if (!is.null(truth))
 {
  points((1:p)[-truth], j[-truth], pch=4)
  points((1:p)[truth], j[truth], pch=1, cex=1.5) 
 }
 else
 {
   points((1:p), j, pch=4)
 }
 if (!is.null(filename)) {
  dev.off()
 }
}


