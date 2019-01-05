//
// Created by joseph on 19.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SIGMOID_LAYERS_TEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SIGMOID_LAYERS_TEST_H

#include "../src/Matrix2D.h"
#include "../src/SigmoidLayer.h"
#include "../src/LogisticRegressor.h"
class SigmoidLayerTest {

  AGH_NN::SigmoidLayer* layer1 = nullptr;
  AGH_NN::Matrix2D<double> X1 = AGH_NN::Matrix2D<double>(2, 3, 0.0);
  AGH_NN::Matrix2D<double> Y1 = AGH_NN::Matrix2D<double>(3, 2, 0.0);

  SigmoidLayerTest() {
    AGH_NN::Matrix2D<double> weights1(2, 2, 0.0);
    weights1[0][0] = 1.0; weights1[0][1] = 1.0;
    weights1[1][0] = 2.0; weights1[1][1] = 2.0;

    AGH_NN::Matrix2D<double> bias1(2, 1, 2.0);

    X1[0][0] = 1.0; X1[0][1] = 2.0; X1[0][2] = -1.0;
    X1[1][0] = 3.0; X1[1][1] = 4.0; X1[1][2] = -3.2;

    Y1[0][0] = 1.0; Y1[0][1] = 1.0;
    Y1[1][0] = 0.0; Y1[1][1] = 0.0;
    Y1[2][0] = 1.0; Y1[2][1] = 1.0;

    layer1 = new AGH_NN::SigmoidLayer(weights1, bias1);
  }

  void forwardPropagationSingleExampleTest() {
    layer1->forward_propagation(X1);
    double cost = AGH_NN::LogisticRegressor::calculateCost(layer1->getA(), Y1);

    ASSERT_EQUALS_I(layer1->getA().get_rows(), Y1.get_rows());
    ASSERT_EQUALS_I(layer1->getA().get_cols(), Y1.get_cols());

    ASSERT_EQUALS(layer1->getA()[0][0], 0.99987661);
    ASSERT_EQUALS(layer1->getA()[1][0], 0.99999386);
    ASSERT_EQUALS(layer1->getA()[2][0], 0.00449627);
    ASSERT_EQUALS(cost, 5.801545319394553);

  }

  void backwardPropagationSingleExampleTest() {
    AGH_NN::Matrix2D<double> errors =
        AGH_NN::LogisticRegressor::calculateBackPropDerivatives(layer1->getA(), Y1);
    layer1->backward_propagation(errors);

    ASSERT_EQUALS_I(layer1->getDW().get_rows(), layer1->getW().get_rows());
    ASSERT_EQUALS_I(layer1->getDW().get_cols(), layer1->getW().get_cols());
    ASSERT_EQUALS_I(layer1->getDB().get_rows(), layer1->getB().get_rows());
    ASSERT_EQUALS_I(layer1->getDB().get_cols(), layer1->getB().get_cols());

    ASSERT_EQUALS(layer1->getDW()[0][0], 0.99845601);
    ASSERT_EQUALS(layer1->getDW()[1][0], 2.39507239);
    ASSERT_EQUALS(layer1->getDB()[0][0], 0.00145557813678);


    ASSERT_EQUALS(layer1->getDW()[0][1], 0.99845601);
    ASSERT_EQUALS(layer1->getDW()[1][1], 2.39507239);
    ASSERT_EQUALS(layer1->getDB()[1][0], 0.00145557813678);
  }

  void forwardPropagationMultipleExamplesTest() {

  }

  void backwardPropagationMultipleExamplesTest() {

  }

  void cleanup() {
    delete layer1;
  }

public:
  static void test() {
    SigmoidLayerTest layerTest;
    layerTest.forwardPropagationSingleExampleTest();
    layerTest.backwardPropagationSingleExampleTest();
    layerTest.forwardPropagationMultipleExamplesTest();
    layerTest.backwardPropagationMultipleExamplesTest();
    layerTest.cleanup();
  }
};

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SIGMOID_LAYERS_TEST_H
