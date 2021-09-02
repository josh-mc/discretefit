
<!-- README.md is generated from README.Rmd. Please edit that file -->

# discretefit

### Simulated goodness-of-fit tests for discrete distributions

<!-- badges: start -->
<!-- badges: end -->

The discretefit package provides fast Monte Carlo simulations for
conducting goodness-of-fit tests for discrete distributions. Simulations
are written in C++. The package is under development but currently
includes goodness-of-fit tests based on the root-mean-square statistic,
the Chi-squared statistic, the Kolmogovor-Smirnov statistic.

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

chisq.test(x, p = p, simulate.p.value = TRUE)
#> 
#>  Chi-squared test for given probabilities with simulated p-value (based
#>  on 2000 replicates)
#> 
#> data:  x
#> X-squared = 30, df = NA, p-value = 0.3698
```

The root-mean-squared statistic convincingly rejects the hypothesis that
x is drawn from the distribution defined in p.

``` r
rms_gof(x, p)
#> [1] 9.999e-05
```
