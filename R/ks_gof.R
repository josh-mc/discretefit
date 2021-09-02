
#' Simulated p-values for Kolmogorov-Smirnov goodness-of-fit
#'
#' @param x - a numeric vector that contains counts for each discrete variable.
#' @param p - a vector of probabilities of the same length of x. An error is given
#'     if any entry of p is negative or if the sum of p does not equal one.
#' @param reps - an integer specifying the number of Monte Carlo simulations. The default
#'     is set to 10,000 which may be appropriate for exploratory analysis. A higher
#'     number of simulation should be selected for more precise results.
#'
#' @return
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

  if(length(x) != length(p)) {
    stop("The vectors x and p must be the same length.")
  }

  if(sum(p < 0) >= 1) {
    stop("The vector p cannot contain negative probabilities.")
  }

  if(sum(p) != 1) {
    stop("The probilities in vector p must sum to one.")
  }

  out <- ks_gof_cpp(x, p, reps)

  return(out)

}
