//
// Created by joseph on 17.01.19.
//
#include <cmath>
#include "SoftMaxLayer.h"

AGH_NN::SoftMaxLayer::~SoftMaxLayer() {
  delete A;
  A = nullptr;
}

void AGH_NN::SoftMaxLayer::forward_propagation(AGH_NN::Matrix2D<double> &X) {
  lastX = &X;
  if(A != nullptr && (A->get_cols() != X.get_cols() || A->get_rows() != X.get_rows())) {
    delete A;
    A = new Matrix2D<double>(X.get_rows(), X.get_cols(), 0.0);
  } else if(A == nullptr){
    A = new Matrix2D<double>(X.get_rows(), X.get_cols(), 0.0);
  }

  for(unsigned long ex = 0; ex < A->get_cols(); ++ex) {
    double sum = 0.0;
    for (unsigned long ft = 0; ft < A->get_rows(); ++ft) {
      sum += std::exp(X[ft][ex]);
    }
    for (unsigned long ft = 0; ft < A->get_rows(); ++ft) {
      (*A)[ft][ex] = std::exp(X[ft][ex]) / sum;
    }
  }
}

AGH_NN::Matrix2D<double> AGH_NN::SoftMaxLayer::backward_propagation(AGH_NN::Matrix2D<double> &prevError) {
  AGH_NN::Matrix2D<double> ret(lastX->get_rows(), lastX->get_cols(), 0.0);
  for(unsigned long ex = 0; ex < ret.get_cols(); ++ex) {
    for(unsigned long i = 0; i < ret.get_rows(); ++i) {
      for(unsigned long j = 0; j < ret.get_rows(); ++j) {
        if(i == j) {
          ret[i][ex] += (*A)[i][ex] * (1 - (*A)[j][ex]) * prevError[ex][i];
        } else {
          ret[i][ex] -= (*A)[j][ex] * (*A)[i][ex] * prevError[ex][j];
        }
      }
    }
  }
  return ret;
}