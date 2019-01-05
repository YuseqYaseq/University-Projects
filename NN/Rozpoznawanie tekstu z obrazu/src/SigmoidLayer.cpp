//
// Created by joseph on 17.11.18.
//

#include "SigmoidLayer.h"

//1 / e^(wT * X + b)
void AGH_NN::SigmoidLayer::forward_propagation(AGH_NN::Matrix2D<double>& X)
{
  lastX = &X;
  activatedWeights = AGH_NN::sigmoid2D(weights.T() * X + bias).T();
}

AGH_NN::Matrix2D<double> AGH_NN::SigmoidLayer::backward_propagation(
        const AGH_NN::Matrix2D<double>& prevError)
{
  dw = ((*lastX) * activatedWeights.dot(-activatedWeights + 1).dot(prevError)) / prevError.get_rows();
  db = avg(activatedWeights.dot(-activatedWeights + 1).dot(prevError), OVER_COLUMNS).T();
  return (weights * activatedWeights.dot(-activatedWeights + 1).dot(prevError).T()) / prevError.get_rows();
}

void AGH_NN::SigmoidLayer::update_parameters(double learning_rate)
{
  weights -= dw * learning_rate;
  bias -= db * learning_rate;
}