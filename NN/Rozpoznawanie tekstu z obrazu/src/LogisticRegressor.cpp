//
// Created by joseph on 01.12.18.
//

#include "LogisticRegressor.h"

double AGH_NN::LogisticRegressor::calculateCost(AGH_NN::Matrix2D<double>& A, AGH_NN::Matrix2D<double>& Y)
{
  return -avg(Y.dot(log(A)) + (-Y + 1).dot(log(-A + 1)));
}

AGH_NN::Matrix2D<double> AGH_NN::LogisticRegressor::calculateBackPropDerivatives(
                                                      AGH_NN::Matrix2D<double>& A,
                                                      AGH_NN::Matrix2D<double>& Y)
{
  return -(Y - A).div(A - A.dot(A));
}