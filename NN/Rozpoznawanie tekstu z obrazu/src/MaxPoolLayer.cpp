//
// Created by joseph on 05.01.19.
//

#include <cfloat>
#include <fstream>
#include "MaxPoolLayer.h"

AGH_NN::MaxPoolLayer::MaxPoolLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h,
                                   unsigned long _wf, unsigned long _hf) : k(_k), d(_d), w(_w), h(_h), wf(_wf), hf(_hf){
  A = std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(w/wf, h/hf, 0.0)));
  lastX = nullptr;
  dX = nullptr;
}

AGH_NN::MaxPoolLayer::MaxPoolLayer(const char *pathName) {

  std::fstream file(pathName, std::fstream::in);
  if(!file.is_open()) {
    std::cerr << "Failed to load from " << pathName << "!" << std::endl;
    return;
  }
  file >> k >> d >> w >> h >> wf >> hf;
  file.close();

  A = std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(w/wf, h/hf, 0.0)));
  lastX = nullptr;
  dX = nullptr;
}

void AGH_NN::MaxPoolLayer::save_to_file(const char *pathName) {
  std::fstream file(pathName, std::fstream::out);
  if(!file.is_open()) {
    std::cerr << "Failed to load from " << pathName << "!" << std::endl;
    return;
  }
  file << k << " " << d << " " << w << " " << h << " " << wf << " " << hf << std::endl;
  file.close();
}


AGH_NN::MaxPoolLayer::~MaxPoolLayer() {
  delete dX;
  dX = nullptr;
}

void AGH_NN::MaxPoolLayer::forward_propagation(std::vector<std::vector<AGH_NN::Matrix2D<double>>> &X) {
  if(k != X.size()) {
    k = X.size();
    A = std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
        std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(w/wf, h/hf, 0.0)));
  }

  lastX = &X;
  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      for(unsigned long res_x = 0; res_x < w/wf; ++res_x) {
        for(unsigned long res_y = 0; res_y < h/hf; ++res_y) {
          double max = -DBL_MAX;
          for(unsigned long x = res_x * wf; x < (res_x + 1) * wf; ++x) {
            for(unsigned long y = res_y * hf; y < (res_y + 1) * hf; ++y) {
              if(X[ex][dim][y][x] > max) {
                max = X[ex][dim][y][x];
              }
            }
          }
          A[ex][dim][res_y][res_x] = max;
        }
      }
    }
  }
}

std::vector<std::vector<AGH_NN::Matrix2D<double>>> & AGH_NN::MaxPoolLayer::backward_propagation(
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> &prevError) {

  delete dX;
  dX = new std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(h, w, 0.0)));

  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      for(unsigned long res_x = 0; res_x < w/wf; ++res_x) {
        for(unsigned long res_y = 0; res_y < h/hf; ++res_y) {
          double max = -DBL_MAX;
          unsigned long result_pos_x = UINT32_MAX;
          unsigned long result_pos_y = UINT32_MAX;
          for(unsigned long x = res_x * wf; x < (res_x + 1) * wf; ++x) {
            for(unsigned long y = res_y * hf; y < (res_y + 1) * hf; ++y) {
              if((*lastX)[ex][dim][y][x] > max) {
                max = (*lastX)[ex][dim][y][x];
                result_pos_x = x;
                result_pos_y = y;
              }
            }
          }
          (*dX)[ex][dim][result_pos_y][result_pos_x] = prevError[ex][dim][res_y][res_x];
        }
      }
    }
  }

  return *dX;
}

void AGH_NN::MaxPoolLayer::update_parameters(double learning_rate) {

}