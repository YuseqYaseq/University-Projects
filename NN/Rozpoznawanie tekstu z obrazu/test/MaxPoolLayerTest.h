//
// Created by joseph on 05.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYERTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYERTEST_H

#include "assert.h"
#include "../src/MaxPoolLayer.h"


class MaxPoolLayerTest {
private:
  AGH_NN::MaxPoolLayer* layer1 = nullptr;
  AGH_NN::MaxPoolLayer* layer2 = nullptr;

  //matrix [2 x 2 x 2 x 2]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> X;

  //matrix [2 x 2 x 1 x 1]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> Y;

  //matrix [2 x 2 x 1 x 1]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> errors;

  //for 1st layer
  unsigned long k = 2;
  unsigned long d = 2;
  unsigned long w = 2;
  unsigned long h = 2;
  unsigned long wf = 2;
  unsigned long hf = 2;

  MaxPoolLayerTest() {
    layer1 = new AGH_NN::MaxPoolLayer(k, d, w, h, wf, hf);

    X.resize(k);
    for(unsigned long i = 0; i < k; ++i) {
      X[i].resize(d, AGH_NN::Matrix2D<double>(h, w, 0.0));
    }

    X[0][0][0][0] = 1.0; X[0][0][0][1] = 2.0;
    X[0][0][1][0] = 4.0; X[0][0][1][1] = 5.0;

    X[0][1][0][0] = 0.1; X[0][1][0][1] = 0.2;
    X[0][1][1][0] = 0.5; X[0][1][1][1] = 0.1;

    X[1][0][0][0] = 90.0; X[1][0][0][1] = 20.0;
    X[1][0][1][0] = 00.0; X[1][0][1][1] = 50.0;

    X[1][1][0][0] = 100.0; X[1][1][0][1] = 700.0;
    X[1][1][1][0] = 400.0; X[1][1][1][1] = 100.0;

    Y.resize(k);
    for(unsigned long i = 0; i < k; ++i) {
      Y[i].resize(d, AGH_NN::Matrix2D<double>(1, 1, 0.0));
    }

    Y[0][0][0][0] = 5.0; Y[0][1][0][0] = 0.5;
    Y[1][0][0][0] = 90.0; Y[1][1][0][0] = 700.0;

    errors.resize(k);
    for(unsigned long i = 0; i < k; ++i) {
      errors[i].resize(d, AGH_NN::Matrix2D<double>(1, 1, 0.0));
    }

    errors[0][0][0][0] = 0.3; errors[0][1][0][0] = 0.5;
    errors[1][0][0][0] = 0.2; errors[1][1][0][0] = 0.1;

  }

  void forwardPropagationMultipleExamplesTest() {
    layer1->forward_propagation(X);

    ASSERT_EQUALS_I(layer1->getA()[0][0].get_rows(), 1);
    ASSERT_EQUALS_I(layer1->getA()[0][0].get_cols(), 1);

    ASSERT_EQUALS(layer1->getA()[0][0][0][0], Y[0][0][0][0]);
    ASSERT_EQUALS(layer1->getA()[0][1][0][0], Y[0][1][0][0]);
    ASSERT_EQUALS(layer1->getA()[1][0][0][0], Y[1][0][0][0]);
    ASSERT_EQUALS(layer1->getA()[1][1][0][0], Y[1][1][0][0]);
  }

  void backwardPropagationMultipleExamplesTest() {
    std::vector<std::vector<AGH_NN::Matrix2D<double>>>& backpropRes = layer1->backward_propagation(errors);

    ASSERT_EQUALS(backpropRes[0][0][0][0], 0.0); ASSERT_EQUALS(backpropRes[0][0][0][1], 0.0);
    ASSERT_EQUALS(backpropRes[0][0][1][0], 0.0); ASSERT_EQUALS(backpropRes[0][0][1][1], 0.3);

    ASSERT_EQUALS(backpropRes[0][1][0][0], 0.0); ASSERT_EQUALS(backpropRes[0][1][0][1], 0.0);
    ASSERT_EQUALS(backpropRes[0][1][1][0], 0.5); ASSERT_EQUALS(backpropRes[0][1][1][1], 0.0);

    ASSERT_EQUALS(backpropRes[1][0][0][0], 0.2); ASSERT_EQUALS(backpropRes[1][0][0][1], 0.0);
    ASSERT_EQUALS(backpropRes[1][0][1][0], 0.0); ASSERT_EQUALS(backpropRes[1][0][1][1], 0.0);

    ASSERT_EQUALS(backpropRes[1][1][0][0], 0.0); ASSERT_EQUALS(backpropRes[1][1][0][1], 0.1);
    ASSERT_EQUALS(backpropRes[1][1][1][0], 0.0); ASSERT_EQUALS(backpropRes[1][1][1][1], 0.0);
  }

  void cleanup() {
    delete layer1;
  }

public:
  static void test() {
    MaxPoolLayerTest layerTest;
    layerTest.forwardPropagationMultipleExamplesTest();
    layerTest.backwardPropagationMultipleExamplesTest();

    layerTest.cleanup();
  };
};


#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYERTEST_H
