//
// Created by joseph on 18.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYERTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYERTEST_H

#include "../src/Matrix2D.h"
#include "../src/ReLULayer.h"

class ReLULayerTest {

  AGH_NN::Matrix2D<double> X;
  AGH_NN::Matrix2D<double> Y;
  AGH_NN::ReLULayer layer;

  ReLULayerTest() {
    //layer
  }

  void forwardPropagationTest() {

  }

  void backwardPropagationTest() {

  }

  void cleanup() {

  }

public:
  static void test() {
    ReLULayerTest test;
    test.forwardPropagationTest();
    test.backwardPropagationTest();

    test.cleanup();
  }
};

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYERTEST_H
