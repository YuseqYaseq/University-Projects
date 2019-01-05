//
// Created by joseph on 14.11.18.
//

#include "../src/Matrix2D.h"
#include "assert.h"

AGH_NN::Matrix2D<double> matrix1(3, 3, 0.0);
AGH_NN::Matrix2D<double> identity3x3(3, 3, 0.0);

//macierz kolumnowa
AGH_NN::Matrix2D<int> matrix4x1(4, 1, static_cast<int>(0));
AGH_NN::Matrix2D<int> matrix4x4(4, 4, static_cast<int>(0));

void setMatrices() {
  matrix1[0][0] =  3.0; matrix1[0][1] = -2.0; matrix1[0][2] =  1.0;
  matrix1[1][0] =  5.0; matrix1[1][1] =  7.0; matrix1[1][2] = -3.0;
  matrix1[2][0] = -0.4; matrix1[2][1] = -2.0; matrix1[2][2] =  15.0;

  identity3x3[0][0] = 1.0; identity3x3[0][1] = 0.0; identity3x3[0][2] = 0.0;
  identity3x3[1][0] = 0.0; identity3x3[1][1] = 1.0; identity3x3[1][2] = 0.0;
  identity3x3[2][0] = 0.0; identity3x3[2][1] = 0.0; identity3x3[2][2] = 1.0;

  matrix4x1[0][0] = 1;
  matrix4x1[1][0] = 2;
  matrix4x1[2][0] = 3;
  matrix4x1[3][0] = 4;

  matrix4x4[0][0] =  1; matrix4x4[0][1] =  2; matrix4x4[0][2] =  3; matrix4x4[0][3] =  4;
  matrix4x4[1][0] =  5; matrix4x4[1][1] =  6; matrix4x4[1][2] =  7; matrix4x4[1][3] =  8;
  matrix4x4[2][0] =  9; matrix4x4[2][1] = 10; matrix4x4[2][2] = 11; matrix4x4[2][3] = 12;
  matrix4x4[3][0] = 13; matrix4x4[3][1] = 14; matrix4x4[3][2] = 15; matrix4x4[3][3] = 16;
}

void multiplicationTest() {

  AGH_NN::Matrix2D<double> results1 = matrix1 * identity3x3;
  ASSERT_EQUALS_I(results1.get_cols(), 3);
  ASSERT_EQUALS_I(results1.get_rows(), 3);
  results1 = matrix1;
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j)
    {
      ASSERT_EQUALS(results1[i][j], matrix1[i][j]);
    }
  }

  results1 = identity3x3 * matrix1;
  ASSERT_EQUALS_I(results1.get_cols(), 3);
  ASSERT_EQUALS_I(results1.get_rows(), 3);
  for(int i = 0; i < 3; ++i)
  {
    for(int j = 0; j < 3; ++j)
    {
      ASSERT_EQUALS(results1[i][j], matrix1[i][j]);
    }
  }

  AGH_NN::Matrix2D<int> results2 = matrix4x4 * matrix4x1;
  ASSERT_EQUALS_I(results2.get_rows(), 4);
  ASSERT_EQUALS_I(results2.get_cols(), 1);

  ASSERT_EQUALS_I(results2[0][0], 30);
  ASSERT_EQUALS_I(results2[1][0], 70);
  ASSERT_EQUALS_I(results2[2][0], 110);
  ASSERT_EQUALS_I(results2[3][0], 150);

}

void transposeTest() {

}

void plusEqualsTest() {
  AGH_NN::Matrix2D<double> results1 = matrix1;
  results1 += matrix1;
  ASSERT_EQUALS(results1[0][0],  6.0);
  ASSERT_EQUALS(results1[0][1], -4.0);
  ASSERT_EQUALS(results1[0][2],  2.0);
  ASSERT_EQUALS(results1[1][0], 10.0);
  ASSERT_EQUALS(results1[1][1], 14.0);
  ASSERT_EQUALS(results1[1][2], -6.0);
  ASSERT_EQUALS(results1[2][0], -0.8);
  ASSERT_EQUALS(results1[2][1], -4.0);
  ASSERT_EQUALS(results1[2][2], 30.0);
}

void dotTest() {
  //3x3 dot 3x3
  AGH_NN::Matrix2D<double> results1 = matrix1;
  results1 = results1.dot(identity3x3);
  ASSERT_EQUALS(results1[0][0], 3.0);
  ASSERT_EQUALS(results1[0][1], 0.0);
  ASSERT_EQUALS(results1[0][2], 0.0);
  ASSERT_EQUALS(results1[1][0], 0.0);
  ASSERT_EQUALS(results1[1][1], 7.0);
  ASSERT_EQUALS(results1[1][2], 0.0);
  ASSERT_EQUALS(results1[2][0], 0.0);
  ASSERT_EQUALS(results1[2][1], 0.0);
  ASSERT_EQUALS(results1[2][2], 15.0);

  //4x1 dot 4x4
  AGH_NN::Matrix2D<int> results2 = matrix4x1.dot(matrix4x4);
  ASSERT_EQUALS_I(results2.get_rows(), 4);
  ASSERT_EQUALS_I(results2.get_cols(), 4);
  ASSERT_EQUALS_I(results2[0][0], 1);
  ASSERT_EQUALS_I(results2[0][1], 2);
  ASSERT_EQUALS_I(results2[0][2], 3);
  ASSERT_EQUALS_I(results2[1][0], 10);
  ASSERT_EQUALS_I(results2[1][1], 12);
  ASSERT_EQUALS_I(results2[1][2], 14);
  ASSERT_EQUALS_I(results2[2][0], 27);
  ASSERT_EQUALS_I(results2[2][1], 30);
  ASSERT_EQUALS_I(results2[2][2], 33);

  //1x4 dot 4x4
  results2 = matrix4x1.T().dot(matrix4x4);
  ASSERT_EQUALS_I(results2.get_rows(), 4);
  ASSERT_EQUALS_I(results2.get_cols(), 4);
  ASSERT_EQUALS_I(results2[0][0], 1);
  ASSERT_EQUALS_I(results2[0][1], 4);
  ASSERT_EQUALS_I(results2[0][2], 9);
  ASSERT_EQUALS_I(results2[1][0], 5);
  ASSERT_EQUALS_I(results2[1][1], 12);
  ASSERT_EQUALS_I(results2[1][2], 21);
  ASSERT_EQUALS_I(results2[2][0], 9);
  ASSERT_EQUALS_I(results2[2][1], 20);
  ASSERT_EQUALS_I(results2[2][2], 33);

  //4x4 dot 4x1
  results2 = matrix4x4.dot(matrix4x1);
  ASSERT_EQUALS_I(results2.get_rows(), 4);
  ASSERT_EQUALS_I(results2.get_cols(), 4);
  ASSERT_EQUALS_I(results2[0][0], 1);
  ASSERT_EQUALS_I(results2[0][1], 2);
  ASSERT_EQUALS_I(results2[0][2], 3);
  ASSERT_EQUALS_I(results2[1][0], 10);
  ASSERT_EQUALS_I(results2[1][1], 12);
  ASSERT_EQUALS_I(results2[1][2], 14);
  ASSERT_EQUALS_I(results2[2][0], 27);
  ASSERT_EQUALS_I(results2[2][1], 30);
  ASSERT_EQUALS_I(results2[2][2], 33);

  //4x4 dot 1x4
  results2 = matrix4x4.dot(matrix4x1.T());
  ASSERT_EQUALS_I(results2.get_rows(), 4);
  ASSERT_EQUALS_I(results2.get_cols(), 4);
  ASSERT_EQUALS_I(results2[0][0], 1);
  ASSERT_EQUALS_I(results2[0][1], 4);
  ASSERT_EQUALS_I(results2[0][2], 9);
  ASSERT_EQUALS_I(results2[1][0], 5);
  ASSERT_EQUALS_I(results2[1][1], 12);
  ASSERT_EQUALS_I(results2[1][2], 21);
  ASSERT_EQUALS_I(results2[2][0], 9);
  ASSERT_EQUALS_I(results2[2][1], 20);
  ASSERT_EQUALS_I(results2[2][2], 33);
}

void divTest() {
  AGH_NN::Matrix2D<double> results1 = matrix1.div(matrix1);
  ASSERT_EQUALS(results1[0][0], 1.0);
  ASSERT_EQUALS(results1[0][1], 1.0);
  ASSERT_EQUALS(results1[0][2], 1.0);
  ASSERT_EQUALS(results1[1][0], 1.0);
  ASSERT_EQUALS(results1[1][1], 1.0);
  ASSERT_EQUALS(results1[1][2], 1.0);
  ASSERT_EQUALS(results1[2][0], 1.0);
  ASSERT_EQUALS(results1[2][1], 1.0);
  ASSERT_EQUALS(results1[2][2], 1.0);
}

void sigmoidTest() {
  AGH_NN::Matrix2D<double> results1(1, 2, 0.0);
  results1[0][0] = 0.0;
  results1[0][1] = 2.0;
  results1 = AGH_NN::sigmoid2D(results1);
  ASSERT_EQUALS(results1[0][0], 0.5);
  ASSERT_EQUALS(results1[0][1], 0.88079708);
}

void logTest() {
  AGH_NN::Matrix2D<double> results1(1, 4, 0.0);
  results1[0][0] =  0.5;
  results1[0][1] =  1.0;
  results1[0][2] =  5.0;
  results1[0][3] = 10.0;
  results1 = AGH_NN::log(results1);
  ASSERT_EQUALS(results1[0][0], -0.693147);
  ASSERT_EQUALS(results1[0][1], 0.0);
  ASSERT_EQUALS(results1[0][2], 1.60944);
  ASSERT_EQUALS(results1[0][3], 2.30259);
}

void sumTest() {
  AGH_NN::Matrix2D<int> results0 = sum(matrix4x4, OVER_COLUMNS);
  AGH_NN::Matrix2D<int> results1 = sum(matrix4x4, OVER_ROWS);

  ASSERT_EQUALS_I(results0.get_rows(), 1);
  ASSERT_EQUALS_I(results0.get_cols(), 4);
  ASSERT_EQUALS_I(results1.get_rows(), 4);
  ASSERT_EQUALS_I(results1.get_cols(), 1);

  ASSERT_EQUALS_I(results0[0][0], 28);
  ASSERT_EQUALS_I(results0[0][1], 32);
  ASSERT_EQUALS_I(results0[0][2], 36);
  ASSERT_EQUALS_I(results0[0][3], 40);

  ASSERT_EQUALS_I(results1[0][0], 10);
  ASSERT_EQUALS_I(results1[1][0], 26);
  ASSERT_EQUALS_I(results1[2][0], 42);
  ASSERT_EQUALS_I(results1[3][0], 58);
}

void avgTest() {

  AGH_NN::Matrix2D<int> results0 = avg(matrix4x4, OVER_COLUMNS);
  AGH_NN::Matrix2D<int> results1 = avg(matrix4x4, OVER_ROWS);

  ASSERT_EQUALS_I(results0.get_rows(), 1);
  ASSERT_EQUALS_I(results0.get_cols(), 4);
  ASSERT_EQUALS_I(results1.get_rows(), 4);
  ASSERT_EQUALS_I(results1.get_cols(), 1);

  ASSERT_EQUALS_I(results0[0][0], 28 / 4);
  ASSERT_EQUALS_I(results0[0][1], 32 / 4);
  ASSERT_EQUALS_I(results0[0][2], 36 / 4);
  ASSERT_EQUALS_I(results0[0][3], 40 / 4);

  ASSERT_EQUALS_I(results1[0][0], 10 / 4);
  ASSERT_EQUALS_I(results1[1][0], 26 / 4);
  ASSERT_EQUALS_I(results1[2][0], 42 / 4);
  ASSERT_EQUALS_I(results1[3][0], 58 / 4);
}

void Matrix2DTest() {
  setMatrices();
  multiplicationTest();
  plusEqualsTest();
  dotTest();
  divTest();
  sigmoidTest();
  logTest();
  sumTest();
  avgTest();
}