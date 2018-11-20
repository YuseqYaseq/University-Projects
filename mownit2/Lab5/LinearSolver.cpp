//
// Created by joseph on 14.11.18.
//

#include <fstream>
#include "LinearSolver.h"

using namespace AGH_NN;

template <typename T>
Matrix2D<T> LinearSolver<T>::solveJacoby(Matrix2D<T> &A, Matrix2D<T> &b, int iters, Matrix2D<T>& solution,
        bool saveIterDiffToFile, std::fstream* file)
{
  unsigned long size = b.get_rows();
  Matrix2D<T> x = Matrix2D<T>(b.get_rows(), 1, static_cast<T>(0));
  Matrix2D<T> x_prev = x;
  for(int n = 0; n < iters; ++n)
  {
    for(int i = 0; i < size; ++i)
    {
      T sum = 0;
      for(int j = 0; j < size; ++j)
      {
        if(j != i)
        {
          sum += A[i][j] * x_prev[j][0];
        }
      }
      x[i][0] = (b[i][0] - sum) / A[i][i];
    }
    if(saveIterDiffToFile)
    {
      (*file) << n << " " << fabs(avg(x - solution)) << std::endl;
    }
    x_prev = x;
  }

  return x;
}

template <typename T>
Matrix2D<T> LinearSolver<T>::solveGaussSeidel(Matrix2D<T> &A, Matrix2D<T> &b, int iters, Matrix2D<T> &solution,
                                              bool saveIterDiffToFile, std::fstream *file)
{
  unsigned long size = b.get_rows();
  Matrix2D<T> x = Matrix2D<T>(b.get_rows(), 1, static_cast<T>(0));
  Matrix2D<T> x_prev = x;
  for(int n = 0; n < iters; ++n)
  {
    for(int i = 0; i < size; ++i)
    {
      T sum = 0;
      for(int j = 0; j < size; ++j)
      {
        if(j > i)
        {
          sum += A[i][j] * x_prev[j][0];
        }
        if(j < i)
        {
          sum += A[i][j] * x[j][0];
        }
      }
      x[i][0] = (b[i][0] - sum) / A[i][i];
    }
    if(saveIterDiffToFile)
    {
      (*file) << n << " " << fabs(avg(x - solution)) << std::endl;
    }
    x_prev = x;
  }

  return x;
}

template <typename T>
Matrix2D<T> LinearSolver<T>::solveSOR(Matrix2D<T> &A, Matrix2D<T> &b, int iters, Matrix2D<T> &solution,
                                      bool saveIterDiffToFile, std::fstream *file)
{
  double omega = 1.2;
  unsigned long size = b.get_rows();
  Matrix2D<T> x = Matrix2D<T>(b.get_rows(), 1, static_cast<T>(0));
  Matrix2D<T> x_prev = x;
  for(int n = 0; n < iters; ++n)
  {
    for(int i = 0; i < size; ++i)
    {
      T sum = 0;
      for(int j = 0; j < size; ++j)
      {
        if(j > i)
        {
          sum += A[i][j] * x_prev[j][0];
        }
        if(j < i)
        {
          sum += A[i][j] * x[j][0];
        }
      }
      x[i][0] = (1 - omega) * x_prev[i][0] + omega * (b[i][0] - sum) / A[i][i];
    }
    if(saveIterDiffToFile)
    {
      (*file) << n << " " << fabs(avg(x - solution)) << std::endl;
    }
    x_prev = x;
  }

  return x;
}