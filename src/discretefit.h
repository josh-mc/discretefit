//Header for discretefit

#ifndef COMPUTE_VEC_1_FRAC_H
#define COMPUTE_VEC_1_FRAC_H

#include <Rcpp.h>
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector vector_1,
                                 IntegerVector uni_2,
                                 int n_bins);

#endif


#ifndef RMS_STAT_H
#define RMS_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double rms_stat(NumericVector vec_1_frac,
         NumericVector vec_2_frac);

#endif

#ifndef KS_STAT_H
#define KS_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double ks_stat(NumericVector vec_1_frac,
               NumericVector vec_2_frac);

#endif

#ifndef CHISQ_STAT_H
#define CHISQ_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double chisq_stat(NumericVector vector_1,
           NumericVector vec_1_frac,
           NumericVector vec_2_frac);

#endif




