\name{pga}
\alias{pga}

\title{Parallel Genetic Algorithm for Variable Selection}

\description{ 
The PGA algorithm as described in \cite{Technometrics} 48, page 494, Table 6.
}
\synopsis{
pga(y, X, m, N, B=100, mutation=1/ncol(X), start = NULL, prior = 0.35)
}
\usage{
pga(y, X, m, N, B=100, mutation=1/ncol(X), start = NULL, prior = 0.35)
pga(y, X, N=8, B=25)
}

\arguments{
     
\item{y}{an \code{n}-by-\code{1} response vector.}
     
\item{X}{an \code{n}-by-\code{p} matrix; each column is a 
candidate predictor variable.}
     
\item{m}{population size in each universe. If missing, default = 
\code{ncol(X)} or \code{ncol(X)+1}, depending on whether \code{ncol(X)} is 
even or odd.}
     
\item{N}{number of generations to evolve in each universe; this needs to 
be fairly short to prevent each evolutionary path from converging. For an 
example of how to determine the proper \code{N}, see \code{\link{sga}}.}
     
\item{B}{number of parallel paths or parallel universes.}
     
\item{mutation}{mutation rate; this can be a vector of length \code{N} if 
a different mutation rate is needed for each generation 
\code{t=1,2,...,N}; default = \code{1/p} for all \code{t=1,2,...,N}.}
     
\item{start}{the starting population; mostly useless, default = 
\code{NULL}.}
     
\item{prior}{prior probability which controls the density of 1's in the 
initial population, default = \code{0.35}, but if there is some prior 
information that the number of relevant variables is large, then it can be 
more efficient to use a higher \code{prior}, e.g., \code{prior=0.7}.}

}

\value{

Returns a \code{B}-by-\code{p} matrix. Element \code{(b,j)} of the matrix 
is the frequency that variable \code{j} \dQuote{shows up} in the 
last-generation population of universe \code{b}.

}

\note{     
Please see \link{pga-package} for an introductory overview and examples.}

\seealso{\code{\link{sga}}}

\references{
Zhu M, Chipman HA (2006). Darwinian evolution in parallel 
universes: A parallel genetic algorithm for variable selection. 
\cite{Technometrics}, 48(4), 491 -- 502. 

Zhu M (2008). Kernels and ensembles: Perspectives on statistical learning. 
\cite{The American Statistician}, 62(2), 97 -- 109.
} 

\author{Dandi Qiao and Mu Zhu, University of Waterloo, Canada.}

\keyword{optimize}    
\keyword{multivariate}    

