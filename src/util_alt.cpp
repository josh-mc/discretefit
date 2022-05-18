#include <Rcpp.h>

#include <iostream>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include "random.h"

using namespace Rcpp;

// [[Rcpp::export]]

List rcont_j_par_pcg(int n,
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

  std::random_device rd;
  pcg g(rd);

  for(int i = 0; i < n; ++i)  {

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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}


// [[Rcpp::export]]

List rcont_cpp(int n,
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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}




// [[Rcpp::export]]

List rcont_j(int n,
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

  std::random_device rd;
  std::mt19937 g(rd());

  for(int i = 0; i < n; ++i)  {

    // Shuffle

    int n_v = v.size();

    for(int i = 0; i < (n_v - 1); ++i)  {

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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}

// [[Rcpp::export]]

List rcont_j_par(int n,
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

  std::random_device rd;
  std::mt19937 g(rd());

  for(int i = 0; i < n; ++i)  {

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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}




// [[Rcpp::export]]

List rcont_cpp2(int n,
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

    //Is there a way to save by not shuffling last n - x?

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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}



// [[Rcpp::export]]

List rcont_r(int n,
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

  IntegerVector vs = wrap(v);

  for(int i = 0; i < n; ++i)  {

    /* std::random_device rd;
     std::mt19937 g(rd());

     std::shuffle(v.begin(), v.end(), g);

     */

    IntegerVector s_v = sample(vs, v.size());

    std::vector<int> vv = as<std::vector<int>>(s_v);

    std::vector<int> q(n_c * n_r);

    int a = 0;
    int count_b = 0;
    //int bins = c_sums.size();

    for(int i = 0; i < r_sums.size(); i++) {

      int l = r_sums(i);
      int b = a + l;

      std::vector<int> cts(n_c);

      for(int j = a; j < b; j++) {

        cts[vv[j]]++;
      }

      for(int k = 0; k < cts.size(); k++) {

        q[k + count_b] = cts[k];

      }

      a += l;
      count_b += cts.size();

    }

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;

  }

  return return_list;
}


// [[Rcpp::export]]

List rcont_r2(int n,
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

  IntegerVector vs = wrap(v);

  for(int i = 0; i < n; ++i)  {

    IntegerVector s_v = sample(vs, v.size() - r_sums(n_r -1));

    // Don't need sample for last row/col

    std::vector<int> vv = as<std::vector<int>>(s_v);


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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}



// [[Rcpp::export]]

List rcont_r3(int n,
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

  IntegerVector vs = wrap(v);

  for(int i = 0; i < n; ++i)  {


    IntegerVector s_v = sample(vs, v.size());

    //IntegerVector s_v = dqrng::dqsample_int(vs, v.size() - r_sums(n_r -1));

    // Don't need sample for last row/col

    std::vector<int> vv = as<std::vector<int>>(s_v);


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

    IntegerVector qq = wrap(q);
    qq.attr("dim") = Dimension(n_c, n_r);
    return_list(i) = qq;



  }

  return return_list;
}










// [[Rcpp::export]]
IntegerVector RCONT_setup(IntegerVector c_sums)  {

  std::vector<int> v;
  v.reserve(sum(c_sums));

  for(int i = 0; i < c_sums.size(); ++i){

    for(int j = 0; j < c_sums(i); ++ j){

      v.push_back(i);

    }
  }

  return wrap(v);
}


// [[Rcpp::export]]
IntegerVector RCONT_tab(IntegerVector v, int bins, int a, int b) {

  std::vector<int> cts(bins);

  for(int j = a; j < b; j++) {

    cts[v[j]]++;
  }

  return wrap(cts);
}



// [[Rcpp::export]]
IntegerVector RCONT_simulate(IntegerVector v,
                             IntegerVector r_sum,
                             IntegerVector c_sum)  {


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
IntegerVector shuffle_j(IntegerVector x, int seed)  {

  int n_x = x.size();

  std::mt19937 g(seed);

  for(int i = 0; i < (n_x - 1); ++i)  {

    std::uniform_int_distribution<int> dist(i, (n_x - 1));
    int num = dist(g);

    std::swap(x[i], x[num]);

  }

  return x;

}

//RNGs

// [[Rcpp::export]]

List test_cpp2(int n, int x)  {

  List return_list(n);

  std::vector<int> v;
  v.reserve(x);

  for(int i = 0; i < x; ++i) {

    v.push_back(i);

  }

  std::random_device rd;
  pcg rand(rd);

  for(int i = 0; i < n; ++i)  {

    std::shuffle(v.begin(), v.end(), rand);

    return_list(i) = v;

  }

  return return_list;
}




// [[Rcpp::export]]

void test_pcg(int x)  {

  std::vector<int> v;
  v.reserve(x);

  for(int i = 0; i < x; ++i) {

    v.push_back(i);

  }

  std::random_device rd;
  pcg g(rd);

  std::shuffle(v.begin(), v.end(), g);

}





// [[Rcpp::export]]

void test_mt(int x)  {

  std::vector<int> v;
  v.reserve(x);

  for(int i = 0; i < x; ++i) {

    v.push_back(i);

  }

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(v.begin(), v.end(), g);

}


// [[Rcpp::export]]

void test_splitmix(int x)  {

  std::vector<int> v;
  v.reserve(x);

  for(int i = 0; i < x; ++i) {

    v.push_back(i);

  }

  std::random_device rd;
  splitmix g(rd);
  std::shuffle(v.begin(), v.end(), g);

}



// [[Rcpp::export]]

void test_xorshift(int x)  {

  std::vector<int> v;
  v.reserve(x);

  for(int i = 0; i < x; ++i) {

    v.push_back(i);

  }

  std::random_device rd;
  xorshift g(rd);

  std::shuffle(v.begin(), v.end(), g);

}


// [[Rcpp::export]]

void test_rcpp(int x)  {

  IntegerVector v = seq(0, x);
  IntegerVector s_v = sample(v, x);

}

// [[Rcpp::export]]
Rcpp::IntegerVector shuffle_cpp_pcg(Rcpp::IntegerVector x)  {
  std::random_device rd;
  pcg g(rd);
  std::shuffle(x.begin(), x.end(), g);
  return x;
}




// [[Rcpp::export]]
IntegerVector shuffle_j_pcg(IntegerVector x)  {

  int n_x = x.size();

  std::random_device rd;
  pcg g(rd);

  for(int i = 0; i < (n_x - 1); ++i)  {

    std::uniform_int_distribution<int> dist(i, (n_x - 1));
    int num = dist(g);

    std::swap(x[i], x[num]);

  }

  return x;

}
