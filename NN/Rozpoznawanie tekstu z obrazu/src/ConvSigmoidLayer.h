//
// Created by joseph on 06.12.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYER_H

#include <vector>
#include "Matrix2D.h"

class ActualConvSigmoidLayerTest;
class ConvSigmoidLayerTest;

namespace AGH_NN {
  class ConvSigmoidLayer {
  public:

    void forward_propagation(std::vector<std::vector<Matrix2D<double>>>& X);
    std::vector<std::vector<Matrix2D<double>>>&
        backward_propagation(std::vector<std::vector<Matrix2D<double>>>& prevError);
    void update_parameters(double learning_rate);


    ConvSigmoidLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h, unsigned long _m,
        unsigned long _wf, unsigned long _hf, unsigned long _s, unsigned long _p);

    //load from file
    explicit ConvSigmoidLayer(const char* pathName);
    void save_to_file(const char* pathName);

    ~ConvSigmoidLayer();

    void initialize_gaussian();
    void initialize_gaussian(double median, double variance, unsigned long seed);

    std::vector<std::vector<Matrix2D<double>>>& getA(){return A;}
    std::vector<std::vector<Matrix2D<double>>>& getW(){return filters;}
    Matrix2D<double>&                           getB(){return bias;}
    std::vector<std::vector<Matrix2D<double>>>& getDW(){return dw;}
    Matrix2D<double>&                           getDB(){return db;}
    std::vector<std::vector<Matrix2D<double>>>* getLastX() {return lastX;}
  //private:

    //number of examples
    unsigned long k;

    //input depth
    unsigned long d;

    //input width
    unsigned long w;

    //input height
    unsigned long h;

    //number of filters
    unsigned long m;

    //filter width
    unsigned long wf;

    //filter height
    unsigned long hf;

    //stride
    unsigned long s;

    //padding
    unsigned long p;

    //filters[m][d][wf][hf]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> filters;

    //results[k x m x getSize(w, wf, s, p) x getSize(h, hf, s, p)
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> A;

    //bias[1 x m]
    AGH_NN::Matrix2D<double>  bias;

    //bias derivatives[same as bias]
    AGH_NN::Matrix2D<double> db;

    //filter derivatives[same as filters]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> dw;

    //last X used[k x d x w x h]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>>* lastX;

    //dX [k x d x w x h]
    std::vector<std::vector<AGH_NN::Matrix2D<double>>>* dX;

    unsigned long getSize(unsigned long size, unsigned long filterSize,
        unsigned long stride, unsigned long padding);

    double getValue(unsigned long example, unsigned long cornerX,
        unsigned long cornerY, unsigned long filterNo, std::vector<std::vector<AGH_NN::Matrix2D<double>>>& X);

    friend ConvSigmoidLayerTest;
    friend ActualConvSigmoidLayerTest;
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_CONVSIGMOIDLAYER_H
