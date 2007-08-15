\name{sga}

\alias{sga}

\title{Single-path Genetic Algorithm for Variable Selection}

\description{
The SGA algorithm as described in \cite{Technometrics} 48, page 493, Table 
5. 

Before running parallel evolution, it is sometimes useful to get a rough 
idea of how many generations to evolve in each universe. To do so, one can 
use \code{sga} with \code{check.convg=TRUE}; see example below. Otherwise, 
this function is often NOT used directly.
}
\synopsis{
sga(y, X, m, N, start = NULL, mutation=1/ncol(X), prior = 0.35, check.convg = FALSE, thresh=0.05)
}
\usage{
sga(y, X, m, N, start = NULL, mutation=1/ncol(X), prior = 0.35, check.convg = FALSE, thresh = 0.05)
sga(y, X, N=50)
sga(y, X, N=200, check.convg=TRUE)
}

\arguments{

\item{y}{an \code{n}-by-\code{1} response vector.}

\item{X}{an \code{n}-by-\code{p} matrix; each column is a
candidate predictor variable.}

\item{m}{population size in each universe, default = \code{ncol(X)} or
\code{ncol(X)+1}, depending on whether \code{ncol(X)} is even or odd.}

\item{N}{number of generations to evolve in each universe; this needs to
be fairly short to prevent each evolutionary path from converging.}

\item{start}{the starting population; mostly useless, default = 
\code{NULL}.}

\item{mutation}{mutation rate; this can be a vector of length \code{N} if 
a different mutation rate is needed for each generation 
\code{t=1,2,...,N}; default = \code{1/p} for all \code{t=1,2,...,N}.}

\item{prior}{prior probability which controls the density of 1's in the 
initial population, default = \code{0.35}, but if there is some prior 
information that the number of relevant variables is large, then it can be 
more efficient to use a higher \code{prior}, e.g., \code{prior=0.7}.}

\item{check.convg}{\code{TRUE} if running \code{sga} initially
to find out the number of generations needed for a single path to 
converge; \code{FALSE} otherwise.}
     
\item{thresh}{a prespecified threshold; if the entropy of the population 
falls below \code{thresh}, the evolutionary algorithm is deemed to have 
converged; see \cite{Technometrics} 48, page 495, Section 3.2.} 

} 

\value{

\item{ans}{returned only if \code{check.convg=TRUE}; it is the number of 
iterations needed to achieve convergence.}

\item{popn}{last-generation population after \code{N} generations of 
evolution, returned as an \code{m}-by-\code{p} binary matrix.}

\item{combo.gene}{a \code{p}-by-\code{1} vector, whose \code{j}-th 
element is the frequency that variable \code{j} \dQuote{shows up} in the 
last-generation population.}

\item{best}{a \code{p}-by-\code{1} binary vector, representing the best 
solution after \code{N} generations of evolution. If the evolutionary 
algorithm has converged in the entropy sense, then \code{combo.gene} is 
expected to be the same as \code{best} after rounding; see example below.}

\item{optval}{used during code development; ignore.}

\item{convg}{same as above.}

\item{perf}{same as above.}

}

\seealso{\code{\link{pga}} }

\references{Zhu M, Chipman HA (2006). Darwinian evolution in parallel 
universes: A parallel genetic algorithm for variable selection. 
\cite{Technometrics}, 48(4), 491--502.
}

\author{Dandi Qiao and Mu Zhu, University of Waterloo, Canada.}

\examples{
## simulate some data
sigma <- 1
N <- 50
d <- 10
truth <- c(2,5,8)
beta <- rep(0,d)
beta[truth] <- c(1,1,1) 
X <- matrix(rnorm(N*d), N, d)
y <- X \%*\% beta + sigma*rnorm(N)

## get a rough idea of how many generations are needed for
## the evolutionary algorithm to converge (in the entropy sense) 
check=numeric(5)
for (i in 1:5){
 check[i] = sga(y, X, N=200, check.convg=TRUE)$ans
}
round(mean(check))
## if round(mean(check)) above is equal to 20, then one often runs
## just 10 generations in each parallel universe to prevent each path
## from converging ...

## run a long evolutionary path and identify the best solution, 
## but this is often not too useful ... however, from the example
## below, you will see that, if evolution has converged in the
## entropy sense, then $best and $combo.gene are not
## going to be very different ...
stuff<-sga(y, X, N=200)
stuff$best
round(stuff$combo.gene)
}

\keyword{optimize}
\keyword{multivariate}

