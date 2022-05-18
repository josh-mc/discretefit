

test_that("rcont3_cpp tables equal rowSums/colSums", {

  mat <- matrix(data = 1:16, ncol = 4)

  r_sum <- rowSums(mat)
  c_sum <- rowSums(mat)

  a <- unlist(rcont3_cpp(1, c_sum, r_sum, seed = 1002))
  b <- matrix(a, ncol = 4)
  r <- rowSums(b)
  c <- colSums(b)

  expect_equal(r_sum, r)
  expect_equal(c_sum, c)

})

test_that("rcont_cpp tables equal rowSums/colSums - unequal tables", {

  r_sum <- c(rep(10, 3))
  c_sum <- c(rep(15, 2))

  a <- unlist(rcont3_cpp(1, c_sum, r_sum, seed = 1002))
  b <- matrix(a, ncol = 2)
  r <- rowSums(b)
  c <- colSums(b)

  expect_equal(r, r_sum)
  expect_equal(c, c_sum)

})


test_that("rcont_cpp generates correct probabilities for lady tasting tea", {

  n <- 100000
  r_sums <- c(rep(4, 2))
  c_sums <- c(rep(4, 2))

  x <- rcont3_cpp(n, r_sums, c_sums, seed = sample.int(.Machine$integer.max, 1))

  #Takes the count for the first cell which is all you need for
  #calculating successes for a 2 x 2 table.

  y <- unlist(Map(`[`, x, 1))

  counts <- table(y)
  per <- as.numeric(counts / sum(counts))

  #This is a vector of the probabilities for the
  #lady tasting tea example. See https://en.wikipedia.org/wiki/Lady_tasting_tea
  p <- c(1/70, 16/70, 36/70, 16/70, 1/70)

  p_val <- chisq.test(counts, p = p)$p.value

  expect_equal(per, p, tolerance = 0.005)
  expect_gt(p_val, 0.05)

})

test_that("rcont_cpp ~ r2dtables (3 x 2)", {

  n <- 1000
  r_sum <- c(rep(10, 3))
  c_sum <- c(rep(15, 2))

  a <- rcont_cpp(n, c_sum, r_sum)

  a_vec <- integer(n)

  for(i in 1:n)  {

    a_vec[i] <- as.integer(paste0(a[[i]], collapse = ""))

  }

  a_counts <- table(a_vec)



  b <- r2dtable(n, r_sum, c_sum)

  b_vec <- integer(n)

  for(i in 1:n)  {

    b_vec[i] <- as.integer(paste0(b[[i]], collapse = ""))

  }

  b_counts <- table(b_vec)

  #Adding zeros.

  uniq_a <- as.character(sort(unique(a_vec)))
  uniq_b <- as.character(sort(unique(b_vec)))
  uniq <- as.character(sort(unique(c(a_vec, b_vec))))

  a_final <- numeric(length(uniq))

  count <- 1
  cts <- 1

  for(i in uniq) {

    if(i %in% uniq_a) {

      a_final[count] <- a_counts[cts]

      cts<- cts + 1

    }

  else a_final[count] <- 0

  count <- count + 1

}


  b_final <- numeric(length(uniq))

  count <- 1
  cts <- 1

  for(i in uniq) {


    if(i %in% uniq_b) {

      b_final[count] <- b_counts[cts]

      cts<- cts + 1

    }

    else b_final[count] <- 0

    count <- count + 1

  }

  mat <- matrix(c(a_final, b_final), ncol = 2)

  p_val <- chisq.test(mat, simulate.p.value = TRUE, B = 10000)$p.value

  print(p_val)

  expect_gt(p_val, 0.05)

})


  test_that("rcont_cpp ~ r2dtables (4 x 4)", {

    n <- 10000
    r_sum <- c(1:4)
    c_sum <- c(4:1)

    a <- rcont3_cpp(n, c_sum, r_sum, seed = sample.int(.Machine$integer.max, 1))

    a_vec <- character(n)

    for(i in 1:n)  {

      a_vec[i] <- paste0(a[[i]], collapse = "")

    }

    a_counts <- table(a_vec)



    b <- r2dtable(n, r_sum, c_sum)

    b_vec <- character(n)

    for(i in 1:n)  {

      b_vec[i] <- paste0(b[[i]], collapse = "")

    }

    b_counts <- table(b_vec)

    #Adding zeros.

    uniq_a <- sort(unique(a_vec))
    uniq_b <- sort(unique(b_vec))
    uniq <- sort(unique(c(uniq_a, uniq_b)))

    a_final <- numeric(length(uniq))

    count <- 1
    cts <- 1

    for(i in uniq) {

      if(i %in% uniq_a) {

        a_final[count] <- a_counts[cts]

        cts<- cts + 1

      }

      else a_final[count] <- 0

      count <- count + 1

    }


    b_final <- numeric(length(uniq))

    count <- 1
    cts <- 1

    for(i in uniq) {


      if(i %in% uniq_b) {

        b_final[count] <- b_counts[cts]

        cts<- cts + 1

      }

      else b_final[count] <- 0

      count <- count + 1

    }

    mat <- matrix(c(a_final, b_final), ncol = 2)

    p_val <- chisq.test(mat, simulate.p.value = TRUE, B = 10000)$p.value

    print(mat)
    print(p_val)

    expect_gt(p_val, 0.05)

  })


