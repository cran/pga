\name{get.pga.ans}
\alias{get.pga.ans}
\title{Select Variables Based on Largest Gap in the Bubble Plot}

\description{ 
Find the variables floating on the top of the bubble plot.
}

\usage{
get.pga.ans(obj)
}

\arguments{
\item{obj}{object created by \code{pga}.}
}

\value{
If the largest gap is less than \code{0.8225/sqrt(B)} (where \code{B} is 
the total number of parallel paths used), a warning message will be 
printed that the gap is not statistically significant. See 
\cite{Technometrics}, 48, page 496, equation (7).}

\seealso{
\code{\link{pga}},
\code{\link{view.bubble}},
\code{\link{get.topfew}}
}

\author{Mu Zhu, University of Waterloo, Canada.}

\keyword{misc}
