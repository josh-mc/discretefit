
#' Simulated p-values for root mean squared goodness-of-fit
#'
#' @param x - a numeric vector.
#' @param p - a numeric vector representing the reference distribution.
#' @param reps - an integer specifying the number of simulations. The default is set to 10,000
#'     which is appropriate for exploratory analysis. A higher number of simulations
#'     should be selected for final analysis.
#'
#' @return A number representing the p-value.
#' @export
#'
#' @examples
#' x <- c(15, 36, 17)
#' p <- c(0.25, 0.5, 0.25)
#'
#' rms_gof(x, p)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit
#'
rms_gof <- function(x,
                    p,
                    reps = 10000)  {

  errors_x_p(x, p)

  out <- simulate_p(1, x, p, reps)

  return(out)

}
