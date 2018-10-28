//
// Created by joseph on 28.10.18.
//

#include "LinearRegression.h"
#include "LinearRegressor.h"

void LinearRegressor::fit(const std::vector<float>& x, const std::vector<float>& y)
{
    coefficients = linearRegression(x, y);
}

std::vector<float> LinearRegressor::predict(const std::vector<float>& x)
{
    std::vector<float> y(x.size());
    for(int i = 0; i < x.size(); ++i)
    {
        y.push_back(x[i] * coefficients.first + coefficients.second);
    }
    return y;
}