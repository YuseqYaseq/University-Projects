//
// Created by joseph on 17.11.18.
//

#include "FullyConnectedLayer.h"

//1 / e^(wT * X + b)
void AGH_NN::FullyConnectedLogisticRegressionLayer::forward_propagation(AGH_NN::Matrix2D<double> X)
{
  activatedWeights = AGH_NN::sigmoid2D(weights.T().dot(X) + bias);
}

AGH_NN::Matrix2D<double> AGH_NN::FullyConnectedLogisticRegressionLayer::backward_propagation(
        AGH_NN::Matrix2D<double> prevError)
{
  
}

//cost = (-1/m) * np.sum(Y * np.log(A) + (1 - Y) * np.log(1 - A))

double AGH_NN::FullyConnectedLogisticRegressionLayer::compute_cost(AGH_NN::Matrix2D<double> Y)
{
  return -avg(Y * log(activatedWeights) + (1.0 - Y) * log(1.0 - activatedWeights));
}

void AGH_NN::FullyConnectedLogisticRegressionLayer::update_parameters(double learning_rate)
{
  weights -= learning_rate * dw;
  bias -= learning_rate * db;
}