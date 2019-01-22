//
// Created by joseph on 08.12.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYERTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYERTEST_H

#include "assert.h"
#include "../src/ConvSigmoidLayer.h"

class ConvSigmoidLayerTest {
private:
  AGH_NN::ConvSigmoidLayer* layer = nullptr;
  AGH_NN::ConvSigmoidLayer* noPaddingLayer = nullptr;
  AGH_NN::ConvSigmoidLayer* oneNumHugePaddingLayer = nullptr;
  AGH_NN::ConvSigmoidLayer* layer2 = nullptr;

  AGH_NN::ConvSigmoidLayer* dlugopolLayer = nullptr;

  //matrix [2 x 2 x 5 x 5]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> dlugopolX;

  //matrix [2 x 2 x 3 x 3]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> X;

  //matrix [2 x 2 x 3 x 3]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> X2;

  //matrix [1 x 1 x 1 x 1]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> simpleX;

  //matrix [2 x 2 x 3 x 3]
  std::vector<AGH_NN::Matrix2D<double>> Y;

  //for 1st layer
  unsigned long k = 2;
  unsigned long d = 2;
  unsigned long w = 3;
  unsigned long h = 3;
  unsigned long m = 2;
  unsigned long wf = 3;
  unsigned long hf = 3;
  unsigned long s = 1;
  unsigned long p = 1;

  //na ten zrabany test
  unsigned long d_k = 2;
  unsigned long d_d = 2;
  unsigned long d_w = 5;
  unsigned long d_h = 5;
  unsigned long d_m = 3;
  unsigned long d_wf = 3;
  unsigned long d_hf = 3;
  unsigned long d_s = 1;
  unsigned long d_p = 1;



  ConvSigmoidLayerTest() {
    layer = new AGH_NN::ConvSigmoidLayer(k, d, w, h, m, wf, hf, s, p);
    layer->filters[0][0][0][0] = 0.0; layer->filters[0][0][0][1] = 1.0; layer->filters[0][0][0][2] = 0.0;
    layer->filters[0][0][1][0] = 1.0; layer->filters[0][0][1][1] = 2.0; layer->filters[0][0][1][2] = 1.0;
    layer->filters[0][0][2][0] = 0.0; layer->filters[0][0][2][1] = 1.0; layer->filters[0][0][2][2] = 0.0;

    layer->filters[0][1][0][0] = 0.0; layer->filters[0][1][0][1] = 1.0; layer->filters[0][1][0][2] = 0.0;
    layer->filters[0][1][1][0] = 1.0; layer->filters[0][1][1][1] = 2.0; layer->filters[0][1][1][2] = 1.0;
    layer->filters[0][1][2][0] = 0.0; layer->filters[0][1][2][1] = 1.0; layer->filters[0][1][2][2] = 0.0;

    layer->filters[1][0][0][0] = 1.2; layer->filters[1][0][0][1] = 0.34; layer->filters[1][0][0][2] = 1.1;
    layer->filters[1][0][1][0] = 1.2; layer->filters[1][0][1][1] = 0.34; layer->filters[1][0][1][2] = 1.1;
    layer->filters[1][0][2][0] = 1.2; layer->filters[1][0][2][1] = 0.34; layer->filters[1][0][2][2] = 1.1;

    layer->filters[1][1][0][0] = 1.2; layer->filters[1][1][0][1] = 0.34; layer->filters[1][1][0][2] = 1.1;
    layer->filters[1][1][1][0] = 1.2; layer->filters[1][1][1][1] = 0.34; layer->filters[1][1][1][2] = 1.1;
    layer->filters[1][1][2][0] = 1.2; layer->filters[1][1][2][1] = 0.34; layer->filters[1][1][2][2] = 1.1;

    X.resize(k);
    for(unsigned long i = 0; i < k; ++i) {
      X[i].resize(d, AGH_NN::Matrix2D<double>(h, w, 0.0));
    }

    X[0][0][0][0] = 1.0; X[0][0][0][1] = 2.0; X[0][0][0][2] = 3.0;
    X[0][0][1][0] = 4.0; X[0][0][1][1] = 5.0; X[0][0][1][2] = 6.0;
    X[0][0][2][0] = 7.0; X[0][0][2][1] = 8.0; X[0][0][2][2] = 9.0;

    X[0][1][0][0] = 0.1; X[0][1][0][1] = 0.2; X[0][1][0][2] = 0.3;
    X[0][1][1][0] = 0.4; X[0][1][1][1] = 0.5; X[0][1][1][2] = 0.6;
    X[0][1][2][0] = 0.7; X[0][1][2][1] = 0.8; X[0][1][2][2] = 0.9;

    X[1][0][0][0] = 10.0; X[1][0][0][1] = 20.0; X[1][0][0][2] = 30.0;
    X[1][0][1][0] = 40.0; X[1][0][1][1] = 50.0; X[1][0][1][2] = 60.0;
    X[1][0][2][0] = 70.0; X[1][0][2][1] = 80.0; X[1][0][2][2] = 90.0;

    X[1][1][0][0] = 100.0; X[1][1][0][1] = 200.0; X[1][1][0][2] = 300.0;
    X[1][1][1][0] = 400.0; X[1][1][1][1] = 500.0; X[1][1][1][2] = 600.0;
    X[1][1][2][0] = 700.0; X[1][1][2][1] = 800.0; X[1][1][2][2] = 900.0;

    simpleX.emplace_back(std::vector<AGH_NN::Matrix2D<double>>());
    simpleX[0].emplace_back(AGH_NN::Matrix2D<double>(1, 1, 1.0));

    noPaddingLayer = new AGH_NN::ConvSigmoidLayer(k, d, w, h, m, wf, hf, s, 0);
    noPaddingLayer->filters = layer->filters;

    oneNumHugePaddingLayer = new AGH_NN::ConvSigmoidLayer(1, 1, 1, 1, m, wf, hf, s, 2);
    oneNumHugePaddingLayer->filters = layer->filters;

    layer2 = new AGH_NN::ConvSigmoidLayer(k, d, w, h, m, wf, hf, s, p);

    layer2->filters[0][0][0][0] = 0.0; layer2->filters[0][0][0][1] = 1.0; layer2->filters[0][0][0][2] = 0.0;
    layer2->filters[0][0][1][0] = 1.0; layer2->filters[0][0][1][1] = 2.0; layer2->filters[0][0][1][2] = 1.0;
    layer2->filters[0][0][2][0] = 0.0; layer2->filters[0][0][2][1] = 1.0; layer2->filters[0][0][2][2] = 0.0;

    layer2->filters[0][1][0][0] = 0.0; layer2->filters[0][1][0][1] = 1.0; layer2->filters[0][1][0][2] = 0.0;
    layer2->filters[0][1][1][0] = 1.0; layer2->filters[0][1][1][1] = 2.0; layer2->filters[0][1][1][2] = 1.0;
    layer2->filters[0][1][2][0] = 0.0; layer2->filters[0][1][2][1] = 1.0; layer2->filters[0][1][2][2] = 0.0;

    layer2->filters[1][0][0][0] = 1.2; layer2->filters[1][0][0][1] = 0.34; layer2->filters[1][0][0][2] = 1.1;
    layer2->filters[1][0][1][0] = 1.2; layer2->filters[1][0][1][1] = 0.34; layer2->filters[1][0][1][2] = 1.1;
    layer2->filters[1][0][2][0] = 1.2; layer2->filters[1][0][2][1] = 0.34; layer2->filters[1][0][2][2] = 1.1;

    layer2->filters[1][1][0][0] = 1.2; layer2->filters[1][1][0][1] = 0.34; layer2->filters[1][1][0][2] = 1.1;
    layer2->filters[1][1][1][0] = 1.2; layer2->filters[1][1][1][1] = 0.34; layer2->filters[1][1][1][2] = 1.1;
    layer2->filters[1][1][2][0] = 1.2; layer2->filters[1][1][2][1] = 0.34; layer2->filters[1][1][2][2] = 1.1;

    X2.resize(k);
    for(unsigned long i = 0; i < k; ++i) {
      X2[i].resize(d, AGH_NN::Matrix2D<double>(h, w, 0.0));
    }
  }

  void getValueTest() {

    layer->lastX = &X;
    noPaddingLayer->lastX = &X;
    oneNumHugePaddingLayer->lastX = &simpleX;

    ASSERT_EQUALS(layer->getValue(0, 0, 0, 0, X), 8.8);
    ASSERT_EQUALS(layer->getValue(0, 1, 0, 0, X), 14.3);
    ASSERT_EQUALS(layer->getValue(0, 2, 0, 0, X), 15.4);

    ASSERT_EQUALS(layer->getValue(0, 0, 1, 0, X), 23.1);
    ASSERT_EQUALS(layer->getValue(0, 1, 1, 0, X), 33.0);
    ASSERT_EQUALS(layer->getValue(0, 2, 1, 0, X), 31.9);

    ASSERT_EQUALS(layer->getValue(0, 0, 2, 0, X), 28.6);
    ASSERT_EQUALS(layer->getValue(0, 1, 2, 0, X), 40.7);
    ASSERT_EQUALS(layer->getValue(0, 2, 2, 0, X), 35.2);

    ASSERT_EQUALS(noPaddingLayer->getValue(0, 0, 0, 0, X), 33.0);

    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 0, 0, 0, X), 0.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 1, 0, 0, X), 1.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 2, 0, 0, X), 0.0);

    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 0, 1, 0, X), 1.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 1, 1, 0, X), 2.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 2, 1, 0, X), 1.0);

    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 0, 2, 0, X), 0.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 1, 2, 0, X), 1.0);
    ASSERT_EQUALS(oneNumHugePaddingLayer->getValue(0, 2, 2, 0, X), 0.0);
  }

  void forwardPropagationTest() {
    layer->forward_propagation(X);
    ASSERT_EQUALS_I(layer->getA().size(), layer->k);
    for(unsigned long i = 0; i < k; ++i) {
      for(unsigned long j = 0; j < m; ++j) {
        ASSERT_EQUALS_I(layer->getA()[i][j].get_cols(), 3);
        ASSERT_EQUALS_I(layer->getA()[i][j].get_rows(), 3);
      }
    }
    
    ASSERT_EQUALS(layer->getA()[0][0][0][0], 8.8); ASSERT_EQUALS(layer->getA()[0][0][0][1], 14.3); ASSERT_EQUALS(layer->getA()[0][0][0][2], 15.4);
    ASSERT_EQUALS(layer->getA()[0][0][1][0], 23.1); ASSERT_EQUALS(layer->getA()[0][0][1][1], 33.0); ASSERT_EQUALS(layer->getA()[0][0][1][2], 31.9);
    ASSERT_EQUALS(layer->getA()[0][0][2][0], 28.6); ASSERT_EQUALS(layer->getA()[0][0][2][1], 40.7); ASSERT_EQUALS(layer->getA()[0][0][2][2], 35.2);
  }

  void cleanup() {
    delete layer;
    delete noPaddingLayer;
    delete oneNumHugePaddingLayer;
    delete layer2;
  }

public:
  static void test() {
    ConvSigmoidLayerTest layerTest;
    layerTest.getValueTest();
    layerTest.forwardPropagationTest();

    layerTest.cleanup();
  }
};


#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYERTEST_H
