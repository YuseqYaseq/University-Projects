//
// Created by joseph on 28.10.18.
//

#include "LinearRegression.h"

float mean(PointsList1D x)
{
    float mean = 0.0f;
    unsigned long size = x.size();
    for(int i = 0; i < size; ++i)
    {
        mean += x[i];
    }
    mean /= size;
    return mean;
}

float rmse(PointsList1D x)
{
    float m = mean(x);
    float error = 0.0f;
    unsigned long size = x.size();

    for(int i = 0; i < size; ++i)
    {
        error += (x[i] - m) * (x[i] - m);
    }
    return error / size;
}
//y = ax + b
//pair.first == a
//pair.second == b
std::pair<float, float> linearRegression(const PointsList1D& x, const PointsList1D& y)
{
    std::pair<float, float> ab = {0.0f, 0.0f};
    float nominator = 0.0f;
    float denominator = 0.0f;
    float x_mean = mean(x);
    float y_mean = mean(y);

    for(int i = 0; i < x.size(); ++i)
    {
        nominator += (x[i] - x_mean) * (y[i] - y_mean);
        denominator += (x[i] - x_mean) * (x[i] - x_mean);
    }
    ab.first = nominator / denominator;
    ab.second = y_mean - ab.first * x_mean;
    return ab;
}