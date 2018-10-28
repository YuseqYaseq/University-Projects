
#include "CubicInterpolation.h"

const PointsList1D points1D =
{
    0.0f,
    1.6f,
    2.3f,
    3.5f,
    4.3f,
    5.9f,
    6.8f
};

const PointsList2D points2D =
{
    { 0.0f, 1.1f },
    { 1.6f, 8.3f },
    { 2.3f, 6.5f },
    { 3.5f, 4.7f },
    { 4.3f, 3.1f },
    { 5.9f, 7.5f },
    { 6.8f, 0.0f }
};

int main() {
    auto interpolation = CubicInterpolation(points2D, points1D);
    interpolation.Interpolate2D(10);
    interpolation.Interpolate1D(13);
    return 0;
}