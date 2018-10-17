//
// Created by joseph on 17.10.18.
//

#include <math.h>

#include "funs.h"
#include "CubicInterpolation.h"

float CubicInterpolation::CubicHermite(PolynomialCoeffs coeffs, float t) const
{
    float a = -coeffs.A / 2.0f + (3.0f*coeffs.B) / 2.0f - (3.0f*coeffs.C) / 2.0f + coeffs.D / 2.0f;
    float b = coeffs.A - (5.0f*coeffs.B) / 2.0f + 2.0f*coeffs.C - coeffs.D / 2.0f;
    float c = -coeffs.A / 2.0f + coeffs.C / 2.0f;
    float d = coeffs.B;

    return a * static_cast<float>(pow(t, 3)) + b * static_cast<float>(pow(t, 2)) + c * t + d;
}

void CubicInterpolation::Interpolate2D(int pointsToInterpolate)
{
    std::vector<int> index(pointsToInterpolate);
    std::vector<float> t;
    std::vector<float> tx;

    int i = 0, points_size = pointsList.size() - 1;
    std::generate(index.begin(), index.end(), [&i, &pointsToInterpolate, &points_size, &t, &tx]()
    {
        float percent = ((float)i) / (float(pointsToInterpolate - 1));
        tx.push_back((points_size)* percent);
        t.push_back(tx[i] - floor(tx[i]));
        return int(tx[i++]);
    });

    for (int i = 0; i < pointsToInterpolate; ++i)
    {
        std::array<PolynomialCoeffs, 2> coeffs;
        std::array<float, 2> A = GetIndexClamped(pointsList, index[i] - 1);
        std::array<float, 2> B = GetIndexClamped(pointsList, index[i]);
        std::array<float, 2> C = GetIndexClamped(pointsList, index[i] + 1);
        std::array<float, 2> D = GetIndexClamped(pointsList, index[i] + 2);

        for (int i = 0; i < 2; i++)
        {
            coeffs[i].A = A[i];
            coeffs[i].B = B[i];
            coeffs[i].C = C[i];
            coeffs[i].D = D[i];
        }

        float x = CubicHermite(coeffs[0], t[i]);
        float y = CubicHermite(coeffs[1], t[i]);

        std::cout << "Value at " << tx[i] << " = " << x << "  " << y << std::endl;
    }
}

void CubicInterpolation::Interpolate1D(int pointsToInterpolate)
{
    //TODO
}