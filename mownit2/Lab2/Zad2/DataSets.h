//
// Created by joseph on 28.10.18.
//

#ifndef LAB2_DATASETS_H
#define LAB2_DATASETS_H

#include "../Zad1/funs.h"

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

const PointsList1D pointsForRegressionX =
        {
                0.0f,
                1.0f,
                2.0f
        };

const PointsList1D pointsForRegressionY =
        {
                0.0f,
                1.0f,
                2.0f
        };

const PointsList1D DataSetX2 =
        {
                1.0f,
                2.0f,
                4.0f,
                3.0f,
                5.0f
        };

const PointsList1D DataSetY2 =
        {
                1.0f,
                3.0f,
                3.0f,
                2.0f,
                5.0f
        };


const PointsList1D DataRegressorX =
        {
         108, 19, 13, 124, 40, 57, 23, 14, 45, 10, 5, 48, 11, 23, 7, 2, 24, 6, 3, 23, 6, 9, 9, 3, 29,
         7, 4, 20, 7, 4, 0, 25, 6, 5, 22, 11, 61, 12, 4, 16, 13, 60, 41, 37, 55, 41, 11, 27, 8, 3,
         17, 13, 13, 15, 8, 29, 30, 24, 9, 31, 14, 53, 26
        };




const PointsList1D DataRegressorY =
        {
                392.5,46.2,15.7,422.2,119.4,170.9,56.9,77.5,214.0,65.3,20.9,
                248.1,23.5,39.6,48.8,6.6,134.9,50.9,4.4,113.0,14.8,48.7,52.1,13.2,103.9,77.5,11.8,
                98.1,27.9,38.1,0.00,69.2,14.6,40.3,161.5,57.2,217.6,58.1,12.6,59.6,89.9,202.4,181.3,
                152.8,162.8,73.4,21.3,92.6,76.1,39.9,142.1,93.0,31.9,32.1,55.6,133.3,194.5,137.9,87.4,
                209.8,95.5,244.6,187.5

        };
#endif //LAB2_DATASETS_H
