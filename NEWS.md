# discretefit 0.1.0

* Changed all GOF functions to class 'htest.' This means these functions now return a list that includes the p-value as well as the test statistics. In the previous version, these functions returned a numeric value directly (the p-value).
* Added the parameter 'tolerance' to all GOF functions. This allows users directly to adjust the tolerance for numerical imprecision.
* Added the function `ft_gof()` that implements the Freeman-Tukey GOF test.
* Added the function `cvm_gof()` that implements the Cramer-von Mises GOF test.
* Updated the test requiring the vector of probabilities to sum to one to include tolerance for numerical imprecision. 
* Added a `NEWS.md` file to track changes to the package.

