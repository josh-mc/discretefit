#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector x,
                              int n_bins,
                              int draws) {

    NumericVector counts(n_bins);

    for (auto& i : x) {

      if (i > 0 && i <= n_bins)

        counts[i - 1]++;
    }

    return counts / draws;
  }





