#include <iostream>

#include "Matrix2D.h"

int main() {
  double** d = new double*[3];
  for(int i = 0; i < 3; ++i)
  {
    d[i] = new double[3];
  }
  AGH_NN::Matrix2D<double> m(3, 3, d);
  m[1][1] = 2;
  std::cout << m << std::endl;
  return 0;
}