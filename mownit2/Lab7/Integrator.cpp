//
// Created by joseph on 12.12.18.
//

#include <iostream>
#include "Integrator.h"

std::vector<double> Integrator::solveEuler(std::function<double(double /*y*/, double /*t*/)> dy, double t0,
                                              double y0, double h, unsigned long iters) {
  std::vector<double> out(iters);
  for(unsigned long i = 0; i < iters; ++i) {
    out[i] = y0 + dy(y0, t0) * h;
    t0 += h;
    y0 = out[i];
  }
  return out;
}