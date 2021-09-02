#include <Rcpp.h>
using namespace Rcpp;

#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]

double rms_stat(IntegerVector vector_1,
                IntegerVector vector_2)  {

  IntegerVector uni_1 = sort_unique(vector_1);
  IntegerVector uni_2 = sort_unique(vector_2);
  IntegerVector mat_0 = match(uni_2, uni_1);
  IntegerVector mat_1 = ifelse(is_na(mat_0), 0, mat_0);

  IntegerVector tab_1 = table(vector_1);

  int n_bins = uni_2.size();

  NumericVector vector_1_bins(n_bins);
  IntegerVector vector_2_bins = table(vector_2);

  for(int i = 0; i < n_bins; ++i)  {

    int a = uni_2(i);

    if(mat_1(i) > 0) {

      int a = mat_1(i) - 1;
      vector_1_bins(i) = tab_1(a);

    }

    else {

      vector_1_bins(i) = 0;

    }

  }

  NumericVector vector_2_bins_numeric = as<NumericVector>(vector_2_bins);

  //int n_vec_1 = vector_1.size();
  //int n_vec_2 = vector_2.size();

  //NumericVector vec_1_frac = vector_1_bins / n_vec_1;
  //NumericVector vec_2_frac = vector_2_bins_numeric / n_vec_2;

  NumericVector vec_1_frac = vector_1_bins / vector_1.size();
  NumericVector vec_2_frac = vector_2_bins_numeric / vector_2.size();
  NumericVector x = pow((vec_1_frac - vec_2_frac), 2);

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double rms = y / uni_2.size();

  return rms;

}


double rms_mod(IntegerVector vector_1,
               IntegerVector uni_2,
               int n_bins,
               NumericVector vec_2_frac)  {

  IntegerVector uni_1 = sort_unique(vector_1);
  IntegerVector mat_0 = match(uni_2, uni_1);
  IntegerVector mat_1 = ifelse(is_na(mat_0), 0, mat_0);

  IntegerVector tab_1 = table(vector_1);
  NumericVector vector_1_bins(n_bins);

  for(int i = 0; i < n_bins; ++i)  {

    int a = uni_2(i);

    if(mat_1(i) > 0) {

      int a = mat_1(i) - 1;
      vector_1_bins(i) = tab_1(a);

    }

    else {

      vector_1_bins(i) = 0;

    }

  }

  NumericVector vec_1_frac = vector_1_bins / vector_1.size();

  NumericVector x = pow((vec_1_frac - vec_2_frac), 2);

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double rms = y / uni_2.size();

  return rms;
}


// [[Rcpp::export]]

double rms_gof_cpp(IntegerVector vector_1,
               IntegerVector vector_2,
               double reps)  {

  //Here we take the rms_stat.

  IntegerVector uni_2 = sort_unique(vector_2);
  int n_bins = uni_2.size();

  IntegerVector vector_2_bins = table(vector_2);
  NumericVector vector_2_bins_numeric = as<NumericVector>(vector_2_bins);
  NumericVector vec_2_frac = vector_2_bins_numeric / vector_2.size();

  double rms_statistic = rms_mod(vector_1,
                                 uni_2,
                                 n_bins,
                                 vec_2_frac);

  int draws = vector_1.size();

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    IntegerVector sam_0 = sample(vector_2, draws, true);
    double sam_0_rms = rms_mod(sam_0,
                               uni_2,
                               n_bins,
                               vec_2_frac);

    if (sam_0_rms >= 0.999999999999986 * rms_statistic)  {
      total_actual += 1;
    }

  }

  double p_value = (total_actual + 1) / (reps + 1);

  return p_value;

}

