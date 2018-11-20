#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "Matrix2D.h"
#include "LinearSolver.h"
#include "DataProvider.h"

void testImpl(std::string fileName, AGH_NN::Matrix2D<double> A, AGH_NN::Matrix2D<double> B,
              AGH_NN::Matrix2D<double> X, int which)
{
  LinearSolver<double> solver;
  std::fstream file(fileName, std::fstream::out);
  if(!file.is_open())
  {
    std::cerr << "Can't open file!" << std::endl;
  }
  switch(which)
  {
    case 0: solver.solveJacoby(A, B, 16, X, true, &file); break;
    case 1: solver.solveGaussSeidel(A, B, 16, X, true, &file); break;
    case 2: solver.solveSOR(A, B, 16, X, true, &file); break;
  }
  file.close();
}

int main() {
  std::vector<AGH_NN::Matrix2D<double>> A;
  std::vector<AGH_NN::Matrix2D<double>> B;
  std::vector<AGH_NN::Matrix2D<double>> X;

  setABX(A, B, X);

  for(unsigned long i = 0; i < A.size(); ++i)
  {
    std::string fileName0 = "../results/gauss/" + std::to_string(i);
    std::string fileName1 = "../results/jacob/" + std::to_string(i);
    std::string fileName2 = "../results/sor/"   + std::to_string(i);
    testImpl(fileName0, A[i], B[i], X[i], 0);
    testImpl(fileName1, A[i], B[i], X[i], 1);
    testImpl(fileName2, A[i], B[i], X[i], 2);
  }

  return 0;
}