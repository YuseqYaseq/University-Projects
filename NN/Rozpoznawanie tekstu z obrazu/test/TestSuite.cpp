//
// Created by joseph on 14.11.18.
//

#include "Matrix2DTest.h"
#include "SigmoidLayerTest.h"
#include "ConvSigmoidLayerTest.h"
#include "MaxPoolLayerTest.h"

int main() {
  Matrix2DTest();
  SigmoidLayerTest::test();
  ConvSigmoidLayerTest::test();
  MaxPoolLayerTest::test();
}