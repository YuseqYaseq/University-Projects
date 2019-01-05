//
// Created by joseph on 28.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYERTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYERTEST_H

#include "../src/AdditionLayer.h"
#include "../src/Matrix2D.h"
#include "assert.h"

AGH_NN::AdditionLayer layer1;
AGH_NN::Matrix2D<double> X1;

AGH_NN::AdditionLayer layer2;
AGH_NN::Matrix2D<double> X2;
AGH_NN::Matrix2D<double> prevError2;

AGH_NN::AdditionLayer layer3;
AGH_NN::Matrix2D<double> X3;
AGH_NN::Matrix2D<double> prevError3;

void init()
{
  unsigned long m = 3;
  unsigned long n = 5;

  AGH_NN::Matrix2D<double> weights1(m, n, 0.0);
  for(unsigned long i = 0; i < m; ++i)
  {
    for(unsigned long j = 0; j < n; ++j)
    {
      weights1[i][j] = i + j;
    }
  }

  AGH_NN::Matrix2D<double> bias1(m, 1, 0.0);
  for(unsigned long i = 0; i < m; ++i)
  {
    bias1[i][0] = i;
  }

  layer1 = AGH_NN::AdditionLayer(m, n);
  layer1.getW() = weights1;
  layer1.getB() = bias1;

  X1 = AGH_NN::Matrix2D<double>(n, 1, 0.0);
  for(unsigned long i = 0; i < n; ++i)
  {
    X1[i][0] = i;
  }

  m = 2;
  n = 2;
  AGH_NN::Matrix2D<double> weights2(m, n, 0.0);
  weights2[0][0] =  0.1; weights2[0][1] = 0.5;
  weights2[1][0] = -0.3; weights2[1][1] = 0.8;

  AGH_NN::Matrix2D<double> bias2(m, 1, 0.0);
  bias2[0][0] = 0.0; bias2[1][0] = 0.0;

  X2 = AGH_NN::Matrix2D<double>(n, 1, 0.0);
  X2[0][0] = 0.2; X2[1][0] = 0.4;

  layer2 = AGH_NN::AdditionLayer(m, n);
  layer2.getW() = weights2;
  layer2.getB() = bias2;

  prevError2 = AGH_NN::Matrix2D<double>(m, 1, 0.0);
  prevError2[0][0] = 0.44; prevError2[1][0] = 0.52;

  //multiple examples
  unsigned long k = 3;

  m = 3;
  n = 5;
  AGH_NN::Matrix2D<double> weights3(m, n, 0.0);
  for(unsigned long i = 0; i < m; ++i)
  {
    for(unsigned long j = 0; j < n; ++j)
    {
      weights3[i][j] = i+j;
    }
  }

  X3 = AGH_NN::Matrix2D<double>(n, k, 0.0);
  for(unsigned long i = 0; i < n; ++i)
  {
    X3[i][0] = i; X3[i][1] = (i + 1) * 3; X3[i][2] = (i + 1) * 10;
  }

  AGH_NN::Matrix2D<double> bias3(m, 1, 0.0);
  for(unsigned long i = 0; i < m; ++i)
  {
    bias3[i][0] = i;
  }

  layer3 = AGH_NN::AdditionLayer(m, n);
  layer3.getW() = weights3;
  layer3.getB() = bias3;

  prevError3 = AGH_NN::Matrix2D<double>(m, k, 0.0);
  for(unsigned long i = 0; i < m; ++i)
  {
    for(unsigned long j = 0; j < k; ++j)
    {
      prevError3[i][j] = i + j;
    }
  }

}

void forwardPropagationSingleExampleTest()
{
  layer1.forward_propagation(X1);
  layer2.forward_propagation(X2);
  AGH_NN::Matrix2D<double> res1 = layer1.getRes();
  AGH_NN::Matrix2D<double> res2 = layer2.getRes();
  ASSERT_EQUALS_I(res1.get_rows(), 3);
  ASSERT_EQUALS_I(res1.get_cols(), 1);
  ASSERT_EQUALS(res1[0][0], 30.0);
  ASSERT_EQUALS(res1[1][0], 41.0);
  ASSERT_EQUALS(res1[2][0], 52.0);

  ASSERT_EQUALS_I(res2.get_rows(), 2);
  ASSERT_EQUALS_I(res2.get_cols(), 1);
  ASSERT_EQUALS(res2[0][0], 0.22);
  ASSERT_EQUALS(res2[1][0], 0.26);
}

void forwardPropagationMultipleExamplesTest()
{
  layer3.forward_propagation(X3);
  AGH_NN::Matrix2D<double> res3 = layer3.getRes();
  ASSERT_EQUALS_I(res3.get_rows(), 3);
  ASSERT_EQUALS_I(res3.get_cols(), 3);
  ASSERT_EQUALS(res3[0][0], 30.0); ASSERT_EQUALS(res3[0][1], 120.0); ASSERT_EQUALS(res3[0][2], 400.0);
  ASSERT_EQUALS(res3[1][0], 41.0); ASSERT_EQUALS(res3[1][1], 166.0); ASSERT_EQUALS(res3[1][2], 551.0);
  ASSERT_EQUALS(res3[2][0], 52.0); ASSERT_EQUALS(res3[2][1], 212.0); ASSERT_EQUALS(res3[2][2], 702.0);
}

void backwardPropagationSingleExampleTest()
{
  AGH_NN::Matrix2D<double> res2 = layer2.backward_propagation(prevError2);
  ASSERT_EQUALS_I(res2.get_rows(), 2);
  ASSERT_EQUALS_I(res2.get_cols(), 1);
  ASSERT_EQUALS_I(layer2.getDW().get_rows(), layer2.getW().get_rows());
  ASSERT_EQUALS_I(layer2.getDW().get_cols(), layer2.getW().get_cols());
  ASSERT_EQUALS_I(layer2.getDB().get_rows(), layer2.getB().get_rows());
  ASSERT_EQUALS_I(layer2.getDB().get_cols(), layer2.getB().get_cols());

  ASSERT_EQUALS(res2[0][0], -0.112);
  ASSERT_EQUALS(res2[1][0],  0.636);

  ASSERT_EQUALS(layer2.getDW()[0][0], 0.088);
  ASSERT_EQUALS(layer2.getDW()[1][0], 0.176);
  ASSERT_EQUALS(layer2.getDW()[0][1], 0.104);
  ASSERT_EQUALS(layer2.getDW()[1][1], 0.208);

  ASSERT_EQUALS(layer2.getDB()[0][0], 1.0);
  ASSERT_EQUALS(layer2.getDB()[1][0], 1.0);
}

void backwardPropagationMultipleExamplesTest()
{
  AGH_NN::Matrix2D<double> res3 = layer3.backward_propagation(prevError3);
  ASSERT_EQUALS_I(res3.get_rows(), 3);
  ASSERT_EQUALS_I(res3.get_cols(), 3);
  ASSERT_EQUALS_I(layer3.getDW().get_rows(), layer3.getW().get_rows());
  ASSERT_EQUALS_I(layer3.getDW().get_cols(), layer3.getW().get_cols());
  ASSERT_EQUALS_I(layer3.getDB().get_rows(), layer3.getB().get_rows());
  ASSERT_EQUALS_I(layer3.getDB().get_cols(), layer3.getB().get_cols());

  /*ASSERT_EQUALS(res3[0][0], -0.112);
  ASSERT_EQUALS(res3[1][0],  0.636);

  ASSERT_EQUALS(layer3.getDW()[0][0], 0.088);
  ASSERT_EQUALS(layer3.getDW()[1][0], 0.176);
  ASSERT_EQUALS(layer3.getDW()[0][1], 0.104);
  ASSERT_EQUALS(layer3.getDW()[1][1], 0.208);

  ASSERT_EQUALS(layer3.getDB()[0][0], 1.0);
  ASSERT_EQUALS(layer3.getDB()[1][0], 1.0);*/
}

void AdditionLayerTest()
{
  init();
  forwardPropagationSingleExampleTest();
  //TODO poprawić dla wielu próbek
  //forwardPropagationMultipleExamplesTest();
  backwardPropagationSingleExampleTest();
  //backwardPropagationMultipleExamplesTest();
}


#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYERTEST_H
