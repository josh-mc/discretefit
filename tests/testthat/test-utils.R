



test_that("RCONT_setup = example_1", {

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

  b <- RCONT_setup(x) + 1 #b/c this indexes starting at 0 instead of 1

  expect_equal(a, b)

})
