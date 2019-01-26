//
// Created by joseph on 19.11.18.
//

#ifndef LAB5_DATAPROVIDER_H
#define LAB5_DATAPROVIDER_H

#include <vector>
#include "Matrix2D.h"

using namespace AGH_NN;

void setABX(std::vector<Matrix2D<double>>& A, std::vector<Matrix2D<double>>& B,
        std::vector<Matrix2D<double>>& X)
{
  //1
  A.emplace_back(AGH_NN::Matrix2D<double>(4, 4, 0.0));
  A[0][0][0] =  4.0; A[0][0][1] = -1.0; A[0][0][2] = -0.2; A[0][0][3] =  2.0;
  A[0][1][0] = -1.0; A[0][1][1] =  5.0; A[0][1][2] =  0.0; A[0][1][3] = -2.0;
  A[0][2][0] =  0.2; A[0][2][1] =  1.0; A[0][2][2] = 10.0; A[0][2][3] = -1.0;
  A[0][3][0] =  0.0; A[0][3][1] = -2.0; A[0][3][2] = -1.0; A[0][3][3] =  4.0;

  B.emplace_back(AGH_NN::Matrix2D<double>(4, 1, 0.0));
  B[0][0][0] = 21.6;
  B[0][1][0] = 36;
  B[0][2][0] = -20.6;
  B[0][3][0] = -11;

  X.emplace_back(AGH_NN::Matrix2D<double>(4, 1, 0.0));
  X[0][0][0] = 7;
  X[0][1][0] = 9;
  X[0][2][0] = -3;
  X[0][3][0] = 1;

  //2
  A.emplace_back(AGH_NN::Matrix2D<double>(4, 4, 0.0));
  A[1][0][0] = 10.0; A[1][0][1] = -1.0; A[1][0][2] =  2.0; A[1][0][3] =  0.0;
  A[1][1][0] = -1.0; A[1][1][1] = 11.0; A[1][1][2] = -1.0; A[1][1][3] =  3.0;
  A[1][2][0] =  2.0; A[1][2][1] = -1.0; A[1][2][2] = 10.0; A[1][2][3] = -1.0;
  A[1][3][0] =  0.0; A[1][3][1] =  3.0; A[1][3][2] = -1.0; A[1][3][3] =  8.0;

  B.emplace_back(AGH_NN::Matrix2D<double>(4, 1, 0.0));
  B[1][0][0] =   6.0;
  B[1][1][0] =  25.0;
  B[1][2][0] = -11.0;
  B[1][3][0] =  15.0;

  X.emplace_back(AGH_NN::Matrix2D<double>(4, 1, 0.0));
  X[1][0][0] =  1.0;
  X[1][1][0] =  2.0;
  X[1][2][0] = -1.0;
  X[1][3][0] =  1.0;

  //3
  A.emplace_back(AGH_NN::Matrix2D<double>(3, 3, 0.0));
  A[2][0][0] =  1.0; A[2][0][1] =  0.0; A[2][0][2] =  0.0;
  A[2][1][0] =  0.0; A[2][1][1] =  1.0; A[2][1][2] =  0.0;
  A[2][2][0] =  0.0; A[2][2][1] =  0.0; A[2][2][2] =  1.0;

  B.emplace_back(AGH_NN::Matrix2D<double>(3, 1, 0.0));
  B[2][0][0] =   1.0;
  B[2][1][0] =   1.0;
  B[2][2][0] =   1.0;

  X.emplace_back(AGH_NN::Matrix2D<double>(3, 1, 0.0));
  X[2][0][0] =  1.0;
  X[2][1][0] =  1.0;
  X[2][2][0] =  1.0;

  //4
  A.emplace_back(AGH_NN::Matrix2D<double>(3, 3, 0.0));
  A[3][0][0] = 1.0; A[3][0][1] = 0.0; A[3][0][2] = 0.0;
  A[3][1][0] = 0.0; A[3][1][1] = 1.0; A[3][1][2] = 0.0;
  A[3][2][0] = 0.0; A[3][2][1] = 0.0; A[3][2][2] = 1.0;

  B.emplace_back(AGH_NN::Matrix2D<double>(3, 1, 0.0));
  B[3][0][0] =   0.0;
  B[3][1][0] =   0.0;
  B[3][2][0] =   0.0;

  X.emplace_back(AGH_NN::Matrix2D<double>(3, 1, 0.0));
  X[3][0][0] =  0.0;
  X[3][1][0] =  0.0;
  X[3][2][0] =  0.0;

  //5
  A.emplace_back(AGH_NN::Matrix2D<double>(5, 5, 1.0));
  A[4][0][0] = 990; A[4][0][1] =  71; A[4][0][2] = 678; A[4][0][3] = 443; A[4][0][4] =  67;
  A[4][1][0] =  45; A[4][1][1] = 867; A[4][1][2] =   1; A[4][1][3] = -23; A[4][1][4] =  42;
  A[4][2][0] = 213; A[4][2][1] = 123; A[4][2][2] =7484; A[4][2][3] =   0; A[4][2][4] =   9;
  A[4][3][0] =  12; A[4][3][1] = 344; A[4][3][2] =-123; A[4][3][3] = 789; A[4][3][4] = -45;
  A[4][4][0] =  81; A[4][4][1] =  35; A[4][4][2] =  61; A[4][4][3] =  80; A[4][4][4] = 500;

  B.emplace_back(AGH_NN::Matrix2D<double>(5, 1, 1.0));
  B[4][0][0] =  4899;
  B[4][1][0] =    821;
  B[4][2][0] = -477055;
  B[4][3][0] =  19692 ;
  B[4][4][0] =  -9280;

  X.emplace_back(AGH_NN::Matrix2D<double>(5, 1, 0.0));
  X[4][0][0] =   45;
  X[4][1][0] =    0;
  X[4][2][0] =  -65;
  X[4][3][0] =   13;
  X[4][4][0] =  -20;
}

#endif //LAB5_DATAPROVIDER_H