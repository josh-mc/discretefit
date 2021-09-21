
<!-- README.md is generated from README.Rmd. Please edit that file -->

# discretefit

<!-- badges: start -->
<!-- badges: end -->

discretefit provides fast, Monte Carlo simulations for conducting
goodness-of-fit tests for discrete distributions. Simulations are
written in C++.

The package is under development but currently includes goodness-of-fit
tests based on the root-mean-square statistic, the Chi-squared
statistic, the Kolmogovor-Smirnov statistic.

## Installation

You can install the development version from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("josh-mc/discretefit")
```

## Example

The Chi-squared test for goodness-of-fit demonstrates low statistical
power in a surprisingly large number of cases. Perkins, Tygert, and Ward
provide the following toy example.

``` r
library(discretefit)

x <- c(15, 5, rep(0, 28))
p <- c(0.25, 0.25, rep(1/(2 * 30 -4), 28))

set.seed(99)
chisq_gof(x, p)
#> [1] 0.3858614
```

The root-mean-squared statistic convincingly rejects the hypothesis that
x is drawn from the distribution defined in p.

``` r
set.seed(99)
rms_gof(x, p)
#> [1] 9.999e-05
```
