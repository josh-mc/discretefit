#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector vector_1,
                                 IntegerVector uni_2,
                                 int n_bins)  {

  IntegerVector uni_1 = sort_unique(vector_1);
  IntegerVector mat_0 = match(uni_2, uni_1);
  IntegerVector mat_1 = ifelse(is_na(mat_0), 0, mat_0);

  IntegerVector tab_1 = table(vector_1);
  NumericVector vector_1_bins(n_bins);

  for(int i = 0; i < n_bins; ++i)  {

    if(mat_1(i) > 0) {

      vector_1_bins(i) = tab_1(mat_1(i) - 1);

    }

    else {

      vector_1_bins(i) = 0;

    }

  }

  NumericVector vec_1_frac = vector_1_bins / vector_1.size();

  return vec_1_frac;

}

