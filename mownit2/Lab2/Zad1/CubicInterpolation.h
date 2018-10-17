//
// Created by joseph on 17.10.18.
//

#ifndef LAB2_CUBICINTERPOLATION_H
#define LAB2_CUBICINTERPOLATION_H

#include <iostream>
#include <algorithm>
#include <math.h>

#include "funs.h"
#include "IInterpolation.h"

/// <summary>
/// Defines Hermite Cubic Interpolation
/// </summary>
class CubicInterpolation : public IInterpolation
{
    // public construction methods
public:
    explicit CubicInterpolation(const PointsList2D& points) : pointsList(points) {}

    // IInterpolation methods
public:
    void Interpolate2D(int pointsToInterpolate) override;
    void Interpolate1D(int pointsToInterpolate) override;

    // private methods
private:
    struct PolynomialCoeffs
    {
        float A, B, C, D;
    };

    float CubicHermite(PolynomialCoeffs coeffs, float t) const;

    // private members
private:
    const PointsList2D& pointsList;

};


#endif //LAB2_CUBICINTERPOLATION_H
