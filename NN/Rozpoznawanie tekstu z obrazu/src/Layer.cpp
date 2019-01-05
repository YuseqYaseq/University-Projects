//
// Created by joseph on 17.11.18.
//
#include <random>

#include "Layer.h"

AGH_NN::Layer::Layer(unsigned long currSize, unsigned long prevSize)
{
  weights = Matrix2D<double>(prevSize, currSize, 0.0);
  bias = Matrix2D<double>(currSize, 1, 0.0);
  dw = Matrix2D<double>(prevSize, currSize, 0.0);
  db = Matrix2D<double>(currSize, 1, 0.0);
}

void AGH_NN::Layer::initialize_gaussian()
{
  srand(time(NULL));
  initialize_gaussian(0.0, 1.0, static_cast<unsigned long>(rand()));
}

void AGH_NN::Layer::initialize_gaussian(double median, double variance, unsigned long seed)
{
  std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(median, variance);
  for(int i = 0; i < weights.get_cols(); ++i)
  {
    for(int j = 0; j < weights.get_rows(); ++j)
    {
      weights[j][i] = distribution(generator);
    }
    //There is no need to randomly initialize bias
    bias[i][0] = 0.0;
  }
}
