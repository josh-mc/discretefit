
test_that("chisq_ind produce correct answer", {

  x <- matrix(data = 1:16, ncol = 4)

  set.seed(02332)

  a <- chisq_ind2(x, reps = 10000)

  #b <- chisq.test(x, simulate.p.value = TRUE)

  expect_equal(0.9989001, a)

})

test_that("chisq_ind produce correct answer", {

  x <- matrix(data = c(12, 38, 29, 11, 9, 27), ncol = 2)

  set.seed(02332)

  a <- chisq_ind2(x, reps = 10000)

  #b <- chisq.test(x, simulate.p.value = TRUE, B = 10000)

  expect_equal(0.00579942, a)

})


test_that("chisq_ind approximate published results", {

  x <- c(48, 17066,
         38, 14464,
         5,  788,
         1, 126,
         1, 37)


  x <- matrix(x, ncol = 2, byrow = TRUE)

  set.seed(02332)

  a <- chisq_ind2(x, reps = 10000)

  b <- chisq.test(x, simulate.p.value = TRUE, B = 10000)

  expect_equal(0.03369663, a)

})
