view.order <- function(obj, grid = F,  filename=NULL, ...)
{
# make an order plot
# by Mu Zhu
# first version = Jan 2002
# this version  = Aug 2007
#
# Inputs:
# obj      = results from pga()
# filename = if NULL, plots to standard R graphics device
# grid     = whether horizontal grid lines should be turned on or not

  if (!is.null(filename)) {
   postscript(file=paste(filename, "-order.ps", sep=""), 
    height=8, width=8, horiz=FALSE)
  }

  j.all = apply(obj, 2, mean)
  num = nrow(obj)
  
  plot(j.all[order(-j.all)], 
    xlab="Ordered Variables", 
    ylab="Importance",
    main=paste("Order Plot: B=", num, "Parallel Paths", sep=" "), 
    cex.lab=1.5, cex.main=1.5, ...)
  if (grid) abline(h=(1:9)/10, col="red", lty=2)
  if (!is.null(filename)) {
    dev.off()
  }
}

