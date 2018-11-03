#ifndef __MATRIX2D_H
#define __MATRIX2D_H

#include <vector>
#include <iostream>
#include <array>

namespace AGH {
  template<typename T>
  class Matrix2D {

  public:
    explicit Matrix2D(const std::vector<std::vector<T>> &mat);
    explicit Matrix2D() = default;

    Matrix2D(unsigned long _rows, unsigned long _cols, const T &_initial);

    Matrix2D(const Matrix2D<T> &rhs);

    virtual ~Matrix2D();

    // Operator overloading, for "standard" mathematical matrix operations
    Matrix2D<T> &operator=(const Matrix2D<T> &rhs);

    // Matrix mathematical operations
    Matrix2D<T> operator+(const Matrix2D<T> &rhs);

    Matrix2D<T> operator*(const Matrix2D<T> &rhs);

    // Access the individual elements
    T &operator()(const unsigned &row, const unsigned &col);

    const T &operator()(const unsigned &row, const unsigned &col) const;

    std::vector<T> &operator[](const unsigned &row);

    bool isSymmetrical();

    T determinant();

    Matrix2D<T> transpose();

    // Printing matrix
    friend std::ostream &operator<<(const std::ostream &ostream, const Matrix2D<T> &matrix);

    // Access the row and column sizes
    unsigned long get_rows() const;

    unsigned long get_cols() const;

    std::pair<Matrix2D<T>, Matrix2D<T>> doolittleDecomposition();
    Matrix2D<T> choleskyDecomposition();
    Matrix2D<T> gaussianElimination();

  private:
    std::vector<std::vector<T>> matrix;
    unsigned long rows;
    unsigned long cols;

  };
};

#include "Matrix2D.cpp"

#endif