\name{convert.scanone}
\alias{convert.scanone}

\title{Convert output from scanone for R/qtl version 0.98}

\description{
  Convert the output from scanone from the format used in R/qtl version
  0.97 and earlier to that used in version 0.98 and later.
}

\usage{
\method{convert}{scanone}(object)
}

\arguments{
 \item{object}{Output from the function \code{\link[qtl]{scanone}}, for
   R/qtl version 0.97 and earlier.}
}

\value{
  The same scanone output, but revised for use with R/qtl version 0.98
  and later.  
}

\details{
  Previously, inter-marker locations were named as, for example,
  \code{loc7.5.c3}; these were changed to \code{c3.loc7.5}.
}

\author{Karl W Broman, \email{kbroman@biostat.wisc.edu} }

\examples{
\dontrun{out.new <- convert(out.old)}
}

\seealso{ \code{\link[qtl]{scanone}}, \code{\link[qtl]{convert.scantwo}} }

\keyword{manip}
