//
// Created by joseph on 28.10.18.
//

#ifndef LAB2_LINEARREGRESSOR_H
#define LAB2_LINEARREGRESSOR_H

#include <vector>

class LinearRegressor {
public:
    LinearRegressor() {}

    void fit(const std::vector<float>& x, const std::vector<float>& y);
    std::vector<float> predict(const std::vector<float>& x);

    float getA() {return coefficients.first;}
    float getB() {return coefficients.second;}

private:
    std::pair<float, float> coefficients;
};


#endif //LAB2_LINEARREGRESSOR_H
