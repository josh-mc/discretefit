#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

double rms_stat1(NumericVector vec_1_frac,
               NumericVector vec_2_frac)  {

  NumericVector x = pow((vec_1_frac - vec_2_frac), 2);

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double rms = sqrt(y / vec_2_frac.size());

  return rms;
}

// [[Rcpp::export]]

double rms_gof_cpp(NumericVector vector_1,
                   NumericVector vec_2_frac,
                   double reps)  {

  //Here we take the rms statistic.

  int draws = 0;

  for(int i = 0; i < vector_1.size(); i++)  {
    draws += vector_1(i);
  }

  NumericVector vec_1_frac = vector_1 / draws;

  double rms_statistic = rms_stat1(vec_1_frac,
                                  vec_2_frac);

  int n_bins = vec_2_frac.size();
  IntegerVector uni_2 = seq_len(n_bins);

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    if (i % 1000 == 0){
      Rcpp::checkUserInterrupt();
    }

    IntegerVector sam_0 = sample(n_bins, draws, true, vec_2_frac);
    NumericVector sam_0_rms = compute_vec_1_frac(sam_0,
                                                 uni_2,
                                                 n_bins);

    double sam_statistic = rms_stat1(sam_0_rms,
                                    vec_2_frac);

    if (sam_statistic >= 0.999999999999986 * rms_statistic)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual + 1) / (reps + 1);

  return p_value;

}
