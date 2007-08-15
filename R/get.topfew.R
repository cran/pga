get.topfew <- function(obj, num=5)
{
# pick the top few numbers of variables in the bubble plot
# by Mu Zhu
# first version = Jan 2005
# this version  = Aug 2007
 judge <- apply(obj,2,mean)
 thresh <- judge[order(judge,decreasing=TRUE)][num]
 ans <- which(judge >= thresh)
 return(ans)
}

