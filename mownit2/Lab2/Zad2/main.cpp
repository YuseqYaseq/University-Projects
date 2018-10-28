//
// Created by joseph on 17.10.18.
//

#include <iostream>

#include "LagrangeInterpolation.h"
#include "LinearRegression.h"
#include "LinearRegressor.h"
#include "DataSets.h"

int main() {
    auto interpolation = LagrangeInterpolation(points2D, points1D);
    interpolation.Interpolate2D(13);
    interpolation.Interpolate1D(13);
    std::pair<float, float> ab = linearRegression(pointsForRegressionX, pointsForRegressionY);
    std::cout << "y = " << ab.first << "x + " << ab.second << "; error = " << rmse(pointsForRegressionX) << std::endl;

    ab = linearRegression(DataSetX2, DataSetY2);
    std::cout << "y = " << ab.first << "x + " << ab.second << "; error = " << rmse(DataSetX2) << std::endl;

    LinearRegressor regressor;
    regressor.fit(DataRegressorX, DataRegressorY);
    std::cout << "y = " << regressor.getA() << "x + " << regressor.getB()
        << "; error = " << rmse(DataRegressorX) << std::endl;
    return 0;
}