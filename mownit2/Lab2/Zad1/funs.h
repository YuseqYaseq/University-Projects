//
// Created by joseph on 17.10.18.
//

#ifndef LAB2_FUNS_H
#define LAB2_FUNS_H

#include <vector>
#include <array>

typedef std::vector<std::array<float, 2>> PointsList2D;
typedef std::vector<float> PointsList1D;

/// <summary>
/// Template function used for clamping specified datasets
/// </summary>
template <typename T>
T GetIndexClamped(const std::vector<T> points, int index)
{
    if (index < 0)
        return points[0];
    else if (index >= int(points.size()))
        return points.back();
    else
        return points[index];
}

#endif //LAB2_FUNS_H
