#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

// [[Rcpp::export]]

double simulate_p(int type,
                  NumericVector vector_1,
                  NumericVector vec_2_frac,
                  double reps)  {

  //Here we take the rms statistic.

  int draws = 0;

  for(int i = 0; i < vector_1.size(); i++)  {
    draws += vector_1(i);
  }

  NumericVector vec_1_frac = vector_1 / draws;

  double statistic = 0;

  if(type == 1) {

    statistic += rms_stat(vec_1_frac,
                          vec_2_frac);

  }

  if(type == 2) {

    statistic += chisq_stat(draws,
                            vec_1_frac,
                            vec_2_frac);
  }

  if(type == 3) {

    statistic += ks_stat(vec_1_frac,
                         vec_2_frac);

  }

  if(type == 4) {

    statistic += g2_stat(draws,
                         vec_1_frac,
                         vec_2_frac);

  }


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

    double sam_statistic = 0;

    if(type == 1)  {

      sam_statistic += rms_stat(sam_0_rms,
                                vec_2_frac);
    }

    if(type == 2)  {

      sam_statistic += chisq_stat(draws,
                                  sam_0_rms,
                                  vec_2_frac);
    }

    if(type == 3)  {

      sam_statistic += ks_stat(sam_0_rms,
                               vec_2_frac);
    }

    if(type == 4)  {

      sam_statistic += g2_stat(draws,
                               sam_0_rms,
                               vec_2_frac);
    }

    if (sam_statistic >= 0.999999999999986 * statistic)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual + 1) / (reps + 1);

  return p_value;

}
