#include <iostream>
#include <gsl/gsl_ieee_utils.h>

int main() {
    float a = 10.0f;
    do {
        a /= 2.0f;
        gsl_ieee_printf_float(&a);
        std::cout << std::endl;
    } while(a != 0.0f);

}