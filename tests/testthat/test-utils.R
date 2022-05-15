

test_that("RCONT_setup works", {

  x <- c(1:7)

  #First we produce the function in R. Each number we generate
  #here represents a column sum. So if the first column has a sum
  #of 8, then there will be 8 1's, if the second column has a sum
  #of 4, then there will be 4 2's, etc.

  RCONT_setup_r <- function(c_sum)  {

    dat <- NULL

    for(i in 1:length(c_sum)) {

      x <- (rep(i, c_sum[i]))

      dat <- append(dat, x)

    }

    return(dat)
  }

  a <- RCONT_setup_r(x)
  b <- RCONT_setup(x)

  expect_equal(a, b)

})

test_that("RCONT_setup_cpp works", {

  x <- c(1:7)

  #First we produce the function in R. Each number we generate
  #here represents a column sum. So if the first column has a sum
  #of 8, then there will be 8 1's, if the second column has a sum
  #of 4, then there will be 4 2's, etc.

  RCONT_setup_r <- function(c_sum)  {

    dat <- NULL

    for(i in 1:length(c_sum)) {

      x <- (rep(i, c_sum[i]))

      dat <- append(dat, x)

    }

    return(dat)
  }

  a <- RCONT_setup_r(x)
  b <- RCONT_setup_cpp(x)

  expect_equal(a, b)

})

test_that("RCONT tables equal rowSums/colSums", {

  mat <- matrix(data = 1:16, ncol = 4)

  r_sum <- rowSums(mat)
  c_sum <- rowSums(mat)

  v <-RCONT_setup(c_sum)
  a <- RCONT_simulate(v, r_sum, c_sum)
  b <- matrix(a, ncol = 4)
  r <- rowSums(b)
  c <- colSums(b)

  expect_equal(r_sum, r)
  expect_equal(c_sum, c)

})


test_that("RCONT_simulate_cpp tables equal rowSums/colSums", {

  mat <- matrix(data = 1:16, ncol = 4)

  r_sum <- rowSums(mat)
  c_sum <- rowSums(mat)

  v <-RCONT_setup_cpp(c_sum)
  a <- RCONT_simulate_cpp(v, r_sum, c_sum)
  b <- matrix(a, ncol = 4)
  r <- rowSums(b)
  c <- colSums(b)

  expect_equal(r_sum, r)
  expect_equal(c_sum, c)

})


test_that("RCONT_tab_cpp works", {

  x <- c(1, 1, 1, 2, 3, 4, 5)

  a <- RCONT_tab_cpp(x, 8, 0, length(x))

  b <- c(0, 3, 1, 1, 1, 1, 0, 0)

  expect_equal(a, b)

})


RCONT_cpp(10, c(10, 10), c(15, 5))

RCONT_cpp2(c(10, 10),
           c(15, 5))
