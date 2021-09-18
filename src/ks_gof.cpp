#include <Rcpp.h>
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector vector_1,
                                 IntegerVector uni_2,
                                 int n_bins,
                                 NumericVector vec_2_frac)  {

  IntegerVector uni_1 = sort_unique(vector_1);
  IntegerVector mat_0 = match(uni_2, uni_1);
  IntegerVector mat_1 = ifelse(is_na(mat_0), 0, mat_0);

  IntegerVector tab_1 = table(vector_1);
  NumericVector vector_1_bins(n_bins);

  for(int i = 0; i < n_bins; ++i)  {

    if(mat_1(i) > 0) {

      int a = mat_1(i) - 1;
      vector_1_bins(i) = tab_1(a);

    }

    else {

      vector_1_bins(i) = 0;

    }

  }

  NumericVector vec_1_frac = vector_1_bins / vector_1.size();

  return vec_1_frac;

}


double ks_mod_p(IntegerVector vector_1,
                IntegerVector uni_2,
                int n_bins,
                NumericVector vec_2_frac)  {

  NumericVector vec_1_frac = compute_vec_1_frac(vector_1,
                                                uni_2,
                                                n_bins,
                                                vec_2_frac);

  NumericVector vec_1_cumsum = cumsum(vec_1_frac);
  NumericVector vec_2_cumsum = cumsum(vec_2_frac);
  NumericVector diff = vec_1_cumsum - vec_2_cumsum;

  NumericVector absolute(diff.size());

  for(int i = 0; i < diff.size(); ++i)  {

    absolute(i) = std::abs(diff(i));

  }

  double maximum = max(absolute);

  return maximum;

}


// [[Rcpp::export]]

double ks_gof_cpp(NumericVector vector_1,
                NumericVector vec_2_frac,
                double reps)  {

  //This first part is just to convert vector_1 into fractions.

  int draws = 0;

  for(int i = 0; i < vector_1.size(); i++)  {
    draws += vector_1(i);
  }

  NumericVector vec_1_frac = vector_1 / draws;

  //Now that we have fractions we can calculate the ks stat.

  NumericVector vec_1_cumsum = cumsum(vec_1_frac);
  NumericVector vec_2_cumsum = cumsum(vec_2_frac);
  NumericVector diff = vec_1_cumsum - vec_2_cumsum;

  NumericVector absolute(diff.size());

  for(int i = 0; i < diff.size(); ++i)  {

    absolute(i) = std::abs(diff(i));

  }

  double ks_stat = max(absolute);

  //Now that we have the KS stat, we can do the simulations.

  int n_bins = vec_2_frac.size();
  IntegerVector uni_2 = seq_len(n_bins);

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    IntegerVector sam_0 = sample(n_bins, draws, true, vec_2_frac);
    double sam_0_ks = ks_mod_p(sam_0,
                               uni_2,
                               n_bins,
                               vec_2_frac);

    if (sam_0_ks >= ks_stat * 0.999999999999986)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual +1) / (reps +1);

  return p_value;

}
