//Header for discretefit

#ifndef COMPUTE_VEC_1_FRAC_H
#define COMPUTE_VEC_1_FRAC_H

#include <Rcpp.h>
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector x,
                                 int n_bins,
                                 int draws);

#endif


#ifndef RCONT3_CPP
#define RCONT3_CPP


#include <Rcpp.h>
#include <random>
#include <algorithm>
#include "pcg_random.h"
using namespace Rcpp;

List rcont3_cpp (int n,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 int seed);

#endif


#ifndef RMS_STAT_H
#define RMS_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double rms_stat(int draws,
                NumericVector vec_1_frac,
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

double chisq_stat(int draws,
           NumericVector vec_1_frac,
           NumericVector vec_2_frac);

#endif


#ifndef G2_STAT_H
#define G2_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double g2_stat(int draws,
                  NumericVector vec_1_frac,
                  NumericVector vec_2_frac);

#endif


#ifndef FT_STAT_H
#define FT_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double ft_stat(int draws,
               NumericVector vec_1_frac,
               NumericVector vec_2_frac);

#endif

#ifndef CVM_STAT_H
#define CVM_STAT_H

#include <Rcpp.h>
using namespace Rcpp;

double cvm_stat(int draws,
               NumericVector vec_1_frac,
               NumericVector vec_2_frac);

#endif

