//
// Created by joseph on 14.11.18.
//

#ifndef LAB5_LINEARSOLVER_H
#define LAB5_LINEARSOLVER_H

#include "Matrix2D.h"

using namespace AGH_NN;

template<typename T>
class LinearSolver {
public:
  //Ax = b
  //returns x
  Matrix2D<T> solveJacoby(Matrix2D<T>& A, Matrix2D<T>& b, int iters, Matrix2D<T>& solution,
          bool saveIterDiffToFile = false, std::fstream* file = nullptr);

  Matrix2D<T> solveGaussSeidel(Matrix2D<T>& A, Matrix2D<T>& b, int iters, Matrix2D<T>& solution,
          bool saveIterDiffToFile = false, std::fstream* file = nullptr);

  Matrix2D<T> solveSOR(Matrix2D<T>& A, Matrix2D<T>& b, int iters, Matrix2D<T>& solution,
          bool saveIterDiffToFile = false, std::fstream* file = nullptr);
private:
};

#include "LinearSolver.cpp"

#endif //LAB5_LINEARSOLVER_H
