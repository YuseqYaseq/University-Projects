//
// Created by joseph on 03.12.18.
//

#ifndef LAB6_APPROXIMATEINTEGRALSOLVER_H
#define LAB6_APPROXIMATEINTEGRALSOLVER_H


#include <functional>

class ApproximateIntegralSolver {
public:
  static double rectanglesMethod(double from, double to, double n, const std::function<double(double)>& function);
  static double trapezesMethod(double from, double to, double n, const std::function<double(double)>& function);
  static double SimpsonsMethod(double from, double to, double n, const std::function<double(double)>& function);

  static double approximatePi(unsigned long iters);
  static double basicMonteCarloMethod(double from, double to, unsigned long n, const std::function<double(double)>& fun);
};


#endif //LAB6_APPROXIMATEINTEGRALSOLVER_H
