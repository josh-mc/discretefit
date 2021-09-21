
#' Simulated p-values for Chi Squared goodness-of-fit
#'
#' @param x - a numeric vector that contains counts for each bin/category.
#' @param p - a numeric vector that contains probabilities for each bin/category. .
#' @param reps - an integer specifying the number of Monte Carlo simulations to perform.
#'     The default is set to 10,000 which is appropriate for exploratory analysis.
#'     A higher number of simulations should be selected for final analysis.

#'
#' @return
#' @export
#'
#' @examples
#' x <- c(15, 36, 17)
#' p <- c(0.25, 0.5, 0.25)
#'
#' chisq_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit


chisq_gof <- function(x, p, reps = 10000)  {

  errors_x_p(x, p)

  out <- chisq_gof_cpp(x, p, reps)

  return(out)

}
