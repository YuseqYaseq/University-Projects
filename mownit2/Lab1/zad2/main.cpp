#include <iostream>
#include <fstream>

float nextElem(float x) {
    return x*1.0002f + 0.001f;
}

double nextElem(double x) {
    return x*1.0002 + 0.001;
}

int main() {
    std::fstream file("ex2_results.txt", std::ios_base::out);
    if(!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return -1;
    }

    float f  = 0.0001f;
    double d = 0.0001;
    for(int i = 0; i < 10000; ++i) {
        f = nextElem(f);
        d = nextElem(d);
    }
    file.precision(100);
    file << "f = " << f << std::endl;
    file << "d = " << d << std::endl;
    file.close();
    return 0;
}