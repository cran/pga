get.pga.ans <- function(obj)
{
# make automatic variable selection decisions based on the largest
# gap in the bubble plot
# by Mu Zhu
# first version = Jan 2005
# this version  = Aug 2007
 judge<-apply(obj,2,mean)
 B <- nrow(obj)
 x <- sort(judge, decreasing=TRUE); n<-length(x)
 gap <-   x[1:(n-1)] - x[2:n]; m<-max(gap)
 number <-  which(gap==m)
 if (m < 0.8225/sqrt(B)) cat("Gap not significant!\n")
 ans<-which(judge>=judge[order(judge,decreasing=TRUE)][number])
 return(ans)
}
