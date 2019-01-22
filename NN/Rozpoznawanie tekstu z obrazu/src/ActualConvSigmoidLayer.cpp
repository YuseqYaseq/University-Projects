//
// Created by joseph on 06.01.19.
//

#include <cmath>
#include "ActualConvSigmoidLayer.h"

void AGH_NN::ActualConvSigmoidLayer::forward_propagation(std::vector<std::vector<AGH_NN::Matrix2D<double>>> &X) {
  k = X.size();
  layer->forward_propagation(X);
  std::vector<std::vector<Matrix2D<double>>> A = layer->getA();
  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      A[ex][dim] = sigmoid2D(A[ex][dim]);
    }
  }
}

std::vector<std::vector<AGH_NN::Matrix2D<double>>> & AGH_NN::ActualConvSigmoidLayer::backward_propagation(
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> &prevError) {

  std::vector<std::vector<AGH_NN::Matrix2D<double>>> error(k,
      std::vector<AGH_NN::Matrix2D<double>>(m, AGH_NN::Matrix2D<double>(h, w, 0.0)));

  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long dim = 0; dim < m; ++dim) {
      for(unsigned long y = 0; y < h; ++y) {
        for(unsigned long x = 0; x < w; ++x) {
          double t = layer->getA()[ex][dim][y][x];
          double dy_dw = (std::exp(-t) / ((std::exp(-t) + 1) * (std::exp(-t) + 1)));
          error[ex][dim][y][x] = dy_dw * prevError[ex][dim][y][x];
        }
      }
    }
  }

  return layer->backward_propagation(error);
}

void AGH_NN::ActualConvSigmoidLayer::update_parameters(double learning_rate) {
  layer->update_parameters(learning_rate);
}

AGH_NN::ActualConvSigmoidLayer::ActualConvSigmoidLayer(unsigned long _k, unsigned long _d, unsigned long _w,
                                                       unsigned long _h, unsigned long _m, unsigned long _wf,
                                                       unsigned long _hf, unsigned long _s, unsigned long _p) {
  layer = new ConvSigmoidLayer(_k, _d, _w, _h, _m, _wf, _hf, _s, _p);
  k = _k;
  m = _m;
  d = _d;
  w = _w;
  h = _h;
}

AGH_NN::ActualConvSigmoidLayer::ActualConvSigmoidLayer(const char *fileName) {
  layer = new ConvSigmoidLayer(fileName);
  k = layer->k;
  m = layer->m;
  d = layer->d;
  w = layer->w;
  h = layer->h;
}

AGH_NN::ActualConvSigmoidLayer::~ActualConvSigmoidLayer() {
  delete layer;
  layer = nullptr;
}