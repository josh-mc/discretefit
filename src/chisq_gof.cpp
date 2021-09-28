#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

double chisq_mod(IntegerVector vector_1,
                   IntegerVector uni_2,
                   int n_bins,
                   NumericVector vec_2_frac)  {

  NumericVector vec_1_frac = compute_vec_1_frac(vector_1,
                                                uni_2,
                                                n_bins);

  NumericVector x = pow((vec_1_frac - vec_2_frac), 2) / vec_2_frac;

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double chi = y * vector_1.size();

  return chi;

}


// [[Rcpp::export]]

double chisq_gof_cpp(NumericVector vector_1,
                   NumericVector vec_2_frac,
                   double reps)  {

  //Here we take the chisq statistic.

  int draws = 0;

  for(int i = 0; i < vector_1.size(); i++)  {
    draws += vector_1(i);
  }

  NumericVector vec_1_frac = vector_1 / draws;
  NumericVector x = pow((vec_1_frac - vec_2_frac), 2) / vec_2_frac;

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double chisq_stat = y * draws;

  int n_bins = vec_2_frac.size();
  IntegerVector uni_2 = seq_len(n_bins);

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    IntegerVector sam_0 = sample(n_bins, draws, true, vec_2_frac);

    double sam_0_chi = chisq_mod(sam_0,
                                   uni_2,
                                   n_bins,
                                   vec_2_frac);

    if (sam_0_chi >= 0.999999999999986 * chisq_stat)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual + 1) / (reps + 1);

  return p_value;

}
