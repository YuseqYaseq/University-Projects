//
// Created by joseph on 28.11.18.
//

#include "AdditionLayer.h"

void AGH_NN::AdditionLayer::forward_propagation(AGH_NN::Matrix2D<double>& X)
{
  results = weights * X + bias;
  lastX = &X;
}

AGH_NN::Matrix2D<double>& AGH_NN::AdditionLayer::backward_propagation(AGH_NN::Matrix2D<double> prevError)
{
  dw = *lastX * prevError.T();
  db = Matrix2D<double>(bias.get_rows(), 1, 1.0);
  //results = sum(weights.dot(prevError), OVER_COLUMNS).T();
  //results = prevError * weights.T();
  results = AGH_NN::Matrix2D<double>(lastX->get_rows(), lastX->get_cols(), 0.0);
  for(unsigned long i = 0; i < results.get_rows(); ++i)
  {
    for(unsigned long j = 0; j < results.get_cols(); ++j)
    {
      for(unsigned long k = 0; k < weights.get_rows(); ++k)
      {
        results[i][j] += prevError[k][j] * weights[k][i];
      }
    }
  }
  return results;
}

void AGH_NN::AdditionLayer::update_parameters(double learning_rate)
{

}

AGH_NN::AdditionLayer::AdditionLayer(unsigned long m, unsigned long n)
{
  results = Matrix2D<double>(m, 1, 0.0);
  weights = Matrix2D<double>(m, n, 0.0);
  bias = Matrix2D<double>(m, 1, 0.0);
  dw = Matrix2D<double>(m, n, 0.0);
  db = Matrix2D<double>(m, 1, 0.0);

}