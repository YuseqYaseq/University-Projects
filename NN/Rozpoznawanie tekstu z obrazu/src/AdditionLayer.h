//
// Created by joseph on 28.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYER_H

#include "Layer.h"
namespace AGH_NN
{
  //A = w0x0 + w1x1 + w2x2 + ... + wNxN + b
  class AdditionLayer : public Layer {
  public:

    //X = matrix 1 x n
    void forward_propagation(Matrix2D<double>& X);

    //prevError = matrix 1 x m
    Matrix2D<double>& backward_propagation(Matrix2D<double> prevError);

    void update_parameters(double learning_rate);


    Matrix2D<double>& getRes(){return results;}
    Matrix2D<double>& getW(){return weights;}
    Matrix2D<double>& getB(){return bias;}
    Matrix2D<double>& getDW(){return dw;}
    Matrix2D<double>& getDB(){return db;}
    Matrix2D<double>& getLastX(){return *lastX;}

    AdditionLayer(unsigned long m, unsigned long n);
    AdditionLayer(){}

  private:

    //m - num of this layer's nodes
    //n - num of prev layer's nodes
    //k - num of examples

    //matrix k x m
    Matrix2D<double> results;

    //matrix n x m
    Matrix2D<double> weights;

    //matrix 1 x m
    Matrix2D<double> bias;

    //same as weights
    Matrix2D<double> dw;

    //same as bias
    Matrix2D<double> db;

    //last X used
    //matrix k x n
    Matrix2D<double>* lastX;
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_ADDITIONLAYER_H
