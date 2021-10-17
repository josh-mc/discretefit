
test_that("chisq_gof equal to chisq.test", {

  x <- c(14, 18, 12, 58)
  p <- c(0.2, 0.2, 0.2, 0.4)

  set.seed(40)
  a <- chisq_gof(x, p)$p_value

  set.seed(40)
  b <- chisq.test(x, p = p, simulate.p.value = TRUE, B = 10000)$p.value

  expect_equal(a, b)

})

test_that("chisq_gof equal to chisq.test", {

  x <- c(134, 128)
  p <- c(0.6, 0.4)

  set.seed(40)
  a <- chisq_gof(x, p)$p_value

  set.seed(40)
  b <- chisq.test(x, p = p, simulate.p.value = TRUE, B = 10000)$p.value

  expect_equal(a, b)

})


test_that("chisq_gof equal to rms_gof for uniform distribution", {

  x <- c(14, 18, 12, 13, 15)
  p <- c(0.2, 0.2, 0.2, 0.2, 0.2)

  set.seed(40)
  a <- chisq_gof(x, p)$p_value

  set.seed(40)
  b <- rms_gof(x, p)$p_value

  expect_equal(a, b)

})


test_that("ks_gof ~equal to ks.test (from dgof package)", {

  x <- c(14, 18, 12, 58)
  y <- c(1, 2, 3, 4, 5, 5)
  p <- c(0.2, 0.2, 0.2, 0.4)

  set.seed(284)
  a <- ks_gof(x, p, reps = 2000)$p_value

  set.seed(284)
  b <- dgof::ks.test(x, ecdf(y), simulate.p.value = TRUE, B = 2000)$p.value

  expect_equal(tolerance = 0.001, a, b)

})


test_that("g_gof is asymtoptically equal to chisq_gof", {

  x <- c(2114, 2128, 2112)
  p <- c(rep(1/3, 3))

  set.seed(300)
  a <- chisq_gof(x, p)$p_value

  set.seed(300)
  b <- g_gof(x, p)$p_value

  expect_equal(a, b)

})

test_that("g_gof is ~equal to G.test (from RVAideMemoire package)", {

  x <- c(214, 228, 212)
  p <- c(rep(1/3, 3))

  set.seed(30)
  a <- g_gof(x, p)$p_value

  b <- as.numeric(RVAideMemoire::G.test(x, p)$p.value)

  expect_equal(tolerance = 0.001, a, b)

})

test_that("ft_gof is asymtoptically equal to chisq_gof", {

  x <- c(2114, 2128, 2112)
  p <- c(rep(1/3, 3))

  set.seed(300)
  a <- chisq_gof(x, p)$p_value

  set.seed(300)
  b <- ft_gof(x, p)$p_value

  expect_equal(a, b)

})


