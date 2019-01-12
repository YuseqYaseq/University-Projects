//
// Created by joseph on 17.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H

#include "Matrix2D.h"
#include "Layer.h"

namespace AGH_NN
{
  class SigmoidLayer : public Layer
  {
  public:
    void forward_propagation(Matrix2D<double>& X) override;
    Matrix2D<double> backward_propagation(const Matrix2D<double>& prevError) override;
    void update_parameters(double learning_rate) override;

    SigmoidLayer(Matrix2D<double> _weights, Matrix2D<double> _bias) : Layer(_weights, _bias){}
    SigmoidLayer(unsigned long m, unsigned long n) : Layer(m, n){}
    SigmoidLayer(const char* pathName) : Layer(pathName) {}
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H
