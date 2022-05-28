chisq_ind2 <- function(x, reps = 10000, tolerance = 0)  {

  n <- sum(x)
  nr <- as.integer(nrow(x))
  nc <- as.integer(ncol(x))
  sr <- rowSums(x)
  sc <- colSums(x)
  E <- outer(sr, sc, "*") / n

  STATISTIC <- sum((x - E)^2 / E)

  ind_sim2(reps = reps,
           r_sums = sr,
           c_sums = sc,
           as.numeric(E),
           seed = sample.int(.Machine$integer.max, 1),
           statistic = STATISTIC,
           tolerance = tolerance)
}

