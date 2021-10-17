#' Simulated Cramer-von Mises goodness-of-fit test
#'
#' The `cvm_gof()` function implements Monte Carlo simulations to calculate p-values
#' based on the Cramer-von Mises statistic for goodness-of-fit tests for discrete
#' distributions.
#'
#' @param x a numeric vector that contains observed counts for each bin/category.
#' @param p a vector of probabilities of the same length of x. An error is given
#'     if any entry of p is negative or if the sum of p does not equal one.
#' @param reps an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#'@param tolerance sets an upper bound for rounding errors when evaluating equality.
#'
#' @return A number representing the p-value.
#' @export
#'
#' @examples
#' x <- c(15, 36, 17)
#' p <- c(0.25, 0.5, 0.25)
#'
#'cvm_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit


cvm_gof <- function(x, p, reps = 10000, tolerance = 1 - 64 * .Machine$double.eps)  {

  errors_x_p(x, p)

  out <- simulate_p(6, x, p, reps, tolerance)

  return(out)

}