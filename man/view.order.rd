\name{view.order}
\alias{view.order}
\title{Create an Order Plot}

\description{ 
Visualizes the result from \code{pga}; it's always used 
together with \code{\link{view.bubble}}. The order plot is very similar to 
the so-called scree plot from principal component analysis. To select 
variables, we look for a big gap in this plot and select the top few 
variables. The bubble plot (see \code{\link{view.bubble}}) will tell us 
which variables are actually on the top.}

\usage{
view.order(obj, grid = F,  filename=NULL, ...)
}

\arguments{
            
\item{obj}{object created by \code{pga}.}      

\item{grid}{if \code{TRUE}, horizontal grid lines are added.}
      
\item{filename}{name to store the output file. If \code{NULL} (default), 
the plot will be made to the standard R graphic device.}

\item{...}{other graphic parameters, such as \code{ylim=c(0,1)}.}

}

\note{     
Please see \link{pga-package} for an introductory overview and examples.}

\seealso{
\code{\link{pga}},
\code{\link{view.bubble}}
}

\author{Mu Zhu, University of Waterloo, Canada.}

\keyword{hplot}

