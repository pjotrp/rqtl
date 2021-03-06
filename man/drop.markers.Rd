\name{drop.markers}
\alias{drop.markers}

\title{Drop a set of markers}

\description{
  Drop a vector of markers from the data matrices and genetic maps.
}

\usage{
drop.markers(cross, markers)
}

\arguments{
 \item{cross}{An object of class \code{cross}.  See
   \code{\link[qtl]{read.cross}} for details.}
 \item{markers}{A character vector of marker names.}
}

\value{
  The input object, with any markers in the vector \code{markers} removed
  from the genotype data matrices, genetic maps, and, if applicable, any
  derived data (such as produced by \code{\link[qtl]{calc.genoprob}}).
  (It might be a good idea to re-derive such things after using this
  function.)
}

\examples{
data(listeria)
listeria2 <- drop.markers(listeria, c("D10M44","D1M3","D1M75"))
}

\seealso{ \code{\link[qtl]{drop.nullmarkers}}, \code{\link[qtl]{geno.table}},
  \code{\link[qtl]{clean.cross}} }

\author{Karl W Broman, \email{kbroman@biostat.wisc.edu} }

\keyword{manip}
