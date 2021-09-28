//Header for utils

#ifndef COMPUTE_VEC_1_FRAC_H
#define COMPUTE_VEC_1_FRAC_H

#include <Rcpp.h>
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector vector_1,
                                 IntegerVector uni_2,
                                 int n_bins);

#endif
