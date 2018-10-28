//
// Created by joseph on 28.10.18.
//

#ifndef LAB2_LINEARREGRESSION_H
#define LAB2_LINEARREGRESSION_H

#include <vector>

#include "../Zad1/funs.h"

float mean(PointsList1D x);

float rmse(PointsList1D x);

//y = ax + b
//pair.first == a
//pair.second == b
std::pair<float, float> linearRegression(const PointsList1D& x, const PointsList1D& y);

#endif //LAB2_LINEARREGRESSION_H
