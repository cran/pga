\name{pga}
\alias{pga-package}
\docType{package}

\title{Variable Selection by Darwinian Evolution in Parallel Universes}

\description{PGA stands for \dQuote{parallel genetic algorithm}; it is 
an ensemble method for variable selection. }

\details{
In order to perform variable selection, we must answer two difficult 
questions. First, what criterion should we use to assess candidate 
solutions? Second, what search algorithm should we use to find the 
\dQuote{best} candidate, where \dQuote{best} is measured by the chosen 
criterion?

For the second question, it is clear (at least given the current state of 
affairs) that we cannot in general perform an exhaustive search, because 
the number of possible solutions is often so large that we cannot finish 
evaluating all of them in less than 100 years even on a very fast 
computer. We must (are forced to) use various heuristic algorithms, e.g., 
a greedy stepwise search algorithm, or a stochastic search algorithm such 
as simulated annealing or the genetic algorithm.

The first question is perhaps even more fundamental. Clearly, if we use a 
wrong criterion, we will not find the right solution even if we could 
perform an exhaustive search. The Akaike information criterion (AIC) and 
the Bayesian information criterion (BIC) are both widely-used criteria for 
variable selection, but it is well-known that AIC tends to select too many 
variables whereas BIC tends to select too few. Finding the correct 
information criterion has remained a very difficult problem and 
researchers are now beginning to believe that perhaps no such magic 
information criterion could ever be found.

PGA is a simple algorithm that can significantly \dQuote{boost up} the 
performance of a wrong information criterion such as the AIC. Here, we 
describe how PGA works in a nutshell: Create a number of parallel 
universes. In each universe, run an 
evolutionary algorithm to optimize a criterion of the AIC type, but do so 
for just a few generations. Whatever it is, there will be a current best 
solution in each universe when we stop. For example, the current best 
subset in universe 1 may be \code{x3, x8, x10}; in universe 2, it may be 
\code{x1, x3, x8, x15}; in universe 3, perhaps \code{x3, x5, x8, x11}; and 
so on. Take a majority vote and select those variables that \dQuote{show 
up} in significantly more universes than the rest. In the example above, 
this would be \code{x3, x8}. Simple as it may sound, PGA has been shown to 
be a very competitive and extremely easy-to-use variable-selection tool in 
practice. 
}

\note{ 
What do we mean by \dQuote{a criterion of the AIC type} above? 
Basically, we are referring to criteria that tend to over-select 
variables, e.g., AIC or the generalized cross-validation (GCV). In the 
current implementation, the GCV criterion is used instead of the AIC, but 
it is well-known that the two are nearly equivalent to each other as long 
as the sample size is not too small. 

Currently, only the GCV criterion for linear regression is implemented. An 
internal function \code{fitness} drives the evolution by computing the GCV 
score for each member of a given population. Similar functions can be 
written for other models. For example, one can easily write another 
\code{fitness} function to compute the AIC score for Cox's proportional 
hazard regression. This may be added in future versions. }

\references{
Zhu M, Chipman HA (2006). Darwinian evolution in parallel universes: A 
parallel genetic algorithm for variable selection. \cite{Technometrics}, 
48(4), 491 -- 502.

Zhu M (2008). Kernels and ensembles: Perspectives on statistical learning. 
\cite{The American Statistician}, 62(2), 97 -- 109. [The relevant section 
is Section 4.3.]
} 

\seealso{
\code{\link{pga}, \link{view.bubble}, \link{view.order}, 
\link{view.movie}, \link{get.pga.ans}, \link{get.topfew}}
}

\keyword{models} 
\keyword{multivariate} 

\author{
Dandi Qiao and Mu Zhu, University of Waterloo, Canada. Dandi is the 
principal C programmer for the package. 
}

\examples{
## simulate some data, needles in a haystack
set.seed(2007)
sigma <- 1
N <- 120
d <- 100                           # a large problem, 100 variables
truth <- c(15,30,45,60,75,90)      # only 6 are in the model
beta <- rep(0,d)
beta[truth] <- c(1,1,2,2,3,3)      # different signal-to-noise ratio
X <- matrix(rnorm(N*d), N, d)
y <- X \%*\% beta + sigma*rnorm(N)

## run PGA
rslt <- pga(y, X, N=15, B=25)

## make a movie
view.movie(rslt, truth=c(15,30,45,60,75,90), filename="myPGA")
 
## make bubble and order plots
par(mfrow=c(2,2))
view.bubble(rslt, truth=c(15,30,45,60,75,90), grid=TRUE, ylim=c(0,1))
view.order(rslt, grid=TRUE, ylim=c(0,1))
 
## get answer
get.pga.ans(rslt)
get.topfew(rslt, num=6)

## simulate 25 times (smaller, toy example) and 
## calculate how often PGA succeeds ...
sigma <- 1
N <- 50
d <- 10
truth <- c(2,5,8)
beta <- rep(0,d)
beta[truth] <- c(1,1,1)
rslt.hard <- rslt.soft <- matrix(0, 25, d)
for (i in 1:25) {
set.seed(i)
X <- matrix(rnorm(N*d), N, d)
y <- X \%*\% beta + sigma*rnorm(N)
rslt <- pga(y, X, N=6, B=25)
ans.hard<-get.pga.ans(rslt); print(ans.hard)
ans.soft<-get.topfew(rslt, num=3); print(ans.soft)
rslt.hard[i,ans.hard]<-1
rslt.soft[i,ans.soft]<-1
}
sim.rslt <- rbind(
summarize.PGAsim(rslt.hard, truth=c(2,5,8), name="PGAhard"),
summarize.PGAsim(rslt.soft, truth=c(2,5,8), name="PGAsoft"))
sim.rslt
}

\keyword{multivariate}    
\keyword{optimize}    


