//
// Created by joseph on 14.11.18.
//

#include "Matrix2DTest.h"
#include "LogisticRegressorTest.h"
#include "LayerTest.h"
#include "SigmoidLayerTest.h"
#include "ConvSigmoidLayerTest.h"
#include "MaxPoolLayerTest.h"


int main() {
  Matrix2DTest();
  LogisticRegressorTest::test();
  LayerTest::test();
  SigmoidLayerTest::test();
  ConvSigmoidLayerTest::test();
  MaxPoolLayerTest::test();
}