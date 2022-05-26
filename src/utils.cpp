#include <Rcpp.h>
#include "discretefit.h"

#include <random>
#include <algorithm>


#include <iostream>
#include <vector>
#include <cmath>


#include <dqrng.h>
#include "pcg_random.h"


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

List rcont32_cpp(int n,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 int seed)  {

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

  pcg32 g(seed);

  for(int i = 0; i < n; ++i)  {

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

    NumericVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_r, n_c);
    return_list(i) = qq;

  }

  return return_list;
}



// [[Rcpp::export]]

List rcont31_cpp(int n,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 int seed)  {

  List return_list(n);

  int n_c = c_sums.size();
  int n_r = r_sums.size();

  std::vector<int> v;
  v.reserve(sum(r_sums));

  for(int i = 0; i < n_r; ++i){

    for(int j = 0; j < r_sums(i); ++ j){

      v.push_back(i);

    }
  }

  pcg32 g(seed);

  for(int i = 0; i < n; ++i)  {

    if (i % 1000 == 0){
      Rcpp::checkUserInterrupt();
    }

    // Shuffle

    int n_v = v.size();

    for(int i = 0; i < (n_v - c_sums(n_c -1)); ++i)  {

      std::uniform_int_distribution<int> dist(i, (n_v - 1));
      int num = dist(g);

      std::swap(v[i], v[num]);

    }

    int n_q = n_c * n_r;

    std::vector<int> q(n_q);

    int a = 0;
    int count_b = 0;
    //int bins = c_sums.size();

    std::vector<int> total_cts(n_r);

    for(int i = 0; i < n_c - 1; i++) {

      int l = c_sums(i);
      int b = a + l;

      std::vector<int> cts(n_r);

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

    for(int i = 0; i < n_r; i++) {

      q[n_q - n_r + i] = r_sums[i] - total_cts[i];

    }

    NumericVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;

  }

  return return_list;
}





// [[Rcpp::export]]

List rcont3_cpp (int n,
                 IntegerVector r_sums,
                 IntegerVector c_sums,
                 int seed)  {

  List return_list(n);

  int n_r = r_sums.size();
  int n_c = c_sums.size();

  int loc_largest = 0;
  int largest = 0;

  for(int i = 0; i < n_c; ++i) {

    if(largest < c_sums(i)) {

      largest = c_sums(i);
      loc_largest = i;

    }

  }

  std::vector<int> v;
  v.reserve(sum(r_sums));

  for(int i = 0; i < n_r; ++i){

    for(int j = 0; j < r_sums(i); ++ j){

      v.push_back(i);

    }
  }

  pcg32 g(seed);

  for(int i = 0; i < n; ++i)  {

    if (i % 1000 == 0){
      Rcpp::checkUserInterrupt();
    }

    // Shuffle

    int n_v = v.size();

    for(int i = 0; i < (n_v - c_sums(loc_largest)); ++i)  {

      std::uniform_int_distribution<int> dist(i, (n_v - 1));
      // Why minus one?
      int num = dist(g);

      std::swap(v[i], v[num]);

    }

    int n_q = n_c * n_r;
    std::vector<int> q(n_q);

    int a = 0;
    int count_b = 0;
    std::vector<int> total_cts(n_r);

    for(int i = 0; i < n_c; i++) {

      int l = c_sums(i);
      int b = a + l;

      if(i != loc_largest) {

        std::vector<int> cts(n_r);

        for(int j = a; j < b; j++) {

          cts[v[j]]++;

          total_cts[v[j]]++;

        }

        for(int k = 0; k < n_r; k++) {

          q[count_b + k] = cts[k];

        }

      }

      a += l;
      count_b += n_r;

    }

    // Largest col.

    for(int i = 0; i < n_r; i++) {

      q[(loc_largest * n_r) + i] = r_sums[i] - total_cts[i];

    }

    NumericVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;

  }

  return return_list;
}

