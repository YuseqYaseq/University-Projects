//
// Created by joseph on 18.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYER_H

#include "Layer.h"
namespace AGH_NN {
  class ReLULayer : public Layer
  {
  public:
    void forward_propagation(Matrix2D<double>& X) override;
    Matrix2D<double> backward_propagation(const Matrix2D<double>& prevError) override;
    void update_parameters(double learning_rate) override;

    ReLULayer(Matrix2D<double> _weights, Matrix2D<double> _bias) : Layer(_weights, _bias){}
    ReLULayer(unsigned long m, unsigned long n) : Layer(m, n){}
    ReLULayer(const char* pathName) : Layer(pathName) {}
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_RELULAYER_H
