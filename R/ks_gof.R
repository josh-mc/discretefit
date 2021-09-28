
#' Simulated p-values for Kolmogorov-Smirnov goodness-of-fit
#'
#' @param x - a numeric vector that contains counts for each discrete variable.
#' @param p - a vector of probabilities of the same length of x. An error is given
#'     if any entry of p is negative or if the sum of p does not equal one.
#' @param reps - an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#'
#' @return A number representing the p-value.
#' @export
#'
#' @examples
#' x <- c(15, 36, 17)
#' p <- c(0.25, 0.5, 0.25)
#'
#' ks_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit
#'

ks_gof <- function(x, p, reps = 10000)  {

  errors_x_p(x, p)

  out <- simulate_p(3, x, p, reps)

  return(out)

}
