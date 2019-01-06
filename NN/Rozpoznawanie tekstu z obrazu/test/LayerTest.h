//
// Created by joseph on 06.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYERTEST_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYERTEST_H

#include <vector>
#include "assert.h"
#include "../src/Layer.h"

class LayerTest {
private:

  unsigned long k = 2;
  unsigned long d = 3;
  unsigned long w = 2;
  unsigned long h = 2;

  //conv result [k x d x w x h]
  std::vector<std::vector<AGH_NN::Matrix2D<double>>>* X;

  //unfold result [k x (d * w * h)]
  AGH_NN::Matrix2D<double>* Y;

  LayerTest() {
    X = new std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
        std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(h, w, 0.0)));

    Y = new AGH_NN::Matrix2D<double>(d * w * h, k, 0.0);

    (*X)[0][0][0][0] = 1.0; (*X)[0][0][0][1] = 2.0;
    (*X)[0][1][0][0] = 3.0; (*X)[0][1][0][1] = 4.0;
    (*X)[0][2][0][0] = 5.0; (*X)[0][2][0][1] = 6.0;

    (*X)[1][0][0][0] = 7.0; (*X)[1][0][0][1] =  8.0;
    (*X)[1][1][0][0] = 9.0; (*X)[1][1][0][1] = 10.0;
    (*X)[1][2][0][0] = 11.0;(*X)[1][2][0][1] = 12.0;

    (*X)[0][0][1][0] = 1.5; (*X)[0][0][1][1] = 2.5;
    (*X)[0][1][1][0] = 3.5; (*X)[0][1][1][1] = 4.5;
    (*X)[0][2][1][0] = 5.5; (*X)[0][2][1][1] = 6.5;

    (*X)[1][0][1][0] = 7.5; (*X)[1][0][1][1] =  8.5;
    (*X)[1][1][1][0] = 9.5; (*X)[1][1][1][1] = 10.5;
    (*X)[1][2][1][0] = 11.5;(*X)[1][2][1][1] = 12.5;

    (*Y)[0][0] = 1.0; (*Y)[1][0] = 2.0; (*Y)[ 2][0] = 1.5; (*Y)[ 3][0] = 2.5;
    (*Y)[4][0] = 3.0; (*Y)[5][0] = 4.0; (*Y)[ 6][0] = 3.5; (*Y)[ 7][0] = 4.5;
    (*Y)[8][0] = 5.0; (*Y)[9][0] = 6.0; (*Y)[10][0] = 5.5; (*Y)[11][0] = 6.5;

    (*Y)[0][1] =  7.0; (*Y)[1][1] =  8.0; (*Y)[ 2][1] =  7.5; (*Y)[ 3][1] =  8.5;
    (*Y)[4][1] =  9.0; (*Y)[5][1] = 10.0; (*Y)[ 6][1] =  9.5; (*Y)[ 7][1] = 10.5;
    (*Y)[8][1] = 11.0; (*Y)[9][1] = 12.0; (*Y)[10][1] = 11.5; (*Y)[11][1] = 12.5;
  }

  void unfoldTest() {
    AGH_NN::Matrix2D<double> res = AGH_NN::unfold(*X);

    ASSERT_EQUALS_I(res.get_cols(), k);
    ASSERT_EQUALS_I(res.get_rows(), d * w * h);

    for(unsigned long ex = 0; ex < k; ++ex) {
      for(unsigned long i = 0; i < d * w * h; ++i) {
        ASSERT_EQUALS(res[i][ex], (*Y)[i][ex]);
      }
    }
  }

  void foldTest() {
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> res2 = AGH_NN::fold(*Y, d, w, h);

    ASSERT_EQUALS_I(res2.size(), k);
    ASSERT_EQUALS_I(res2[0].size(), d);
    ASSERT_EQUALS_I(res2[0][0].get_cols(), h);
    ASSERT_EQUALS_I(res2[0][0].get_rows(), w);

    for(unsigned long ex = 0; ex < k; ++ex) {
      for(unsigned long dim = 0; dim < d; ++dim) {
        for(unsigned long y = 0; y < h; ++y) {
          for(unsigned long x = 0; x < w; ++x) {
            ASSERT_EQUALS(res2[ex][dim][y][x], (*X)[ex][dim][y][x]);
          }
        }
      }
    }
  }

  void cleanup() {
    delete X;
    delete Y;
  }

public:
  static void test() {
    LayerTest layerTest;
    layerTest.unfoldTest();
    layerTest.foldTest();

    layerTest.cleanup();
  }
};

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYERTEST_H
