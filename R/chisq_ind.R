#' Simulated Chi-squared test of independence
#'
#' The `chisq_ind()` function implements Monte Carlo simulations to calculate p-values
#' based on the Chi-squared statistic for tests of independence for r x c contingency
#' tables.
#'
#' For contingency tables with fixed margins, `chisq_ind()` utilizes RCONT3, an
#' algorithm that improves upon the algorithm by Boyett (1979; also see Agresti, Wackerly, and Boyett,
#' 1979) referred to as RCONT. For details see the vignette on contingency tables
#' with fixed margins. To increase performance, this algorithm also uses a permuted
#' congruential generator (PCG) to generate pseudo random numbers (O'Neil, 2014).
#' However, the seed can still be set via `set.seed()`. The C++ header file for the PCG
#' pseudo random number generator is by O'Neil and PCG Project contributors.
#'
#' @param x - a r x c contingency table configured as a matrix with integral values.
#' @param reps - an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#' @param tolerance - sets an upper bound for rounding errors when evaluating
#'    whether a statistic for a simulation is greater than or equal to the
#'    statistic for the observed data. The default is identical to the tolerance
#'    set for simulations in the `chisq.test` function from the `stats`
#'    package in base R.
#'
#' @return A list with class "htest" containing the following components:
#'
#' \item{statistic}{the value of the Chi-squared test statistic}
#' \item{p.value}{the simulated p-value for the test}
#' \item{method}{a character string describing the test}
#' \item{data.name}{a character string give the name of the data}
#'
#' @references
#'
#' Agresti, A., Wackerly, D., & Boyett, J. M. (1979). Exact conditional tests
#'     for cross-classifications: approximation of attained significance levels.
#'     Psychometrika, 44(1), 75-83.
#'
#' Boyett, J. M. (1979). Algorithm AS 144: Random r × c tables with
#'     given row and column totals. Journal of the Royal Statistical Society.
#'     Series C (Applied Statistics), 28(3), 329-332.
#'
#'O’Neill, M. E. (2014). PCG: A family of simple fast space-efficient statistically
#'    good algorithms for random number generation. Harvey Mudd College, Department of
#'    Computer Science, Technical Report.
#'    https://www.cs.hmc.edu/tr/hmc-cs-2014-0905.pdf
#'
#' @export
#'
#' @examples
#'
#'
#'
#'
chisq_ind <- function(x, reps = 10000, tolerance = 0)  {

  n <- sum(x)
  nr <- as.integer(nrow(x))
  nc <- as.integer(ncol(x))
  sr <- rowSums(x)
  sc <- colSums(x)
  E <- outer(sr, sc, "*") / n

  STATISTIC <- sum((x - E)^2 / E)

  PVAL <- ind_fixed(reps = reps,
          r_sums = sr,
          c_sums = sc,
          as.numeric(E),
          seed = sample.int(.Machine$integer.max, 1),
          statistic = STATISTIC,
          tolerance = tolerance)

  val <- list(p.value = PVAL,
              statistic = STATISTIC,
              method = "Simulated Chi-squared test of independence",
              data.name = deparse(substitute(x)),
              class = "htest")

  class(val) <- "htest"

  return(val)
}


