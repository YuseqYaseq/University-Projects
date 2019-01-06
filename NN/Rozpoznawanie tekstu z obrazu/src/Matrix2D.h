#ifndef __MATRIX2D_H
#define __MATRIX2D_H

#include <iostream>
#include <cmath>

namespace AGH_NN {

#define OVER_COLUMNS  0
#define OVER_ROWS     1

  template <typename D>
  class Matrix2D;

  template <typename D>
  std::ostream& operator<<(const std::ostream &ostream, Matrix2D<D> &matrix);

  template<typename D>
  class Matrix2D {

  public:
    explicit Matrix2D(unsigned long _rows, unsigned long _cols, D** mat);
    explicit Matrix2D();

    Matrix2D(unsigned long _rows, unsigned long _cols, const D &_initial);
    Matrix2D(const Matrix2D<D> &rhs);

    virtual ~Matrix2D();

    // Operator overloading, for "standard" mathematical matrix operations
    Matrix2D<D>& operator=(const Matrix2D<D> &rhs);

    Matrix2D<D>& operator+=(const Matrix2D<D> &rhs);
    Matrix2D<D>& operator-=(const Matrix2D<D> &rhs);
    Matrix2D<D>& operator*=(const Matrix2D<D> &rhs);

    // Matrix mathematical operations
    Matrix2D<D> operator+(const Matrix2D<D> &rhs);
    Matrix2D<D> operator-(const Matrix2D<D> &rhs);
    Matrix2D<D> operator*(const Matrix2D<D> &rhs);

    //Add a scalar to every element of a matrix
    Matrix2D<D> operator+(const D scalar);

    //Multiply matrix by a scalar
    Matrix2D<D> operator*(const D scalar);

    //Divide matrix by a scalar
    Matrix2D<D> operator/(const D scalar);

    // Access the individual elements
    D* operator[](const unsigned long id);

    //slice
    Matrix2D<D> slice(unsigned long x_from, unsigned long x_to, unsigned long y_from, unsigned long y_to);

    //Element-wise negation
    Matrix2D<D> operator-();

    //element-wise multiplication
    Matrix2D<D> dot(const Matrix2D<D> &rhs);

    //TODO: add usage of 1xn/nx1 matrices
    //element-wise division
    Matrix2D<D> div(const Matrix2D<D> &rhs);

    bool isSymmetrical();
    D determinant();

    void initialize_gaussian();
    void initialize_gaussian(double median, double variance, unsigned long seed);

    //transpose
    Matrix2D<D> T();

    // Printing matrix
    friend std::ostream& operator<< <>(const std::ostream &ostream, Matrix2D<D> &matrix);

    // Access the row and column sizes
    unsigned long get_rows() const;

    unsigned long get_cols() const;
  private:
    D** matrix = 0;
    unsigned long rows;
    unsigned long cols;

    D operator()(const unsigned long row, const unsigned long column) const;
    void showDotFailedMsg(const Matrix2D<D> &rhs) const;
  };

  template <typename D>
  Matrix2D<D> operator+(const D scalar, Matrix2D<D>& matrix);

  template <typename D>
  Matrix2D<D> operator-(const D scalar, Matrix2D<D>& matrix);

  template <typename D>
  Matrix2D<D> operator*(const D scalar, Matrix2D<D>& matrix);

  template <typename D>
  Matrix2D<D> operator/(const D scalar, Matrix2D<D>& matrix);

  template <typename D>
  Matrix2D<D> exp(Matrix2D<D> a);

  template <typename D>
  Matrix2D<D> log(Matrix2D<D> a);

  template <typename D>
  Matrix2D<D> sigmoid2D(Matrix2D<D> a);

  template <typename D>
  D sum(Matrix2D<D> a);

  template <typename D>
  D avg(Matrix2D<D> a);

  //sum over chosen dimension
  //0 - over columns, returns 1xn
  //1 - over rows, returns nx1
  template <typename D>
  Matrix2D<D> sum(Matrix2D<D> matrix, unsigned long dimension);

  template <typename D>
  Matrix2D<D> avg(Matrix2D<D> matrix, unsigned long dimension);
};

#include "Matrix2D.cpp"

#endif