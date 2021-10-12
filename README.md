
<!-- README.md is generated from README.Rmd. Please edit that file -->

# discretefit

<!-- badges: start -->

[![CRAN\_Status\_Badge](https://www.r-pkg.org/badges/version/discretefit)](https://cran.r-project.org/package=discretefit)
[![CRAN\_latest\_release\_date](https://www.r-pkg.org/badges/last-release/discretefit)](https://cran.r-project.org/package=discretefit)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://choosealicense.com/licenses/mit/)

<!-- badges: end -->

The package `discretefit` implements fast, Monte Carlo simulations for
goodness-of-fit (GOF) tests for discrete distributions. This includes
tests based on the root-mean-square statistic, the Chi-squared
statistic, the log-likelihood-ratio (*G*<sup>2</sup>) statistic, and the
Kolmogovov-Smirnov statistic.

Simulations are written in C++ (utilizing `Rcpp`) and are much faster
than the simulated Chi-squared GOF test in the R `stats` package and the
simulated Kolmogorov-Smirnov GOF test in the `dgof` package.

## Installation

You can install `discretefit` from CRAN.

``` r
install.packages("discretefit")
```

You can also install the development version from GitHub:

``` r
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
#> [1] 0.00289971
rms_gof(x, p)
#> [1] 0.03979602
g_gof(x, p)
#> [1] 9.999e-05
ks_gof(x, p)
#> [1] 0.2365763
```

## Speed

The simulated Chi-squared GOF test in `discretefit` produces identical
answers to the simulated Chi-squared GOF test in the `stats` package
that is part of base R.

``` r
set.seed(499)
chisq_gof(x, p, reps = 2000)
#> [1] 0.002998501
set.seed(499)
chisq.test(x, p = p, simulate.p.value = TRUE)$p.value
#> [1] 0.002998501
```

However, because Monte Carlo simulations in `discretefit` are
implemented in C++, `chisq_gof` is much faster than `chisq.test`,
especially when a large number of simulations are required.

``` r
bench::system_time(
  chisq_gof(x, p, reps = 20000)
)
#> process    real 
#>   359ms   489ms

bench::system_time(
  chisq.test(x, p = p, simulate.p.value = TRUE, B = 20000)
)
#> process    real 
#>   2.58s   3.65s
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
#>   703ms   991ms

bench::system_time(
  dgof::ks.test(x, ecdf(y), simulate.p.value = TRUE, B = 20000)
)
#> process    real 
#>   5.84s   7.18s
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

Take a discrete distribution with 50 bins (or categories). The
probability for the first and second bin is 0.25. The probability for
each of the remaining 48 bins is 0.5 / 48 (\~0.0104).

Now take the observed counts of 15 for the first bin, 5 for the second
bin, and zero for each of the remaining 48 bins. It’s obvious that these
observations are very unlikely to occur for random sample from the above
distribution. However, the Chi-squared test and *G*<sup>2</sup> test
fail to reject the null hypothesis.

``` r
x <- c(15, 5, rep(0, 48))
p <- c(0.25, 0.25, rep(1/(2 * 50 -4), 48))

chisq_gof(x, p)
#> [1] 0.9716028
g_gof(x, p)
#> [1] 0.6643336
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

I’m not aware of an R package that implements a simulated
*G*<sup>2</sup> GOF test but the packages `RVAideMemoire` and
`DescTools` implement GOF tests that utilize approximations based on the
Chi-squared distribution.

I’m not aware of another R package that implements a root-mean-square
GOF test.

## References

Dwass, Meyer. “Modified randomization tests for nonparametric
hypotheses.” Annuls of Mathematical Statistics, 1957.
<https://doi.org/10.1214/aoms/1177707045>

Eddelbuettel, Dirk and Romain Francois. “Rcpp: Seamless R and C++
Integration.” Journal of Statistical Software, 2011.
<https://www.jstatsoft.org/article/view/v040i08>

Perkins, William, Mark Tygert, and Rachel Ward. “Computing the
confidence levels for a root-mean-square test of goodness-of-fit.”
Applied Mathematics and Computation, 2011.
<https://doi.org/10.1016/j.amc.2011.03.124>

Phipson, Belinda, and Gordon K. Smyth. “Permutation p-values should
never be zero: calculating exact p-values when permutations are randomly
drawn.” Statistical Applications in Genetics and Molecular Biology,
2010. <https://dx.doi.org/10.2202/1544-6115.1585>

Ward, Rachel and Raymond J. Carroll. “Testing Hardy–Weinberg equilibrium
with a simple root-mean-square statistic.” Biostatistics, 2014.
<https://doi.org/10.1093/biostatistics/kxt028>
