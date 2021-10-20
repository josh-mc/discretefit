
test_that("chisq_gof equal to chisq.test", {

  x <- c(14, 18, 12, 58)
  p <- c(0.2, 0.2, 0.2, 0.4)

  set.seed(40)
  a <- chisq_gof(x, p)$p.value

  set.seed(40)
  b <- chisq.test(x, p = p, simulate.p.value = TRUE, B = 10000)$p.value

  expect_equal(a, b)

})

test_that("chisq_gof equal to chisq.test", {

  x <- c(134, 128)
  p <- c(0.6, 0.4)

  set.seed(40)
  a <- chisq_gof(x, p)$p.value

  set.seed(40)
  b <- chisq.test(x, p = p, simulate.p.value = TRUE, B = 10000)$p.value

  expect_equal(a, b)

})


test_that("chisq_gof equal to rms_gof for uniform distribution", {

  x <- c(14, 18, 12, 13, 15)
  p <- c(0.2, 0.2, 0.2, 0.2, 0.2)

  set.seed(40)
  a <- chisq_gof(x, p)$p.value

  set.seed(40)
  b <- rms_gof(x, p)$p.value

  expect_equal(a, b)

})

skip_on_cran()

test_that("rms_gof is equal to stored result", {

  x <- c(2114, 2128, 2112)
  p <- c(rep(1/3, 3))


  set.seed(40)
  a <- rms_gof(x, p)$p.value

  b <- 0.966903309669033

  expect_equal(a, b)

})


test_that("ks_gof ~equal to ks.test (from dgof package)", {

  x <- c(14, 18, 15, 28)
  xx <- c(rep(1, 14), rep(2, 18), rep(3, 15), rep(4, 28))
  y <- c(1, 2, 3, 4, 4)
  p <- c(0.2, 0.2, 0.2, 0.4)

  set.seed(284)
  a <- ks_gof(x, p, reps = 2000)$p.value

  set.seed(284)
  b <- dgof::ks.test(xx, ecdf(y), simulate.p.value = TRUE, B = 2000)$p.value

  expect_equal(tolerance = 0.01, a, b)

})

test_that("g_gof is asymtoptically equal to chisq_gof", {

  x <- c(2114, 2128, 2112)
  p <- c(rep(1/3, 3))

  set.seed(300)
  a <- chisq_gof(x, p)$p.value

  set.seed(300)
  b <- g_gof(x, p)$p.value

  expect_equal(a, b)

})

test_that("g_gof is ~equal to G.test (from RVAideMemoire package)", {

  x <- c(214, 228, 212)
  p <- c(rep(1/3, 3))

  set.seed(30)
  a <- g_gof(x, p)$p.value

  b <- 0.707378226223282
  #b <- as.numeric(RVAideMemoire::G.test(x, p)$p.value)

  expect_equal(tolerance = 0.001, a, b)

})

test_that("ft_gof is asymtoptically equal to chisq_gof", {

  x <- c(2114, 2128, 2112)
  p <- c(rep(1/3, 3))

  set.seed(300)
  a <- chisq_gof(x, p)$p.value

  set.seed(300)
  b <- ft_gof(x, p)$p.value

  expect_equal(a, b)

})

test_that("cvm_gof ~equal to groupFit (from cvmdisc package)", {

  x <- c(14, 18, 15, 28)
  p <- c(0.2, 0.2, 0.2, 0.4)
  breaks <- c(0, cumsum(p))

  set.seed(4180)
  a <- cvm_gof(x, p, reps = 10000)$p.value

  set.seed(4180)
  b <- cvmdisc::groupFit(breaks, x, distr = "unif", bootstrap = TRUE, numLoops = 10000)$pvals[2, 1]

  expect_equal(tolerance = 0.01, a, b)

})

test_that("cvm_gof ~equal to cvm.test (from dgof package)", {

  x <- c(1, 4, 11, 4, 0)
  p <- c(0.05, 0.3, 0.3, 0.3, 0.05)


  set.seed(10)
  a <- cvm_gof(x, p, reps = 10000)$p.value

  #xx <- c(rep(1, 1), rep(2, 4), rep(3, 11), rep(4, 4), rep(5, 0))
  #pp <- c(rep(1, 1), rep(2, 6), rep(3, 6), rep(4, 6), rep(5, 1))
  #b <- dgof::cvm.test(xx, ecdf(pp))$p.value

  b <- 0.243733

  expect_equal(tolerance = 0.015, a, b)

})



