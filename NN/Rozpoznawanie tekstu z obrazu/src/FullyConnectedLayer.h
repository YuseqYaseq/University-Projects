//
// Created by joseph on 17.11.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H

#include "Matrix2D.h"
#include "Layer.h"

namespace AGH_NN
{
  class FullyConnectedLogisticRegressionLayer : public Layer{
  public:
    void forward_propagation(Matrix2D<double> X);
    Matrix2D<double> backward_propagation(Matrix2D<double> prevError);
    double compute_cost(Matrix2D<double> Y);
    void update_parameters(double learning_rate);


  private:
    Matrix2D<double> activatedWeights;
    Matrix2D<double> weights;
    Matrix2D<double> bias;

    Matrix2D<double> dw;
    Matrix2D<double> db;
/*
    //J(A, Y)
    double (*costFunction)(Matrix2D<double>& results, Matrix2D<double>& y);

    //A = sigma(w.D * X + b)
    Matrix2D<double> (*activationFunction)(Matrix2D<double>& weights, Matrix2D<double>& X, double bias);

    //derivative dJ/dw
    Matrix2D<double> (*dw)(Matrix2D<double>& activatedWeights, Matrix2D<double>& X, Matrix2D<double>& Y);

    //derivative dJ/db
    Matrix2D<double> (*db)(Matrix2D<double>& activatedWeights, Matrix2D<double>& X, Matrix2D<double>& Y);
*/
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_NEURALNETWORK_H
