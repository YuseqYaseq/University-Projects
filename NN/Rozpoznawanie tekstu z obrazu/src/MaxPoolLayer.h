//
// Created by joseph on 05.01.19.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYER_H

#include <vector>
#include "Matrix2D.h"

namespace AGH_NN {
  class MaxPoolLayer {
  public:
    void forward_propagation(std::vector<std::vector<Matrix2D<double>>>& X);
    std::vector<std::vector<Matrix2D<double>>>&
    backward_propagation(std::vector<std::vector<Matrix2D<double>>>& prevError);
    void update_parameters(double learning_rate);

    MaxPoolLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h,
        unsigned long _wf, unsigned long _hf);

    //load from file
    explicit MaxPoolLayer(const char* pathName);

    void save_to_file(const char* pathName);
    ~MaxPoolLayer();

    std::vector<std::vector<AGH_NN::Matrix2D<double>>> getA() {return A;}

  private:

    //number of examples
    unsigned long k;

    //input depth
    unsigned long d;

    //input width
    unsigned long w;

    //input height
    unsigned long h;

    //filter width
    unsigned long wf;

    //filter height
    unsigned long hf;

    //results[k x d x w/wf x h/hf]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> A;

    //last X used[k x d x w x h]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>>* lastX;

    //dX [k x d x w x h]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>>* dX;

  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_MAXPOOLLAYER_H
