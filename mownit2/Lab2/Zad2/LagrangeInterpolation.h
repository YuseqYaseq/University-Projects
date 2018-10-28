//
// Created by joseph on 17.10.18.
//

#ifndef LAB2_LAGRANGEINTERPOLATION_H
#define LAB2_LAGRANGEINTERPOLATION_H

#include "../Zad1/IInterpolation.h"
#include "../Zad1/funs.h"

class LagrangeInterpolation : public IInterpolation {
public:
    explicit LagrangeInterpolation(const PointsList2D& points2D, const PointsList1D& points1D) : pointsList2D(points2D), pointsList1D(points1D) {}

    void Interpolate1D(unsigned int pointsToInterpolate) override;
    void Interpolate2D(unsigned int pointsToInterpolate) override;

private:
    const PointsList1D& pointsList1D;
    const PointsList2D& pointsList2D;

    float CalculateLagrange1D(float x);
    std::array<float, 2> CalculateLagrange2D(float x);
};


#endif //LAB2_LAGRANGEINTERPOLATION_H
