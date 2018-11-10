//
// Created by joseph on 31.10.18.
//

#ifndef LAB4_FOURIERTRANSFORMATOR_H
#define LAB4_FOURIERTRANSFORMATOR_H

#include <vector>
#include <complex>
#include <cmath>

template <typename T>
class FourierTransformator {
public:
    static std::vector<std::complex<T>> DFT(std::vector<std::complex<T>> vals);
    static std::vector<std::complex<T>> FFT(std::vector<std::complex<T>> vals);
};

#include "FourierTransformator.cpp"

#endif //LAB4_FOURIERTRANSFORMATOR_H
