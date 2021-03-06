\name{calc.penalties}
\alias{calc.penalties}

\title{Calculate LOD penalties}

\description{
  Derive penalties for the penalized LOD scores (used by
  \code{\link[qtl]{stepwiseqtl}}) on the basis of permutation results
  from a two-dimensional, two-QTL scan (obtained by \code{\link[qtl]{scantwo}}).
}

\usage{calc.penalties(perms, alpha=0.05, lodcolumn)}

\arguments{
 \item{perms}{Permutation results from \code{\link[qtl]{scantwo}}.}
 \item{alpha}{Significance level.}
 \item{lodcolumn}{If the scantwo permutation results contain LOD scores for
    multiple phenotypes, this argument indicates which to use in the
    summary.  This may be a vector.  If missing, penalties for all
 phenotypes are calculated.}
}

\details{
  Thresholds derived from \code{\link[qtl]{scantwo}} permutations (that
  is, for a two-dimensional, two-QTL genome scan) are used to calculate
  penalties on main effects and interactions.  

  The main effect penalty is the 1-\code{alpha} quantile of the null
  distribution of the genome-wide maximum LOD score from a single-QTL
  genome scan (as with \code{\link[qtl]{scanone}}).

  The "heavy" interaction penalty is the 1-\code{alpha} quantile of
  the null distribution of the maximum interaction LOD score (that is,
  the \eqn{\log_{10}}{log10} likelihood ratio comparing the best model
  with two interacting QTL to the best model with two additive QTL) from
  a two-dimensional, two-QTL genome scan (as with
  \code{\link[qtl]{scantwo}}).

  The "light" interaction penality is the difference between the
  \code{"fv1"} threshold from the \code{\link[qtl]{scantwo}}
  permutations (that is, the 1-\code{alpha} quantile of the LOD score
  comparing the best model with two interacting QTL to the best
  single-QTL model) and the main effect penalty.
}

\value{
  Vector of three values indicating the penalty on main
  effects and heavy and light penalties on interactions,
  or a matrix of such results, with each row corresponding to a
  different phenotype.
}

\author{Karl W Broman, \email{kbroman@biostat.wisc.edu} }

\examples{
data(fake.f2)
\dontshow{fake.f2 <- subset(fake.f2, chr=18:19)}
fake.f2 <- calc.genoprob(fake.f2, step=5)
out.2dim <- scantwo(fake.f2, method="hk")

# permutations
\dontshow{permo.2dim <- scantwo(fake.f2, method="hk", n.perm=2)}
\dontrun{permo.2dim <- scantwo(fake.f2, method="hk", n.perm=1000)}
summary(permo.2dim, alpha=0.05)

# penalties
calc.penalties(permo.2dim)
}

\references{
  Manichaikul, A., Moon, J. Y., Sen, \'S, Yandell, B. S. and Broman,
  K. W. (2009) A model selection approach for the identification of
  quantitative trait loci in experimental crosses, allowing
  epistasis. \emph{Genetics}, to appear.
}

\seealso{ \code{\link[qtl]{scantwo}}, \code{\link[qtl]{stepwiseqtl}} }

\keyword{utilities}
