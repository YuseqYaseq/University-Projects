//
// Created by joseph on 17.10.18.
//

#include <algorithm>
#include <iostream>
#include "LagrangeInterpolation.h"

void LagrangeInterpolation::Interpolate1D(unsigned int pointsToInterpolate)
{
    std::vector<int> index(pointsToInterpolate);
    std::vector<float> t;

    unsigned long j = 0, points_size = pointsList1D.size() - 1;
    std::generate(index.begin(), index.end(), [&j, &pointsToInterpolate, &points_size, &t]()
    {
        float percent = ((float)j) / (float(pointsToInterpolate - 1));
        t.push_back((points_size)* percent);
        return int(t[j++]);
    });

    for(int i = 0; i < pointsToInterpolate; ++i)
    {
        float x = CalculateLagrange1D(t[i]);

        std::cout << "Value at " << t[i] << " = " << x << std::endl;
    }
}

void LagrangeInterpolation::Interpolate2D(unsigned int pointsToInterpolate)
{
    std::vector<int> index(pointsToInterpolate);
    std::vector<float> t;

    unsigned long j = 0, points_size = pointsList2D.size() - 1;
    std::generate(index.begin(), index.end(), [&j, &pointsToInterpolate, &points_size, &t]()
    {
        float percent = ((float)j) / (float(pointsToInterpolate - 1));
        t.push_back((points_size)* percent);
        return int(t[j++]);
    });

    for(int i = 0; i < pointsToInterpolate; ++i)
    {
        std::array<float, 2> res = CalculateLagrange2D(t[i]);

        std::cout << "Value at " << t[i] << " = " << res[0] << " " << res[1] << std::endl;
    }
}

float LagrangeInterpolation::CalculateLagrange1D(float x)
{
    float ret = 0.0f;
    for(int i = 0; i < pointsList1D.size(); ++i)
    {
        float basePolynomial = 1.0f;
        for(int j = 0; j < pointsList1D.size(); ++j)
        {
            if(i != j)
                basePolynomial *= (x - static_cast<float>(j)) / static_cast<float>(i - j);
        }
        ret += basePolynomial * pointsList1D[i];
    }
    return ret;
}

std::array<float, 2> LagrangeInterpolation::CalculateLagrange2D(float x) {
    int dimension = 2;
    std::array<float, 2> ret = {0.0f, 0.0f};
    for(int d = 0; d < dimension; ++d)
    {
        for(int i = 0; i < pointsList2D.size(); ++i)
        {
            float basePolynomial = 1.0f;
            for(int j = 0; j < pointsList2D.size(); ++j)
            {
                if(i != j)
                    basePolynomial *= (x - static_cast<float>(j)) / static_cast<float>(i - j);
            }
            ret[d] += basePolynomial * pointsList2D[i][d];
        }
    }
    return ret;
}