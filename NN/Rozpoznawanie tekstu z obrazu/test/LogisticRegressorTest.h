//
// Created by joseph on 06.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LOGISTICREGRESSORTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LOGISTICREGRESSORTEST_H

#include "assert.h"
#include "../src/LogisticRegressor.h"

class LogisticRegressorTest {
private:

  AGH_NN::Matrix2D<double>* A1;
  AGH_NN::Matrix2D<double>* A2;
  AGH_NN::Matrix2D<double>* A3;
  AGH_NN::Matrix2D<double>* A4;
  AGH_NN::Matrix2D<double>* Y1;
  AGH_NN::Matrix2D<double>* Y2;
  AGH_NN::Matrix2D<double>* Y3;
  AGH_NN::Matrix2D<double>* Y4;

  LogisticRegressorTest() {
    A1 = new AGH_NN::Matrix2D<double>(1, 2, 0.0);
    A2 = new AGH_NN::Matrix2D<double>(2, 1, 1.0);
    A3 = new AGH_NN::Matrix2D<double>(2, 1, 0.0);
    A4 = new AGH_NN::Matrix2D<double>(1, 3, 1.0);
    (*A4)[0][1] = 1e-10;

    Y1 = new AGH_NN::Matrix2D<double>(1, 2, 0.0);
    Y2 = new AGH_NN::Matrix2D<double>(2, 1, 1.0);
    Y3 = new AGH_NN::Matrix2D<double>(2, 1, 1.0);
    Y4 = new AGH_NN::Matrix2D<double>(1, 3, 1.0);
    (*Y4)[0][1] = 0.0;
  }

  void calculateCostTest() {
    ASSERT_EQUALS(AGH_NN::LogisticRegressor::calculateCost(*A1, *Y1), 0.0);
    ASSERT_EQUALS(AGH_NN::LogisticRegressor::calculateCost(*A2, *Y2), 0.0);
    ASSERT_EQUALS(AGH_NN::LogisticRegressor::calculateCost(*A3, *Y3), INFINITY);
    ASSERT_EQUALS(AGH_NN::LogisticRegressor::calculateCost(*A4, *Y4), 0.0);
  }

  void calculateBackPropDerivativesTest() {

  }

  void cleanup() {
    delete A1;
    delete A2;
    delete A3;
    delete A4;
    delete Y1;
    delete Y2;
    delete Y3;
    delete Y4;
  }

public:
  static void test() {
    LogisticRegressorTest regressorTest;
    regressorTest.calculateCostTest();
    regressorTest.calculateBackPropDerivativesTest();

    regressorTest.cleanup();
  }
};

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LOGISTICREGRESSORTEST_H
