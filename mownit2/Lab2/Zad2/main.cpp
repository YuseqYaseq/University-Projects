//
// Created by joseph on 17.10.18.
//

#include <iostream>

#include "LagrangeInterpolation.h"
#include "LinearRegression.h"
#include "DataSets.h"

int main() {
    auto interpolation = LagrangeInterpolation(points2D, points1D);
    interpolation.Interpolate2D(13);
    interpolation.Interpolate1D(13);
    std::pair<float, float> ab = linearRegression(pointsForRegressionX, pointsForRegressionY);
    std::cout << ab.first << " " << ab.second << " " << rmse(pointsForRegressionX) << std::endl;

    ab = linearRegression(DataSetX2, DataSetY2);
    std::cout << ab.first << " " << ab.second << " " << rmse(DataSetX2) << std::endl;
    return 0;
}