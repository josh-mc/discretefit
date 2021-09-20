
errors_x_p <- function(x, p)  {

  if(length(x) != length(p)) {
    stop("The vectors x and p must be the same length.")
  }

  if(sum(x < 0) >= 1) {
    stop("The vector x cannot contain negative counts.")
  }

  if(sum(x%%1 == 0) < length(x)) {
    stop("The vector x cannot contain fractions. Counts must be expressed as whole numbers.")
  }

  if(sum(p < 0) >= 1) {
    stop("The vector p cannot contain negative probabilities.")
  }

  if(sum(p) != 1) {
    stop("The probilities in vector p must sum to one.")
  }
}
