#include <iostream>

#include "Integrator.h"

double dy(double y, double x) {
  return 2.0 * x;
}

int main() {
  std::vector<double> out = Integrator::solveEuler(dy, 0.0, 0.0, 0.01, 500);
  for(unsigned long i = 0; i < out.size(); ++i) {
    std::cout << out[i] << std::endl;
  }
  return 0;
}