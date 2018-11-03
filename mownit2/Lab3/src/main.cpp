#include <iostream>
#include <cassert>

#include "Matrix2D.h"

using namespace AGH;

int main() 
{
  // initialize matrices using init value
  Matrix2D<double> mat1(3, 3, 1.2);
  Matrix2D<double> mat2(3, 3, 2.8);

  std::vector<std::vector<double>> init { { 1.0, 0.0, 0.0 },
                                          { 0.0, 2.0, 0.0 },
                                          { 0.0, 0.0, 1.0 } };
  Matrix2D<double> m(init);

  std::cout << m.isSymmetrical() << std::endl;
  Matrix2D<double> mat3 = mat1 + mat2;
  std::cout << mat3;
  std::cout << mat3 * m;

  // initialize matrix using specified values
  init = { { 5.0, 3.0, 2.0 },
           { 1.0, 2.0, 0.0 },
           { 3.0, 0.0, 4.0 } };

  Matrix2D<double> mat4(init);
  std::cout << m.determinant() << std::endl;
  std::cout << mat4.doolittleDecomposition().first << std::endl;
  std::cout << mat4.doolittleDecomposition().second << std::endl;

  std::vector<std::vector<double>> init2 = { {  4.0, 12.0, -16.0 },
                                             { 12.0, 37.0, -43.0 },
                                             { -16.0, -43.0, 98.0 }};

  Matrix2D<double> solski(init2);
  std::cout << solski.choleskyDecomposition() << std::endl;

  std::vector<std::vector<double>> init3 = {{3.0, 2.0,-4.0, 3.0},
                                            {2.0, 3.0, 3.0, 15.0},
                                            {5.0, -3, 1.0, 14.0}};


  Matrix2D<double> gausjusz(init3);
  Matrix2D<double> result = gausjusz.gaussianElimination();
  std::cout << result << std::endl;
  assert(result[0][0] - 3.0 < 0.0001);
  assert(result[1][0] - 1.0 < 0.0001);
  assert(result[2][0] - 2.0 < 0.0001);
  return 0;
}