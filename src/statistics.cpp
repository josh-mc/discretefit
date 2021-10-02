#include <Rcpp.h>
#include "discretefit.h"
using namespace Rcpp;

double rms_stat(NumericVector vec_1_frac,
                NumericVector vec_2_frac)  {

  NumericVector x = pow((vec_1_frac - vec_2_frac), 2);

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double rms = sqrt(y / vec_2_frac.size());

  return rms;
}

double chisq_stat(NumericVector vector_1,
                  NumericVector vec_1_frac,
                  NumericVector vec_2_frac)  {

  NumericVector x = pow((vec_1_frac - vec_2_frac), 2) / vec_2_frac;

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double chi = y * vector_1.size();

  return chi;

}

double ks_stat(NumericVector vec_1_frac,
               NumericVector vec_2_frac)  {

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


double g2_stat(NumericVector vector_1,
                  NumericVector vec_1_frac,
                  NumericVector vec_2_frac)  {

  NumericVector x = vec_1_frac * log(vec_1_frac / vec_2_frac);

  // Taking the sum of x
  double y = 0;

  for(int i = 0; i < x.size(); i++){
    y += x[i];
  }

  double g2 = 2 * vector_1.size() * y;

  return g2;

}


