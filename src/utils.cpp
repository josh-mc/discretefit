#include <Rcpp.h>
#include "discretefit.h"

#include <random>
#include <algorithm>

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

  /* staring with 1 instead of 0 so that this vector will not include
   * 0's as 0's are not tabbed by rcont_tab.
   */

  int c_sums_n = c_sums.size() + 1;

  for(int i = 1; i < c_sums_n; ++i){

    for(int j = 0; j < c_sums(i - 1); ++ j){

      mat_draw.push_back(i);

    }
  }

  return wrap(mat_draw);

}


// [[Rcpp::export]]

IntegerVector RCONT_tab(IntegerVector x, int bins, int a, int b) {

  IntegerVector cts(bins);

  int t;

  for(int i = a; i < b; i++) {

    t = x(i) - 1;

    if (0 <= t && t < bins)

      cts(t)++;
  }

  return cts;
}



// [[Rcpp::export]]

IntegerVector RCONT_simulate(IntegerVector v, IntegerVector r_sum, IntegerVector c_sum)  {

  IntegerVector s_v = sample(v, v.size());

  IntegerVector q(r_sum.size() * c_sum.size());
  //v.attr("dim") = q(r_sum.size(), c_sum.size());

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

  IntegerVector v = RCONT_setup(c_sum);

  for(int i = 0; i < n; ++i)  {

    IntegerVector x = RCONT_simulate(v,
                                  r_sum,
                                  c_sum);

    return_list(i) = x;

  }

  return(return_list);

}


// [[Rcpp::export]]

IntegerVector cpp_shuffle() {

  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

  return wrap(v);

}









// [[Rcpp::export]]


std::vector<int> RCONT_setup_cpp(IntegerVector c_sums)  {

  std::vector<int> v;
  v.reserve(sum(c_sums));

  /* staring with 1 instead of 0 so that this vector will not include
   * 0's as 0's are not tabbed by rcont_tab.
   */

  int c_sums_n = c_sums.size();

  for(int i = 0; i < c_sums_n; ++i){

    for(int j = 0; j < c_sums(i); ++ j){

      v.push_back(i);

    }
  }

  return v;
}


// [[Rcpp::export]]

std::vector<int> RCONT_tab_cpp(std::vector<int> v, int nbins, int a, int b) {

  std::vector<int> cts(nbins);
  //cts.reserve(nbins);

  for(int i = a; i < b; i++) {

      cts[v[i]]++;
  }

  return cts;
}


// [[Rcpp::export]]

IntegerVector RCONT_simulate_cpp(std::vector<int> v, IntegerVector r_sum, IntegerVector c_sum)  {

  int n_c = c_sum.size();
  int n_r = r_sum.size();

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

  std::vector<int> q(n_r * n_c);
  //q.reserve(n_r * n_c);

  int count = 0;
  int count_b = 0;

  for(int i = 0; i < n_r; i++) {

    int l = r_sum(i);

    std::vector<int> out = RCONT_tab_cpp(v, n_c, count, count + l);

    for(int j = 0; j < out.size(); j++) {

      q[j + count_b] = out[j];

    }

    count += l;
    count_b += out.size();

  }

  return wrap(q);

}


// [[Rcpp::export]]

List RCONT_cpp(int n,
           IntegerVector r_sum,
           IntegerVector c_sum)  {

  List return_list(n);

  std::vector<int> v = RCONT_setup_cpp(c_sum);

  for(int i = 0; i < n; ++i)  {

    IntegerVector x = RCONT_simulate_cpp(v,
                                     r_sum,
                                     c_sum);

    return_list(i) = x;

  }

  return(return_list);

}





// [[Rcpp::export]]

List RCONT_cpp2(int n,
                IntegerVector r_sums,
                IntegerVector c_sums)  {

  List return_list(n);

  int n_c = c_sums.size();
  int n_r = r_sums.size();

  std::vector<int> v;
  v.reserve(sum(c_sums));

  for(int i = 0; i < n_c; ++i){

    for(int j = 0; j < c_sums(i); ++ j){

      v.push_back(i);

    }
  }

  for(int i = 0; i < n; ++i)  {

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

  std::vector<int> q(n_c * n_r);

  int a = 0;
  int count_b = 0;
  //int bins = c_sums.size();

  for(int i = 0; i < r_sums.size(); i++) {

    int l = r_sums(i);
    int b = a + l;

   // IntegerVector out = RCONT_tab(v, c_sum.size(), count, count + l);
   // RCONT_tab(IntegerVector x, int bins, int a, int b) {

    std::vector<int> cts(n_c);

    for(int j = a; j < b; j++) {

        cts[v[j]]++;
    }

    for(int k = 0; k < cts.size(); k++) {

      q[k + count_b] = cts[k];

    }

    a += l;
    count_b += cts.size();

  }

  return_list(i) = q;

}

return return_list;
}

