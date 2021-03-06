\name{replace.map}
\alias{replace.map}
\alias{replacemap.cross}

\title{Replace the genetic map of a cross}

\description{
  Replace the map portion of a cross object.
}

\usage{
replace.map(cross, map)
\method{replacemap}{cross}(object, map)
}

\arguments{
 \item{cross}{An object of class \code{cross}.  See
   \code{\link[qtl]{read.cross}} for details.}
 \item{object}{Same as \code{cross}.}
 \item{map}{A list containing the new genetic map.  This must be the
   same length and with the same marker names as that contained in
   \code{cross}. }
}

\value{The input \code{cross} object with the genetic map replaced by
  the input \code{map}.}

\author{Karl W Broman, \email{kbroman@biostat.wisc.edu} }

\examples{
data(fake.f2)
\dontshow{fake.f2 <- subset(fake.f2, chr=18:19)}
newmap <- est.map(fake.f2)
plot.map(fake.f2, newmap)
fake.f2 <- replace.map(fake.f2, newmap)
}

\seealso{ \code{\link[qtl]{pull.map}}, \code{\link[qtl]{est.map}} }

\keyword{manip}
