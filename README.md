
<!-- README.md is generated from README.Rmd. Please edit that file -->

# discretefit

<!-- badges: start -->
<!-- badges: end -->

The package `discretefit` implements fast, Monte Carlo simulations for
goodness-of-fit (GOF) tests for discrete distributions. This includes
tests based on the root-mean-square statistic, the Chi-squared
statistic, the log-likelihood-ratio statistic (G^2), and the
Kolmogovov-Smirnov statistic.

Simulations are written in C++ (utilizing `Rcpp`) and are much faster
than the simulated Chi-squared GOF test in the R `stats` package and the
simulated Kolmogorov-Smirnov GOF test in the `dgof` package.

## Installation

You can install the development version from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("josh-mc/discretefit")
```

## Usage

The GOF tests in `discretefit` function on a vector of counts, x, and a
vector of probabilities, p. In the below example, x represents a vector
of counts for five categories, and p represents a vector of
probabilities for each corresponding category. The GOF tests provides
p-values for the null hypothesis that x is a random sample of the
discrete distribution defined by p. 

``` r
library(discretefit)
library(bench)

x <- c(42, 0, 13, 2, 109)
p <- c(0.2, 0.05, 0.1, 0.05, 0.6)

pp <- c(rep(1, 4),
        rep(2, 1),
        rep(3, 2),
        rep(4, 1),
        rep(5, 12))

chisq_gof(x, p)
#> [1] 0.00229977
rms_gof(x, p)
#> [1] 0.03719628
ks_gof(x, p)
#> [1] 0.2435756
g_gof(x, p)
#> [1] 9.999e-05
```

## Speed

The simulated Chi-squared GOF test in `discretefit` produces identical
answers to the simulated Chi-squared GOF test in the stats package that
is part of base R.

``` r
set.seed(499)
chisq_gof(x, p, reps = 2000)
#> [1] 0.002998501
set.seed(499)
chisq.test(x, p = p, simulate.p.value = TRUE)$p.value
#> [1] 0.002998501
```

However, because the Monte Carlo simulations in `discretefit` are
written in C++, chisq\_gof is much faster than `chisq.test`, especially
when a large number of simulations are required.

``` r
bench::system_time(
  chisq_gof(x, p, reps = 20000)
)
#> process    real 
#>   250ms   255ms

bench::system_time(
  chisq.test(x, p = p, simulate.p.value = TRUE, B = 20000)
)
#> process    real 
#>   2.19s   2.25s
```

The `ks_gof` function in `discretefit` is also faster than the simulated
Kolmogorov-Smirnov test in the `dgof` package. (The `ks.test` function
in the `stats` package in base R does not include a simulated test for
discrete distributions.)

The p-values produced by `ks_gof`, however, are not exactly identical to
those produced by ks.test in the `dgof` package because of slight
variations in the algorithms.

``` r
x <- c(114, 118, 112, 158)
y <- c(1, 2, 3, 4, 5, 5)
p <- c(0.2, 0.2, 0.2, 0.4)
  
bench::system_time(
  ks_gof(x, p, reps = 20000)
)
#> process    real 
#>   547ms   546ms

bench::system_time(
  dgof::ks.test(x, ecdf(y), simulate.p.value = TRUE, B = 20000)
)
#> process    real 
#>   3.89s   3.93s
```

Additionally, the simulated GOF tests in base R and the `dgof` package
are vectorized, so for large vectors attempting a large number of
simulations maybe not be possible because of memory constraints. Since
the function in `discretefit` are not vectorized, memory use is
minimized.

## Root-mean-square statistic

In a surprising number of cases, a simulated GOF test based on the
root-mean-square statistic outperforms the Chi-squared test and other
tests in the Cressie-Read power divergence family. This has been
demonstrated by Perkins, Tygert, and Ward (2011). They provide the
following toy example.

Take a discrete distribution with 30 bins (or categories). The
probability for the first and second bin is 0.25. The probability for
each of the remaining 28 bins is 0.5 / 28 (\~0.0179).

Now take the observed counts of 15 for the first bin, 5 for the second
bin, and zero for each of the remaining 28 bins. It’s obvious that these
observations are very unlikely to be a random sample from the above
distribution. However, the Chi-squared test and G^2 test fail to reject
the null hypothesis.

``` r
x <- c(15, 5, rep(0, 28))
p <- c(0.25, 0.25, rep(1/(2 * 30 -4), 28))

chisq_gof(x, p)
#> [1] 0.3960604
g_gof(x, p)
#> [1] 9.999e-05
```

By contrast, the root-mean-square test convincingly rejects the null
hypothesis.

``` r
rms_gof(x, p)
#> [1] 9.999e-05
```

For additional examples, also see Perkins, Tygert, and Ward (2011) and
Ward and Carroll (2014).

## Alternatives

As noted above, the `stats` package in base R implements a simulated
Chi-squared GOF test, and the `dgof` package implements simulated
Kolmogorov-Smirnov GOF test.

I’m not aware of an R package that implements a simulated G^2 GOF test
but the packages `RVAideMemoire` and `DescTools` implement GOF tests
that utilize approximations based on the Chi-squared distribution.

I’m not aware of another R package that implements a root-mean-square
GOF test.

## References

Perkins, William, Mark Tygert, and Rachel Ward. “Computing the
confidence levels for a root-mean-square test of goodness-of-fit.”
Applied Mathematics and Computation, 2011.
<https://doi.org/10.1016/j.amc.2011.03.124>

Ward, Rachel and Raymond J. Carroll. “Testing Hardy–Weinberg equilibrium
with a simple root-mean-square statistic.” Biostatistics, 2014.
<https://doi.org/10.1093/biostatistics/kxt028>
