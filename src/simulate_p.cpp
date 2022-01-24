#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

// [[Rcpp::export]]

List simulate_p(int type,
                  NumericVector vector_1,
                  NumericVector vec_2_frac,
                  double reps,
                  double tolerance)  {


  //Here we calculate draws and vec_1_frac.

  int draws = 0;

  for(int i = 0; i < vector_1.size(); i++)  {
    draws += vector_1(i);
  }

  NumericVector vec_1_frac = vector_1 / draws;

  //Define which statistic to use.

  auto stat_fun = [&](int type,
                        NumericVector vec_1_frac,
                        NumericVector vec_2_frac,
                        int draws)  {

    if(type == 1) {

      return rms_stat(draws,
                      vec_1_frac,
                      vec_2_frac);

    }

    else if(type == 2) {

    return chisq_stat(draws,
                      vec_1_frac,
                      vec_2_frac);
    }

    else if(type == 3) {

    return ks_stat(vec_1_frac,
                   vec_2_frac);

    }

    else if(type == 4) {

    return g2_stat(draws,
                   vec_1_frac,
                   vec_2_frac);

    }

    else if(type == 5) {

      return ft_stat(draws,
                     vec_1_frac,
                     vec_2_frac);

    }

    else {

      return cvm_stat(draws,
                     vec_1_frac,
                     vec_2_frac);

    }

  };

  double statistic = stat_fun(type,
                              vec_1_frac,
                              vec_2_frac,
                              draws);


  int n_bins = vec_2_frac.size();
  IntegerVector uni_2 = seq_len(n_bins);

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    if (i % 1000 == 0){
      Rcpp::checkUserInterrupt();
    }

    IntegerVector sam_0 = sample(n_bins, draws, true, vec_2_frac);
    NumericVector sam_0_frac = compute_vec_1_frac(sam_0,
                                                 n_bins,
                                                 draws);


    double sam_statistic = stat_fun(type,
                                    sam_0_frac,
                                    vec_2_frac,
                                    draws);

    if (sam_statistic >= (1 - tolerance) * statistic)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual + 1) / (reps + 1);

  List L = List::create(Named("statistic") = statistic,
                        Named("p_value") = p_value);

  return L;

}
