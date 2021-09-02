
#' chisq_gof
#'
#' @param vector_1 - Numeric vector
#' @param vector_2 - Numeric vector
#' @param reps - Number of simulations.
#'
#' @return
#' @export
#'
#' @examples
#' x <- c(rep(1, 15), rep(2, 5))
#' y <- c(1, 2)
#'
#' chisq_gof(x, y, reps = 10000)
#'
#' @importFrom Rcpp sourceCpp
#' @useDynLib discretefit


chisq_gof <- function(vector_1,
                      vector_2,
                      reps)  {

  out <- chisq_gof_cpp(vector_1 = vector_1,
                      vector_2 = vector_2,
                      reps = reps)

  return(out)

}
