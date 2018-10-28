#include <iostream>
#include <cmath>

const int ITERS = 10;

int factorial(int n) {
    int prod = 1;
    for(int i = 2; i <= n; ++i) {
        prod *= i;
    }
    return prod;
}

double unstable_algorithm(double x) {
    double sum = x;
    for(int i = 1; i < ITERS; ++i) {
        if(i % 2) {
            sum -= pow(x, 2*i+1) / factorial(2*i + 1);
        } else {
            sum += pow(x, 2*i+1) / factorial(2*i + 1);
        }
    }
    return sum;
}

double stable_algorithm(double x) {
    return sin(x);
}

void print_algorithms(double x1) {
    std::cout << "f(" << x1 << ") = " << unstable_algorithm(x1) << "\t" << stable_algorithm(x1) << std::endl;
}



int main() {
    std::cout.precision(20);
    print_algorithms(0.0);
    print_algorithms(0.1);
    print_algorithms(0.5);
    print_algorithms(1.0);
    print_algorithms(1.5);
    print_algorithms(1.8);
    print_algorithms(1.9);
    print_algorithms(2.0);
    print_algorithms(2.5);
    print_algorithms(3.0);
}