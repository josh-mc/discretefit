
#' Simulated log-likelihood-ratio (G^2) goodness-of-fit test
#'
#' The `g_gof()` function implements Monte Carlo simulations to calculate p-values
#' based on the log-likelihood-ratio statistic for goodness-of-fit tests for discrete
#' distributions. In this context, the log-likelihood-ratio statistic is often referred
#' to as the G^2 statistic. Asymptotically, the G^2 GOF test is identical to the Chi-squared
#' GOF test, but for smaller n, results may vary significantly.
#'
#' @param x a numeric vector that contains observed counts for each bin/category.
#' @param p a vector of probabilities of the same length of x. An error is given
#'     if any entry of p is negative or if the sum of p does not equal one.
#' @param reps an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#'@param tolerance sets an upper bound for rounding errors when evaluation equality.
#'
#'@return A list with class "htest" containing the following components:
#'
#' \item{statistic}{the value of the log-likelihood-ratio test statistic (G2)}
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
#'g_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit


g_gof <- function(x, p, reps = 10000, tolerance = 64 * .Machine$double.eps)  {

  errors_x_p(x, p)

  out <- simulate_p(4, x, p, reps, tolerance)

  names(out$statistic) <- "G2"

  val <- list(p.value = out$p_value,
              statistic = out$statistic,
              method = "Simulated log-likelihood-ratio goodness-of-fit test",
              data.name = deparse(substitute(x)),
              class = "htest")

  class(val) <- "htest"

  return(val)

}

