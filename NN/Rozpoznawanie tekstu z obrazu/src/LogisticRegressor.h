//
// Created by joseph on 01.12.18.
//

#ifndef ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_COSTLAYER_H
#define ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_COSTLAYER_H

#include "Layer.h"
namespace AGH_NN
{
  class LogisticRegressor
  {
  public:
    static double calculateCost(Matrix2D<double>& A, Matrix2D<double>& Y);
    static Matrix2D<double> calculateBackPropDerivatives(Matrix2D<double>& A, Matrix2D<double>& Y);
  };
}

#endif //ROZPOZNAWANIE_TEKSTU_Z_OBRAZU_COSTLAYER_H
