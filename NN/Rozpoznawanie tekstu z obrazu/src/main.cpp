#include <iostream>

#include "SigmoidLayer.h"
#include "LogisticRegressor.h"
#include "../test/assert.h"

using namespace AGH_NN;

int main() {
  double learning_rate = 0.1;

  unsigned long k = 3;
  unsigned long n = 10;
  unsigned long m1 = 5;
  unsigned long m2 = 100;

  SigmoidLayer layer1(m1, n);
  ConvSigmoidLayer layer2(m2, m1);
  layer1.initialize_gaussian();
  layer2.initialize_gaussian();
  Matrix2D<double> X1(n, k, 0.0);
  X1[0][0] = 1.0; X1[0][1] = 2.0; X1[0][2] = -1.0;
  X1[1][0] = 3.0; X1[1][1] = 4.0; X1[1][2] = -3.2;
  X1[2][0] = 5.0; X1[2][1] = 7.0; X1[2][2] = -3.2;
  X1[3][0] = 7.0; X1[3][1] = 4.0; X1[3][2] =  1.2;
  X1[4][0] = 2.0; X1[4][1] = 2.0; X1[4][2] = -3.2;
  X1[5][0] = 9.0; X1[5][1] = 4.0; X1[5][2] = -3.2;
  X1[6][0] = 0.0; X1[6][1] = 4.0; X1[6][2] =  3.2;
  X1[7][0] = 4.0; X1[7][1] = 5.0; X1[7][2] = -3.2;
  X1[8][0] =-1.0; X1[8][1] = 3.0; X1[8][2] = -1.2;
  X1[9][0] = 2.0; X1[9][1] = 4.0; X1[9][2] = -3.2;

  Matrix2D<double> Y(k, m2, 0.0);
  Y[0][0] = 1.0; Y[1][0] = 0.0; Y[2][0] = 1.0;
  std::cout.precision(10);
  for(int i = 0; i < 100000; ++i)
  {
    //forward propagation
    layer1.forward_propagation(X1);
    AGH_NN::Matrix2D<double> A1 = layer1.getA().T();
    layer2.forward_propagation(A1);

    //ASSERT_EQUALS_I(A1.get_rows(), m1);
    //ASSERT_EQUALS_I(A1.get_cols(), k);



    //compute cost
    double cost = LogisticRegressor::calculateCost(layer2.getA(), Y);

    //backward propagation
    AGH_NN::Matrix2D<double> dX2 =
        layer2.backward_propagation(LogisticRegressor::calculateBackPropDerivatives(layer2.getA(), Y)).T();
    layer1.backward_propagation(dX2);

    //update parameters
    layer1.update_parameters(learning_rate);
    layer2.update_parameters(learning_rate);

    if(i % 100 == 0)
    {
      std::cout << "Cost after " << i << " iterations: " << cost << std::endl;
    }
  }
  std::cout << layer2.getW() << std::endl;
  std::cout << layer2.getB();
}