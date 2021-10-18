#' Simulated Freeman-Tukey (Hellinger-distance) goodness-of-fit test
#'
#' The `ft_gof()` function implements Monte Carlo simulations to calculate p-values
#' based on the Freeman-Tukey statistic for goodness-of-fit tests for discrete
#' distributions. This statistic is also referred to as the Hellinger-distance.
#' Asymptotically, the Freeman-Tukey GOF test is identical to the Chi-squared
#' GOF test, but for smaller n, results may vary significantly.
#'
#' @param x a numeric vector that contains observed counts for each bin/category.
#' @param p a vector of probabilities of the same length of x. An error is given
#'     if any entry of p is negative or if the sum of p does not equal one.
#' @param reps an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#'@param tolerance sets an upper bound for rounding errors when evaluating
#'    whether a statistic for a simulation is greater than or equal to the
#'    statistic for the observed data. The default is identical to the tolerance
#'    set for simulations in the `chisq.test` function from the `stats`
#'    package in base R.
#'
#'@return A list with class "htest" containing the following components:
#'
#' \item{statistic}{the value of the Freeman-Tukey test statistic (W2)}
#' \item{p.value}{the simulated p-value for the test}
#' \item{method}{a character string describing the test}
#' \item{data.name}{a character string give the name of the data}
#'
#' @export
#'
#' @examples
#' x <- c(15, 36, 17)
#' p <- c(0.25, 0.5, 0.25)
#'
#'ft_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit


ft_gof <- function(x, p, reps = 10000, tolerance = 64 * .Machine$double.eps)  {

  errors_x_p(x, p)

  out <- simulate_p(4, x, p, reps, tolerance)

  names(out$statistic) <- "FT"

  val <- list(p.value = out$p_value,
              statistic = out$statistic,
              method = "Simulated Freeman-Tukey goodness-of-fit test",
              data.name = deparse(substitute(x)),
              class = "htest")

  class(val) <- "htest"

  return(val)

}

