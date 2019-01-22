//
// Created by joseph on 17.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SOFTMAXLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SOFTMAXLAYER_H

#include "Matrix2D.h"

namespace AGH_NN {
  class SoftMaxLayer {
  public:
    //y - liczba featurów
    //x - liczba przykładów
    void forward_propagation(Matrix2D<double>& X);
    Matrix2D<double> backward_propagation(Matrix2D<double>& prevError);

    Matrix2D<double>& getA() {return *A;}

    Matrix2D<double>* A = nullptr;
    Matrix2D<double>* lastX = nullptr;

    SoftMaxLayer() = default;
    ~SoftMaxLayer();
    //SoftMaxLayer(unsigned long inputSize);
    //SigmoidLayer(Matrix2D<double> _weights, Matrix2D<double> _bias) : Layer(_weights, _bias){}
    //SigmoidLayer(unsigned long m, unsigned long n) : Layer(m, n){}
    //SigmoidLayer(const char* pathName) : Layer(pathName) {}
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_SOFTMAXLAYER_H
