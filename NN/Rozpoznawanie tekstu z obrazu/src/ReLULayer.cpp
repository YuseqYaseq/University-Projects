//
// Created by joseph on 18.01.19.
//

#include "ReLULayer.h"

void AGH_NN::ReLULayer::forward_propagation(AGH_NN::Matrix2D<double> &X)
{
  lastX = &X;
  activatedWeights = (weights.T() * X + bias).T();
  for(unsigned long y = 0; y < activatedWeights.get_rows(); ++y)
  {
    for(unsigned long x = 0; x < activatedWeights.get_cols(); ++x)
    {
      if(activatedWeights[y][x] < 0.0)
        activatedWeights[y][x] = 0.0;
    }
  }
}

AGH_NN::Matrix2D<double> AGH_NN::ReLULayer::backward_propagation(const AGH_NN::Matrix2D<double> &prevError)
{
  dw = (*lastX) * prevError;
  //db =
  AGH_NN::Matrix2D<double> ret(lastX->get_rows(), lastX->get_cols(), 0.0);
  ret = weights * prevError;
  for(unsigned long y = 0; y < activatedWeights.get_rows(); ++y)
  {
    for(unsigned long x = 0; x < activatedWeights.get_cols(); ++x)
    {
      /*if(lastX[y][x] > 0)
      {
        activatedWeights[y][x] = 1;
      }
      else
      {
        activatedWeights[y][x] = 0.0;
      }*/
    }
  }
}

void AGH_NN::ReLULayer::update_parameters(double learning_rate)
{
  weights -= dw * learning_rate;
  bias -= db * learning_rate;
}
