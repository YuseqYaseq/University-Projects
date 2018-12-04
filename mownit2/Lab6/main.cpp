#include <iostream>
#include <tgmath.h>
#include <fstream>

#include "ApproximateIntegralSolver.h"

const std::string PATH = "results/";
const std::string RECTANGLES_PATH = PATH + "rectangles/";
const std::string TRAPEZES_PATH = PATH + "trapezes/";
const std::string SIMPSONS_PATH = PATH + "simpsons/";
const std::string PI_PATH = PATH + "pi/";
const std::string MONTECARLO_PATH = PATH + "montecarlo/";
const std::string EXTENSION = ".txt";

double x_squared(double x) {
  return x * x;
}

double x_cubed(double x) {
  return x * x * x;
}

double f3(double x) {
  return 3.0 * x * x * x -2.34 * x * x + 18.0 * x + 45.0;
}

double f4(double x) {
  return -2.0 * x * x * x * x * x + 9.21 * x * x * x * x - 3.14 * x * x * x - 12.0 * x * x + 7.2 * x + 15.1;
}

void verify(double from, double to, double n, const std::function<double(double)>& fun,
    double true_val, std::string fileName) {

  std::fstream rectangles(RECTANGLES_PATH + fileName + EXTENSION, std::fstream::out);
  std::fstream trapezes(TRAPEZES_PATH + fileName + EXTENSION, std::fstream::out);
  std::fstream simpsons(SIMPSONS_PATH + fileName + EXTENSION, std::fstream::out);
  std::fstream montecarlo(MONTECARLO_PATH + fileName + EXTENSION, std::fstream::out);
  for(unsigned long i = 10; i <= n; i += 10) {
    rectangles << i << " " << fabs(true_val - ApproximateIntegralSolver::rectanglesMethod(from, to, i, fun)) << std::endl;
    trapezes << i << " " << fabs(true_val - ApproximateIntegralSolver::trapezesMethod(from, to, i, fun)) << std::endl;
    simpsons << i << " " << fabs(true_val - ApproximateIntegralSolver::SimpsonsMethod(from, to, i, fun)) << std::endl;
    montecarlo << i << " " << fabs(true_val - ApproximateIntegralSolver::basicMonteCarloMethod(from, to, i, fun)) << std::endl;
  }
  rectangles.close();
  trapezes.close();
  simpsons.close();
  montecarlo.close();
}

int main() {

  verify(-3.0, 3.0, 1000, x_squared, 18.0, "1");
  verify(-3.0, 3.0, 1000, x_cubed, 0.0, "2");
  verify(-2.6, 14.0, 1000, f3, 29073.9, "3");
  verify(-335.345, 140.82, 1000, f4, 479379987230868.0, "4");

  std::fstream pi(PI_PATH + "1" + EXTENSION, std::fstream::out);
  if(!pi.is_open()) {
    std::cerr << "Failed to open pi results!" << std::endl;
  }
  for(unsigned long i = 10; i < 10000; i += 10) {
    pi << i << " " << (M_PI - ApproximateIntegralSolver::approximatePi(i)) << std::endl;
  }
  pi.close();
  return 0;
}