

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

