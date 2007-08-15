summarize.PGAsim <- function(rslt, truth, name="YourMethod")
{
# summarizes simulation results; hard performanace metric
# by Mu Zhu
# Jan 2005
 q <- length(truth)
 extra <- apply(rslt[,-truth],1,sum)
 miss <- q - apply(rslt[,truth],1,sum)
 correct <- (extra==0) & (miss==0)
 x<-data.frame(
 perc.correct=mean(correct))
 dimnames(x)[[1]]<-name
 return(x)
}

