//
// Created by joseph on 12.12.18.
//

#ifndef LAB7_INTEGRATOR_H
#define LAB7_INTEGRATOR_H

#include <functional>
#include <vector>

class Integrator {
public:
  static std::vector<double> solveEuler(std::function<double(double /*y*/, double /*t*/)> dy, double t0,
      double y0, double h, unsigned long iters);

  static std::vector<double> solveBackwardEuler(s)
};


#endif //LAB7_INTEGRATOR_H
