#Defining observed and theoretical distribution
x <- c(42, 5, 13, 2, 109)
p <- c(0.2, 0.05, 0.1, 0.05, 0.6)

#for cvmdisc package
breaks <- c(0, cumsum(p))

#translation for dgof
xx <- c(rep(1, 42), rep(2, 5), rep(3, 13), rep(4, 2), rep(5, 109))
pp <- c(rep(1, 20), rep(2, 5), rep(3, 10), rep(4, 5), rep(5, 60))

test_that("chi_gof statatistic is equal to chisq.test statistic", {

  a <- as.numeric(chisq_gof(x, p, reps = 100)$statistic)

  b <- as.numeric(chisq.test(x, p = p)$statistic)

  expect_equal(a, b)

})

test_that("g_gof statistic is equal to G.test statistic (RVAideMemoire)", {

  a <- as.numeric(g_gof(x, p, reps = 100)$statistic)

  b <- 12.1450359514788
  #b <- as.numeric(RVAideMemoire::G.test(x, p)$statistic)

  expect_equal(a, b)

})


test_that("rms_gof statistic is correct", {

  a <- as.numeric(rms_gof(x, p, reps = 100)$statistic)

  #b <- sqrt(sum((x/sum(x) - p)^2) * 1/length(x))

  b <- sum((sqrt(sum(x)) * (x/sum(x) - p))^2)

  expect_equal(a, b)

})

test_that("ft_gof statistic is correct", {

  a <- as.numeric(ft_gof(x, p, reps = 100)$statistic)

  b <- 4 * sum(x) * sum((sqrt((x/sum(x))) - sqrt(p))^2)

  expect_equal(a, b)

})

test_that("ks_gof statistic is equal to ks.test statistis (dgof)", {

  a <- as.numeric(ks_gof(x, p, reps = 100)$statistic)

  b <- as.numeric(dgof::ks.test(xx, ecdf(pp))$statistic)

  expect_equal(a, b)

})

test_that("cvm_gof statistic is equal to groupFit statistis (cvmdisc)", {

  a <- as.numeric(cvm_gof(x, p, reps = 100)$statistic)

  b <- cvmdisc::groupFit(breaks, x, distr = "unif")$stats[2, 1]

  expect_equal(a, b)

})
