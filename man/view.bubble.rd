\name{view.bubble}
\alias{view.bubble}
\title{Create a Bubble Plot}

\description{
Visualizes the result from \code{pga}; it's always used together with 
\code{\link{view.order}}.}

\usage{
view.bubble(obj, truth=NULL, grid=F, filename=NULL, ...)
}

\arguments{
      
\item{obj}{object created by \code{pga}.}      

\item{truth}{only useful for simulations. A list of truly revelant 
variables, e.g., \code{truth=c(1,3,5,7,9)}. This allows the function to 
use a different symbol for these variables. }

\item{grid}{if \code{TRUE}, horizontal grid lines are added.}
      
\item{filename}{name to store the output file. If \code{NULL} (default), 
the plot will be made to the standard R graphic device.}

\item{...}{other graphic parameters, such as \code{ylim=c(0,1)}.}
}

\note{     
Please see \link{pga-package} for an introductory overview and examples.}

\seealso{
\code{\link{pga}}, 
\code{\link{view.order}}
}

\author{Mu Zhu, University of Waterloo, Canada.}

\keyword{hplot}    

