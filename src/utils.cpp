#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

NumericVector compute_vec_1_frac(IntegerVector x,
                              int n_bins,
                              int draws) {

    NumericVector counts(n_bins);

    for (auto& i : x) {

      if (i > 0 && i <= n_bins)

        counts[i - 1]++;
    }

    return counts / draws;
  }


// [[Rcpp::export]]

IntegerVector RCONT_setup(IntegerVector c_sums)  {

  std::vector<int> mat_draw;

  mat_draw.reserve(sum(c_sums));

  for(int i = 0; i < c_sums.size(); ++i){

    for(int j = 0; j < c_sums[i]; ++ j){

      //This for some reason would not take a (). Thus [] above.

      mat_draw.push_back(i);

    }
  }

  IntegerVector out = wrap(mat_draw);

  return(out + 1);

}


// [[Rcpp::export]]

IntegerVector RCONT_tab(IntegerVector x, int bins, int a, int b) {

  IntegerVector cts(bins);

  int t;

  for(int i = a; i < b; i++) {

    t = x[i] - 1;

    if (0 <= t && t < bins)

      cts[t]++;
  }

  return cts;
}



// [[Rcpp::export]]

IntegerVector RCONT_simulate(IntegerVector v, IntegerVector r_sum, IntegerVector c_sum)  {

  IntegerVector s_v = sample(v, v.size());

  IntegerVector q(r_sum.size() * c_sum.size());

  int count = 0;
  int count_b = 0;

  for(int i = 0; i < r_sum.size(); i++) {

    int l = r_sum(i);

    IntegerVector out = RCONT_tab(s_v, c_sum.size(), count, count + l);

    for(int j = 0; j < out.size(); j++) {

      q(j + count_b) = out(j);

    }

    count += l;
    count_b += out.size();

  }

  return q;

}


// [[Rcpp::export]]

List RCONT(int n,
           IntegerVector r_sum,
           IntegerVector c_sum)  {

  List return_list(n);

  IntegerVector v = RCONT_setup(c_sum) + 1;

  for(int i = 0; i < n; ++i)  {

    IntegerVector x = RCONT_simulate(v,
                                  r_sum,
                                  c_sum);

    return_list[i] = x;

  }

  return(return_list);

}
