#include <iostream>
#include <fstream>

int main() {
    std::fstream file("ex1_results.txt", std::ios_base::out);
    if(!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return -1;
    }

    float float32 = 1.0f/3.0f;
    double float64 = 1.0/3.0;
    double float64_cast = static_cast<double>(1.0f/3.0f);
    file.precision(100);
    file << "float32 = " << float32 << std::endl;
    file << "float64 = " << float64 << std::endl;
    file << "cast float64 = " << float64_cast << std::endl;
    file.close();
    return 0;
}