//
// Created by joseph on 17.10.18.
//

#ifndef LAB2_IINTERPOLATION_H
#define LAB2_IINTERPOLATION_H

/// <summary>
/// Defines structure for interpolation classes
/// </summary>
class IInterpolation
{
    // public construction and destruction methods
public:
    virtual ~IInterpolation() = default;

    // public interface methods
public:
    virtual void Interpolate1D(unsigned int pointsToInterpolate) =  0;
    virtual void Interpolate2D(unsigned int pointsToInterpolate) =  0;

};

#endif //LAB2_IINTERPOLATION_H
