#include <iostream>

#include "SigmoidLayer.h"
#include "ActualConvSigmoidLayer.h"
#include "LogisticRegressor.h"
#include "MaxPoolLayer.h"
#include "../test/assert.h"

using namespace AGH_NN;

//model:
//one example
//conv 3x32x32 s=1, p=1, 4 filters 3x3 -> 4x32x32
//sigmoid 1x(4 * 32 * 32) -> 3

int main() {
  double learning_rate = 0.1;
  unsigned long seed = 3;
  double median = 0.0;
  double variance = 0.01;

  //conv layer1 hyperparams
  unsigned long k1 = 3;
  unsigned long d1 = 3;
  unsigned long w1 = 256;
  unsigned long h1 = 256;
  unsigned long m1 = 50;
  unsigned long wf1 = 3;
  unsigned long hf1 = 3;
  unsigned long s1 = 1;
  unsigned long p1 = 1;

  //maxpool layer2 hyperparams
  unsigned long k2 = k1;
  unsigned long d2 = m1;
  unsigned long w2 = 256;
  unsigned long h2 = 256;
  unsigned long wf2 = 2;
  unsigned long hf2 = 2;
  unsigned long p2 = 0;
  unsigned long s2 = 1;

  //sigmoid layer3 hyperparams
  unsigned long k3 = k1;
  unsigned long n3 = 50 * 128 * 128;
  unsigned long m3 = 3;

  //init layers
  ActualConvSigmoidLayer layer1(k1, d1, w1, h1, m1, wf1, hf1, s1, p1);
  MaxPoolLayer layer2(k2, d2, w2, h2, wf2, hf2);
  SigmoidLayer layer3(m3, n3);


  layer1.layer->initialize_gaussian(median, variance, 3);
  layer3.initialize_gaussian(median, variance, 3);

  //data
  std::vector<std::vector<Matrix2D<double>>> X(k1,
      std::vector<Matrix2D<double>>(d1, Matrix2D<double>(h1, w1, 0.0)));
  Matrix2D<double> Y(k3, m3, 0.0);

  //init data
  srand(seed);
  for(unsigned long y = 0; y < k3; ++y) {
    for(unsigned long x = 0; x < m3; ++x) {
      Y[y][x] = rand() % 2;
    }
  }
  for(unsigned long ex = 0; ex < k1; ++ex) {
    for(unsigned long dim = 0; dim < d1; ++dim) {
      X[ex][dim].initialize_gaussian(median, variance, 3);
    }
  }

  std::cout.precision(10);
  for(int i = 0; i < 100; ++i)
  {
    //forward propagation
    layer1.forward_propagation(X);
    layer2.forward_propagation(layer1.layer->getA());

    Matrix2D<double> A2 = unfold(layer2.getA());
    layer3.forward_propagation(A2);

    //compute cost
    double cost = LogisticRegressor::calculateCost(layer3.getA(), Y);

    //backward propagation
    AGH_NN::Matrix2D<double> dX2 =
        layer3.backward_propagation(LogisticRegressor::calculateBackPropDerivatives(layer3.getA(), Y));

    std::vector<std::vector<AGH_NN::Matrix2D<double>>> folded_dX2 = fold(dX2, m1, w1, h1);
    layer1.backward_propagation(layer2.backward_propagation(folded_dX2));

    //update parameters
    layer1.update_parameters(learning_rate);
    layer2.update_parameters(learning_rate);
    layer3.update_parameters(learning_rate);

    if(i % 1 == 0)
    {
      std::cout << "Cost after " << i << " iterations: " << cost << std::endl;

      std::cout << "weights: " << std::endl;
      std::cout << layer1.layer->getW()[0][0] << std::endl;
      std::cout << layer1.layer->getB();
    }
  }
}