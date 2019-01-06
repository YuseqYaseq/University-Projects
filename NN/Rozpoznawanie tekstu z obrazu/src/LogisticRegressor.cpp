//
// Created by joseph on 01.12.18.
//

#include <cmath>
#include "LogisticRegressor.h"

double AGH_NN::LogisticRegressor::calculateCost(AGH_NN::Matrix2D<double>& A, AGH_NN::Matrix2D<double>& Y)
{
  AGH_NN::Matrix2D<double> left = (-Y + 1);
  AGH_NN::Matrix2D<double> right = (AGH_NN::log(-A + 1));
  AGH_NN::Matrix2D<double> sum = Y.dot(AGH_NN::log(A)) + left.dot(right);
  for(unsigned long y = 0; y < sum.get_rows(); ++y) {
    for(unsigned long x = 0; x < sum.get_cols(); ++x) {
      if(std::isnan(sum[y][x])) {
        sum[y][x] = 0.0;
      }
    }
  }
  return -AGH_NN::avg(sum);
}

AGH_NN::Matrix2D<double> AGH_NN::LogisticRegressor::calculateBackPropDerivatives(
                                                      AGH_NN::Matrix2D<double>& A,
                                                      AGH_NN::Matrix2D<double>& Y)
{
  AGH_NN::Matrix2D<double> sum = -(Y - A).div(A - A.dot(A));
  for(unsigned long y = 0; y < sum.get_rows(); ++y) {
    for(unsigned long x = 0; x < sum.get_cols(); ++x) {
      if(std::isnan(sum[y][x])) {
        sum[y][x] = 0.0;
      }
    }
  }
  return sum;
}