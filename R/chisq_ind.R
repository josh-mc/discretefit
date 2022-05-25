




chisq_ind <- function(x, reps = 10000)  {

  n <- sum(x)
  nr <- as.integer(nrow(x))
  nc <- as.integer(ncol(x))
  sr <- rowSums(x)
  sc <- colSums(x)
  E <- outer(sr, sc, "*") / n

  STATISTIC <- sum((x - E)^2 / E)

  ind_sim(reps = reps,
          r_sums = sc,
          c_sums = sr,
          as.numeric(E),
          seed = sample.int(.Machine$integer.max, 1),
          statistic = STATISTIC,
          tolerance = 0)
}

