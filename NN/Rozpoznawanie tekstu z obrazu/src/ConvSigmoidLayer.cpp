//
// Created by joseph on 06.12.18.
//

#include "ConvSigmoidLayer.h"

AGH_NN::ConvSigmoidLayer::ConvSigmoidLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h,
                                           unsigned long _m, unsigned long _wf, unsigned long _hf, unsigned long _s,
                                           unsigned long _p) : k(_k), d(_d), w(_w), h(_h), m(_m), wf(_wf), hf(_hf),
                                                                s(_s), p(_p) {
  if((w + 2 * p - wf) % s != 0 || (h + 2 * p - hf) % s != 0) {
    std::cerr << "Cannot compute convolution with chosen stride!" << std::endl;
    throw -1;
  }
  filters.resize(m);
  for(unsigned long i = 0; i < m; ++i)
    filters[i].resize(d, Matrix2D<double>(hf, wf, 0.0));

  A.resize(k);
  for(unsigned long i = 0; i < k; ++i)
    A[i].resize(m, Matrix2D<double>(getSize(h, hf, s, p), getSize(w, wf, s, p), 0.0));
  bias = Matrix2D<double>(m, 1, 0.0);

  dX = nullptr;
}

AGH_NN::ConvSigmoidLayer::~ConvSigmoidLayer() {
  if(dX != nullptr) {
    delete dX;
    dX = nullptr;
  }
}

double AGH_NN::ConvSigmoidLayer::getValue(unsigned long example, unsigned long cornerX,
    unsigned long cornerY, unsigned long filterNo, std::vector<std::vector<AGH_NN::Matrix2D<double>>>& X) {
  double sum = 0;
  long paddedStartingPosX = cornerX - p;
  long paddedStartingPosY = cornerY - p;
  for(long x = paddedStartingPosX; x < paddedStartingPosX + static_cast<long>(wf); ++x) {
    for(long y = paddedStartingPosY; y < paddedStartingPosY + static_cast<long>(hf); ++y) {
      for (unsigned long depth = 0; depth < d; ++depth) {
        long filterPosX = x - paddedStartingPosX;
        long filterPosY = y - paddedStartingPosY;

        double xVal;
        if (x < 0 || y < 0 || x > w - 1 || y > h - 1)
          xVal = 0.0;
        else
          xVal = X[example][depth][y][x];
        sum += filters[filterNo][depth][filterPosY][filterPosX] * xVal;
      }
    }
  }
  return sum;
}


void AGH_NN::ConvSigmoidLayer::forward_propagation(std::vector<std::vector<AGH_NN::Matrix2D<double>>>& X) {

  lastX = &X;
  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long f_no = 0; f_no < m; ++f_no) {
      for (unsigned long y = 0; y + hf <= h + 2 * p; y += s) {
        for (unsigned long x = 0; x + wf < w + 2 * p; x += s) {
          A[ex][f_no][y][x] = getValue(ex, x, y, f_no, X) + bias[f_no][0];
        }
      }
      //A[ex][f_no] = sigmoid2D(A[ex][f_no]);
    }
  }
}

std::vector<std::vector<AGH_NN::Matrix2D<double>>> & AGH_NN::ConvSigmoidLayer::backward_propagation(
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> &prevError) {

  //zero out dw
  //for(unsigned long f_no = 0; f_no < m; ++f_no) {
  //  for (unsigned long dim = 0; dim < d; ++dim) {
      for (unsigned long y = 0; y < hf; y ++) {
        for (unsigned long x = 0; x < wf; x ++) {
          dw[0][0][y][x] = 0.0;
        }
      }
  //  }
  //}

  if(dX != nullptr) {
    delete dX;
  }

  dX = new std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(h, w, 0.0)));


  unsigned long f_no = 0;
  unsigned long dim = 0;
  unsigned long ex = 0;
  unsigned long result_w = getSize(w, wf, s, p);
  unsigned long result_h = getSize(h, hf, s, p);
  //for(unsigned long ex = 0; ex < k; ++ex) {
  //  for(unsigned long f_no = 0; f_no < m; ++f_no) {
  //    for(unsigned long dim = 0; dim < d; ++dim) {
        for (unsigned long yf = 0; yf < hf; yf++) {
          for (unsigned long xf = 0; xf < wf; xf++) {
            for(unsigned long y = yf; y < h - (hf - yf - 1); ++y) {
              for(unsigned long x = xf; x < w - (wf - xf - 1); ++x) {
                long dif_x = x - xf;
                long dif_y = y - yf;
                if(dif_x >= 0 && dif_x < result_w && dif_y >= 0 && dif_y < result_h)
                  dw[f_no][dim][yf][xf] += (*lastX)[ex][dim][y][x] * prevError[ex][f_no][dif_y][dif_x];
              }
            }
          }
        }
  //    }
  //  }
  //}

}

void AGH_NN::ConvSigmoidLayer::update_parameters(double learning_rate) {
  for(unsigned long f_no = 0; f_no < m; ++f_no) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      filters[f_no][dim] -= dw[f_no][dim] * learning_rate;
    }
  }
}

unsigned long AGH_NN::ConvSigmoidLayer::getSize(unsigned long size, unsigned long filterSize, unsigned long stride,
                                                unsigned long padding) {
  return (size + 2 * padding - filterSize) / stride + 1;
}