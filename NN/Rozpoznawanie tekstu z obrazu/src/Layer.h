//
// Created by joseph on 17.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYER_H

#include <vector>
#include "Matrix2D.h"

namespace AGH_NN
{
  class Layer {
  public:
    //Calculate error as last
    virtual void forward_propagation(Matrix2D<double>& X) = 0;
    virtual Matrix2D<double> backward_propagation(const Matrix2D<double>& prevError) = 0;
    virtual void update_parameters(double learning_rate)
    {
      weights -= dw * learning_rate;
      bias -= db * learning_rate;
    }

    virtual void initialize_gaussian();
    virtual void initialize_gaussian(double median, double variance, unsigned long seed);

    explicit Layer(const char* pathName);

    void save_to_file(const char* pathName);

    Layer(Matrix2D<double> _weights, Matrix2D<double> _bias) :
              weights(_weights), bias(_bias){}

    virtual ~Layer() = default;
    //m = current layer weights
    //n = previous layer
    Layer(unsigned long currSize, unsigned long prevSize);
    Layer() = default;

    Matrix2D<double>& getA(){return activatedWeights;}
    Matrix2D<double>& getW(){return weights;}
    Matrix2D<double>& getB(){return bias;}
    Matrix2D<double>& getDW(){return dw;}
    Matrix2D<double>& getDB(){return db;}
    Matrix2D<double>& getLastX() {return *lastX;}

  protected:

    //matrix m x n
    Matrix2D<double> activatedWeights;

    //matrix m x n
    Matrix2D<double> weights;

    //matrix n x 1
    Matrix2D<double> bias;

    Matrix2D<double> dw;
    Matrix2D<double> db;

    //last X used
    Matrix2D<double>* lastX;
  };

  //unfolds convolution result to a single 2d matrix [examples x neurons]
  Matrix2D<double> unfold(std::vector<std::vector<Matrix2D<double>>> X);

  //folds [examples x neurons] to conv [examples x dimensions x w x h]
  std::vector<std::vector<Matrix2D<double>>> fold(Matrix2D<double> X,
      unsigned long d, unsigned long w, unsigned long h);

  //saves matrix to file
  void save_to(std::vector<std::vector<Matrix2D<double>>> matrix,
      const char* fileName, std::vector<std::string>& pic_names);
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_LAYER_H
