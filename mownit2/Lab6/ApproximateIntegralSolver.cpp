//
// Created by joseph on 03.12.18.
//

#include <random>
#include "ApproximateIntegralSolver.h"

double ApproximateIntegralSolver::rectanglesMethod(double from, double to, double n,
                                                   const std::function<double(double)>& function) {
  double sum = 0.0;
  for(int i = 1; i <= n; ++i) {
    sum += function(from + i * (to - from) / n);
  }
  return (to - from) * sum / n;
}

double ApproximateIntegralSolver::trapezesMethod(double from, double to, double n,
                                                 const std::function<double(double)>& function) {
  double sum = 0.0;
  double h = (to - from) / n;
  for(int i = 0; i < n; ++i) {
    sum += (function(from + i * h) + function(from + (i + 1.0) * h)) / 2.0;
  }
  return h * sum;
}

double ApproximateIntegralSolver::SimpsonsMethod(double from, double to, double n,
                                                 const std::function<double(double)>& function) {
  double sum = function(from) + function(to);
  double h = (to - from) / n;
  double current_pos = from + h;
  double t = current_pos - h / 2.0;
  for(int i = 1; i < n; ++i) {
    sum += 2 * function(current_pos) + 4 * function(t);
    current_pos += h;
    t += h;
  }
  sum += 4 * function(t);
  return (to - from) * sum / (6 * n);
}

double ApproximateIntegralSolver::approximatePi(unsigned long iters) {
  double radius = 1.0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, radius);
  unsigned long noHits = 0;
  for(unsigned long i = 0; i < iters; ++i) {
    double x = dis(gen);
    double y = dis(gen);
    if(sqrt(x * x + y * y) < radius) noHits++;
  }
  return 4.0 * static_cast<double>(noHits) / static_cast<double>(iters);
}

double ApproximateIntegralSolver::basicMonteCarloMethod(double from, double to, unsigned long n,
                                                        const std::function<double(double)> &fun) {
  double sum = 0.0;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(from, to);
  for(unsigned long i = 0; i < n; ++i) {
    sum += fun(dis(gen));
  }
  return (to - from) * sum / n;
}