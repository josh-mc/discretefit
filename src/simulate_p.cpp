#include <Rcpp.h>
#include "discretefit.h"
#include "pcg_random.h"

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


// [[Rcpp::export]]

double ind_sim(int reps,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 NumericVector E,
                 int seed,
                 double statistic,
                 double tolerance)  {

  int n_c = c_sums.size();
  int n_r = r_sums.size();

  std::vector<int> v;
  v.reserve(sum(c_sums));

  for(int i = 0; i < n_c; ++i){

    for(int j = 0; j < c_sums(i); ++ j){

      v.push_back(i);

    }
  }

  pcg32 g(seed);

  double total_actual = 0;

  for(int i = 0; i < reps; ++i)  {

    if (i % 1000 == 0){
      Rcpp::checkUserInterrupt();
    }

    // Shuffle

    int n_v = v.size();

    for(int i = 0; i < (n_v - r_sums(n_r -1)); ++i)  {

      std::uniform_int_distribution<int> dist(i, (n_v - 1));
      int num = dist(g);

      std::swap(v[i], v[num]);

    }

    int n_q = n_c * n_r;

    std::vector<int> q(n_q);

    int a = 0;
    int count_b = 0;
    //int bins = c_sums.size();

    std::vector<int> total_cts(n_c);

    for(int i = 0; i < n_r - 1; i++) {

      int l = r_sums(i);
      int b = a + l;

      std::vector<int> cts(n_c);

      for(int j = a; j < b; j++) {

        cts[v[j]]++;

        total_cts[v[j]]++;

      }

      for(int k = 0; k < cts.size(); k++) {

        q[k + count_b] = cts[k];

      }

      a += l;
      count_b += cts.size();

    }

    //Last row/col.

    for(int i = 0; i < n_c; i++) {

      q[n_q - n_c + i] = c_sums[i] - total_cts[i];

    }

    //Chisq stat

    NumericVector O = wrap(q);


    //Rcout << "The value of O : " << O << "\n";
    //Rcout << "The value of E : " << E << "\n";


    double sim_statistic = sum(pow((O - E), 2) / E);

    //Rcout << "The value of sim_statistic : " << sim_statistic << "\n";

      if (sim_statistic >= (1 - tolerance) * statistic)  {
        total_actual += 1;
      }

      //Rcout << "The value of total_actual : " << total_actual << "\n";

  }

  double p_val = (total_actual + 1) / (reps + 1);

  return p_val;
}


// [[Rcpp::export]]

double ind_sim2(int reps,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 NumericVector E,
                 int seed,
                 double statistic,
                 double tolerance) {

  double total_actual = 0;

  List simulations = rcont3_cpp(reps,
                                r_sums,
                                c_sums,
                                seed)

  for(int i = 0; i < reps; ++i)  {

    NumericVector O = wrap(simulations[i]);

    double sim_statistic = sum(pow((O - E), 2) / E);

    if (sim_statistic >= (1 - tolerance) * statistic)  {
      total_actual += 1;

      }
  }

  double p_val = (total_actual + 1) / (reps + 1);

  return p_val;

}



