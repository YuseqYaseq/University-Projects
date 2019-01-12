//
// Created by joseph on 06.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ACTUALCONVSIGMOIDLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ACTUALCONVSIGMOIDLAYER_H

#include "ConvSigmoidLayer.h"
namespace AGH_NN {
  class ActualConvSigmoidLayer {
  public:

    void forward_propagation(std::vector<std::vector<Matrix2D<double>>> &X);
    std::vector<std::vector<Matrix2D<double>>> &
    backward_propagation(std::vector<std::vector<Matrix2D<double>>> &prevError);
    void update_parameters(double learning_rate);

    ActualConvSigmoidLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h, unsigned long _m,
                           unsigned long _wf, unsigned long _hf, unsigned long _s, unsigned long _p);
    ActualConvSigmoidLayer(const char* fileName);
    void save_to_file(const char* fileName);

    ~ActualConvSigmoidLayer();
    ConvSigmoidLayer* layer = nullptr;

  private:
    unsigned long k;
    unsigned long m;
    unsigned long d;
    unsigned long h;
    unsigned long w;
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ACTUALCONVSIGMOIDLAYER_H
