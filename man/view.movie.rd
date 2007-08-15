\name{view.movie}
\alias{view.movie}
\title{Create a Dynamic Bubble Plot}

\description{Visualizes the result from \code{pga}. This function creates 
a postscript file. To view the resulting \dQuote{postscript movie}, choose 
the \dQuote{full screen} or \dQuote{fit in window} option from your 
postscript viewer and hold down the \dQuote{page down} button. }

\usage{
view.movie(obj, truth=NULL, filename, ...)
}

\arguments{
      
\item{obj}{object created by \code{pga}.}      
      
\item{truth}{only useful for simulations. A list of truly revelant 
variables. This allows the function to use a different symbol for these 
variables. }
      
\item{filename}{name to store the output file. For example, if 
\code{filename="myPGA"}, then a postscript (.ps) file will be created 
with the name \dQuote{myPGA-movie.ps}; the file will consist of a 
total of \code{B} individual bubble plots, each serving as a frame in the 
movie.}

\item{...}{other graphic parameters, such as \code{ylim=c(0,1)}.}

}

\note{
Please see \link{pga-package} for an introductory overview and examples.}

\seealso{
\code{\link{pga}}, \code{\link{view.bubble}}
}

\author{Mu Zhu, University of Waterloo, Canada.}

\references{ 
Zhu M, Chipman HA (2006). \cite{Technometrics}, 48, page 501, Section 5. 
}

\keyword{hplot}    

