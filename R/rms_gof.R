
#' Simulated p-values for root mean squared goodness-of-fit
#'
#' @param x - a numeric vector.
#' @param y - a numeric vector representing the reference distribution.
#' @param reps - an integer specifying the number of simulations. The default is set to 10,000
#'     which is appropriate for exploratory analysis. A higher number of simulations
#'     should be selected for final analysis.
#'
#' @return
#' @export
#'
#' @examples
#' x <- c(rep(1, 15), rep(2, 5))
#' y <- c(1, 2)
#'
#' rms_gof(x, y, reps = 10000)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit
#'
rms_gof <- function(x,
                    y,
                    reps = 10000)  {

  out <- rms_gof_cpp(x, y, reps)

  return(out)

}
