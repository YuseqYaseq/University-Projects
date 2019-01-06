
#include <random>
#include "Matrix2D.h"


// Parameter Constructor                                                                                                                                                      
template<typename D>
AGH_NN::Matrix2D<D>::Matrix2D(unsigned long _rows, unsigned long _cols, D** mat)
{
  matrix = mat;
  rows = _rows;
  cols = _cols;
}

// Parameter Constructor                                                                                                                                                      
template<typename D>
AGH_NN::Matrix2D<D>::Matrix2D(unsigned long _rows, unsigned long _cols, const D& _initial)
{
  if(matrix)this->~Matrix2D();
  matrix = new D*[_rows];
  for(unsigned long i = 0; i < _rows; ++i)
  {
    matrix[i] = new D[_cols];
    for(unsigned long j = 0; j < _cols; ++j)
    {
      matrix[i][j] = _initial;
    }
  }
  rows = _rows;
  cols = _cols;
}

template <typename D>
AGH_NN::Matrix2D<D>::Matrix2D()
{
  rows = 0;
  cols = 0;
  matrix = 0;
}

// Copy Constructor                                                                                                                                                           
template<typename D>
AGH_NN::Matrix2D<D>::Matrix2D(const Matrix2D<D>& rhs)
{
  rows = rhs.get_rows();
  cols = rhs.get_cols();
  if(matrix)this->~Matrix2D();
  matrix = new D*[rows];
  for(unsigned long i = 0; i < rows; ++i)
  {
    matrix[i] = new D[cols];
    for(unsigned long j = 0; j < cols; ++j)
    {
      matrix[i][j] = rhs.matrix[i][j];
    }
  }
}

template <typename D>
AGH_NN::Matrix2D<D>::~Matrix2D()
{
  if(!matrix)return;
  for(unsigned long i = 0; i < rows; ++i)
  {
    delete[] matrix[i];
  }
  delete[] matrix;
  matrix = 0;
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename D>
unsigned long AGH_NN::Matrix2D<D>::get_rows() const
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename D>
unsigned long AGH_NN::Matrix2D<D>::get_cols() const
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename D>
AGH_NN::Matrix2D<D>& AGH_NN::Matrix2D<D>::operator=(const Matrix2D<D>& rhs)
{
  if (&rhs == this)
    return *this;

  if(matrix)
  {
    this->~Matrix2D();
  }
  rows = rhs.get_rows();
  cols = rhs.get_cols();

  matrix = new D*[rows];
  for(int i = 0; i < rows; ++i)
  {
    matrix[i] = new D[cols];
  }

  for(unsigned long i = 0; i < rows; ++i)
  {
    for(unsigned long j = 0; j < cols; ++j)
    {
      matrix[i][j] = rhs.matrix[i][j];
    }
  }

  return *this;
}

template <typename D>
AGH_NN::Matrix2D<D>& AGH_NN::Matrix2D<D>::operator+=(const AGH_NN::Matrix2D<D> &rhs)
{
  return (*this) = (*this) + rhs;
}

template <typename D>
AGH_NN::Matrix2D<D>& AGH_NN::Matrix2D<D>::operator-=(const AGH_NN::Matrix2D<D> &rhs)
{
  return (*this) = (*this) - rhs;
}

template <typename D>
AGH_NN::Matrix2D<D>& AGH_NN::Matrix2D<D>::operator*=(const AGH_NN::Matrix2D<D> &rhs)
{
  return (*this) = (*this) * rhs;
}

// Access the individual elements                                                                                                                                             
template<typename D>
D* AGH_NN::Matrix2D<D>::operator[](const unsigned long row)
{
  return matrix[row];
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::slice(unsigned long x_from, unsigned long x_to, unsigned long y_from,
                                               unsigned long y_to)
{
  if(x_to > cols - 1 || y_to > rows - 1) {
    std::cerr << "slice dispositioned" << std::endl;
    std::cerr << "rows = " << rows << ", cols = " << cols << std::endl;
    std::cerr << "y_to = " << y_to << ", x_to = " << x_to << std::endl;
    throw -1;
  }
  AGH_NN::Matrix2D<D> ret(y_to - y_from + 1, x_to - x_from + 1, 0.0);
  for(unsigned long y = y_from; y <= y_to; ++y) {
    for(unsigned long x = x_from; x <= x_to; ++x) {
      ret[y - y_from][x - x_from] = matrix[y][x];
    }
  }
  return ret;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator-()
{
  Matrix2D<D> returnMatrix(*this);
  for(int i = 0; i < get_rows(); ++i)
  {
    for(int j = 0; j < get_cols(); ++j)
    {
      returnMatrix[i][j] = -returnMatrix[i][j];
    }
  }
  return returnMatrix;
}

template <typename D>
void AGH_NN::Matrix2D<D>::showDotFailedMsg(const AGH_NN::Matrix2D<D> &rhs) const
{
  std::cerr << "Dimensions don't match!" << std::endl;
  std::cerr << get_cols() << " != " << rhs.get_cols() << " || "
            << get_rows() << " != " << rhs.get_rows() << std::endl;
  throw -1;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::dot(const AGH_NN::Matrix2D<D> &rhs)
{
  if(get_cols() == rhs.get_cols() && get_rows() == rhs.get_rows())
  {
    Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
    for(unsigned long i = 0; i < get_rows(); ++i)
    {
      for(unsigned long j = 0; j < get_cols(); ++j)
      {
        returnMatrix[i][j] = matrix[i][j] * rhs(i, j);
      }
    }
    return returnMatrix;
  }
  else if(get_cols() == rhs.get_cols() && get_rows() != rhs.get_rows())
  {
    if(get_rows() == 1)
    {
      Matrix2D<D> returnMatrix(rhs.get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < rhs.get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[0][j] * rhs(i, j);
        }
      }
      return returnMatrix;
    }
    else if(rhs.get_rows() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][j] * rhs(0, j);
        }
      }
      return returnMatrix;
    }
    else
    {
      showDotFailedMsg(rhs);
    }
  }
  else if(get_cols() != rhs.get_cols() && get_rows() == rhs.get_rows())
  {
    if(get_cols() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), rhs.get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < rhs.get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][0] * rhs(i, j);
        }
      }
      return returnMatrix;
    }
    else if(rhs.get_cols() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][j] * rhs(i, 0);
        }
      }
      return returnMatrix;
    }
    else
    {
      showDotFailedMsg(rhs);
    }
  }
  else
  {
    showDotFailedMsg(rhs);
  }
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::div(const AGH_NN::Matrix2D<D> &rhs)
{
  Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
  if(get_cols() != rhs.get_cols() || get_rows() != rhs.get_rows())
  {
    std::cerr << "Dimensions don't match!" << std::endl;
    std::cerr << get_cols() << " != " << rhs.get_cols() << " || "
              << get_rows() << " != " << rhs.get_rows() << std::endl;
  }

  for(unsigned long i = 0; i < get_rows(); ++i)
  {
    for(unsigned long j = 0; j < get_cols(); ++j)
    {
      returnMatrix[i][j] = matrix[i][j] / rhs.matrix[i][j];
    }
  }
  return returnMatrix;
}

// Addition of two matrices                                                                                                                                                   
template<typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator+(const Matrix2D<D>& rhs)
{
  if(get_cols() == rhs.get_cols() && get_rows() == rhs.get_rows())
  {
    Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
    for(unsigned long i = 0; i < get_rows(); ++i)
    {
      for(unsigned long j = 0; j < get_cols(); ++j)
      {
        returnMatrix[i][j] = matrix[i][j] + rhs(i, j);
      }
    }
    return returnMatrix;
  }
  else if(get_cols() == rhs.get_cols() && get_rows() != rhs.get_rows())
  {
    if(get_rows() == 1)
    {
      Matrix2D<D> returnMatrix(rhs.get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < rhs.get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[0][j] + rhs(i, j);
        }
      }
      return returnMatrix;
    }
    else if(rhs.get_rows() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][j] + rhs(0, j);
        }
      }
      return returnMatrix;
    }
    else
    {
      showDotFailedMsg(rhs);
    }
  }
  else if(get_cols() != rhs.get_cols() && get_rows() == rhs.get_rows())
  {
    if(get_cols() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), rhs.get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < rhs.get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][0] + rhs(i, j);
        }
      }
      return returnMatrix;
    }
    else if(rhs.get_cols() == 1)
    {
      Matrix2D<D> returnMatrix(get_rows(), get_cols(), static_cast<D>(0.0));
      for(unsigned long i = 0; i < get_rows(); ++i)
      {
        for(unsigned long j = 0; j < get_cols(); ++j)
        {
          returnMatrix[i][j] = matrix[i][j] + rhs(i, 0);
        }
      }
      return returnMatrix;
    }
    else
    {
      showDotFailedMsg(rhs);
    }
  }
  else
  {
    showDotFailedMsg(rhs);
  }
}

template<typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator-(const Matrix2D<D>& rhs)
{
  Matrix2D<D> returnMatrix = *this;
  if(rhs.cols != this->cols || rhs.rows != this->rows)
  {
    std::cerr << "Dimensions don't match!" << std::endl;
    std::cerr << rhs.cols << " != " <<  this->cols << " || "
              <<  rhs.rows << " != " << this->rows << std::endl;

    throw std::exception();
  }
  for(unsigned long i = 0; i < rhs.get_rows(); ++i)
  {
    for(unsigned long j = 0; j < rhs.get_cols(); ++j)
    {
      returnMatrix.matrix[i][j] -= rhs.matrix[i][j];
    }
  }
  return returnMatrix;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator+(const D scalar)
{
  Matrix2D<D> returnMatrix = Matrix2D(*this);
  for(int i = 0; i < returnMatrix.get_rows(); ++i)
  {
    for(int j = 0; j < returnMatrix.get_cols(); ++j)
    {
      returnMatrix[i][j] += scalar;
    }
  }
  return returnMatrix;
}

// Left multiplication of this matrix and another
template<typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator*(const Matrix2D<D>& rhs)
{
  Matrix2D<D> returnMatrix = Matrix2D(this->get_rows(), rhs.get_cols(), static_cast<D>(0));
  if(this->get_cols() != rhs.get_rows())
  {
    std::cerr << "Dimensions don't match!" << std::endl;
    std::cerr << this->get_cols() << " != " << rhs.get_rows() << std::endl;
    throw std::exception();
  }
  for(unsigned long i = 0; i < returnMatrix.get_rows(); ++i)
  {
    for(unsigned long j = 0; j < returnMatrix.get_cols(); ++j)
    {
      for(unsigned long k = 0; k < get_cols(); ++k)
      {
        returnMatrix[i][j] += (*this)(i, k) * rhs(k, j);
      }
    }
  }
  return returnMatrix;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator*(const D scalar)
{
  Matrix2D<D> returnMatrix = Matrix2D(*this);
  for(int i = 0; i < returnMatrix.get_rows(); ++i)
  {
    for(int j = 0; j < returnMatrix.get_cols(); ++j)
    {
      returnMatrix[i][j] *= scalar;
    }
  }
  return returnMatrix;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::operator/(const D scalar)
{
  Matrix2D<D> returnMatrix = Matrix2D(*this);
  for(int i = 0; i < returnMatrix.get_rows(); ++i)
  {
    for(int j = 0; j < returnMatrix.get_cols(); ++j)
    {
      returnMatrix[i][j] /= scalar;
    }
  }
  return returnMatrix;
}

template<typename D>
bool AGH_NN::Matrix2D<D>::isSymmetrical()
{
  for(int i = 0; i < this->get_rows(); ++i)
  {
    for(int j = 0; j < this->get_cols(); ++j)
    {
      if(matrix[i][j] != matrix[j][i]) return false;
    }
  }
  return true;
}

//Naive implementation
template<typename D>
D AGH_NN::Matrix2D<D>::determinant()
{
  /*Matrix2D<D>** minors = new Matrix2D<D>[this->get_rows() - 1][this->get_cols() - 1];
  for(int i = 0; i < this->get_rows() - 1; ++i)
  {
    for(int j = 0; j < this->get_cols() - 1; ++j)
    {
      minors
    }
  }*/
}

template<typename D>
AGH_NN::Matrix2D<D> AGH_NN::Matrix2D<D>::T()
{
    Matrix2D<D> ret(this->get_cols(), this->get_rows(), static_cast<D>(0));
    for(unsigned long i = 0; i < this->get_rows(); ++i)
    {
        for(unsigned long j = 0; j < this->get_cols(); ++j)
        {
            ret[j][i] = matrix[i][j];
        }
    }
    return ret;
}

template <typename D>
D AGH_NN::Matrix2D<D>::operator()(const unsigned long row, const unsigned long column) const
{
  return matrix[row][column];
}

// Printing matrix                                                                                                                        
template<typename D>
std::ostream& operator<<(std::ostream& stream, AGH_NN::Matrix2D<D>& matrix)
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix[i][j] << ", ";
    }
    stream << std::endl;
  }
  stream << std::endl;
  return stream;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::exp(AGH_NN::Matrix2D<D> a)
{
  Matrix2D<D> returnMatrix(a.get_rows(), a.get_cols(), static_cast<D>(0.0));
  for(int i = 0; i < a.get_rows(); ++i)
  {
    for(int j = 0; j < a.get_cols(); ++j)
    {
      returnMatrix[i][j] = ::exp(a[i][j]);
    }
  }
  return returnMatrix;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::log(AGH_NN::Matrix2D<D> a)
{
  Matrix2D<D> ret(a.get_rows(), a.get_cols(), static_cast<D>(0));
  for(int i = 0; i < a.get_rows(); ++i)
  {
    for(int j = 0; j < a.get_cols(); ++j)
    {
      ret[i][j] = static_cast<D>(::log(static_cast<double>(a[i][j])));
    }
  }
  return ret;
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::sigmoid2D(AGH_NN::Matrix2D<D> a)
{
  Matrix2D<D> ones(a.get_rows(), a.get_cols(), static_cast<D>(1));
  return ones.div(ones + exp(-a));
}

template <typename D>
AGH_NN::Matrix2D<D> operator+(const D scalar, AGH_NN::Matrix2D<D> matrix)
{
  return matrix + scalar;
}

template <typename D>
AGH_NN::Matrix2D<D> operator*(const D scalar, AGH_NN::Matrix2D<D> matrix)
{
  return matrix * scalar;
}

template <typename D>
D AGH_NN::sum(AGH_NN::Matrix2D<D> a)
{
  D sum = static_cast<D>(0.0);
  for(int i = 0; i < a.get_rows(); ++i)
  {
    for(int j = 0; j < a.get_cols(); ++j)
    {
      sum += a[i][j];
    }
  }
  return sum;
}

template <typename D>
D AGH_NN::avg(AGH_NN::Matrix2D<D> a)
{

  D sum = static_cast<D>(0.0);
  for(int i = 0; i < a.get_rows(); ++i)
  {
    for(int j = 0; j < a.get_cols(); ++j)
    {
      sum += a[i][j];
    }
  }
  return sum / static_cast<D>(a.get_cols() * a.get_rows());
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::sum(AGH_NN::Matrix2D<D> matrix, unsigned long dimension)
{
  if(dimension == 0)
  {
    Matrix2D<D> returnMatrix(1, matrix.get_cols(), static_cast<D>(0.0));
    for(int i = 0; i < matrix.get_rows(); ++i)
    {
      for(int j = 0; j < matrix.get_cols(); ++j)
      {
        returnMatrix[0][j] += matrix[i][j];
      }
    }
    return returnMatrix;
  }
  else
  {
    Matrix2D<D> returnMatrix(matrix.get_rows(), 1, static_cast<D>(0.0));
    for(int i = 0; i < matrix.get_rows(); ++i)
    {
      for(int j = 0; j < matrix.get_cols(); ++j)
      {
        returnMatrix[i][0] += matrix[i][j];
      }
    }
    return returnMatrix;
  }
}

template <typename D>
AGH_NN::Matrix2D<D> AGH_NN::avg(AGH_NN::Matrix2D<D> matrix, unsigned long dimension)
{
  if(dimension == 0)
  {
    Matrix2D<D> returnMatrix(1, matrix.get_cols(), static_cast<D>(0.0));
    for(int i = 0; i < matrix.get_rows(); ++i)
    {
      for(int j = 0; j < matrix.get_cols(); ++j)
      {
        returnMatrix[0][j] += matrix[i][j];
      }
    }
    return returnMatrix / static_cast<D>(matrix.get_rows());
  }
  else
  {
    Matrix2D<D> returnMatrix(matrix.get_rows(), 1, static_cast<D>(0.0));
    for(int i = 0; i < matrix.get_rows(); ++i)
    {
      for(int j = 0; j < matrix.get_cols(); ++j)
      {
        returnMatrix[i][0] += matrix[i][j];
      }
    }
    return returnMatrix / static_cast<D>(matrix.get_cols());
  }
}

template <typename D>
void AGH_NN::Matrix2D<D>::initialize_gaussian()
{
  srand(time(NULL));
  initialize_gaussian(0.0, 1.0, static_cast<unsigned long>(rand()));
}

template <typename D>
void AGH_NN::Matrix2D<D>::initialize_gaussian(double median, double variance, unsigned long seed)
{
  std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(median, variance);
  for(int i = 0; i < get_cols(); ++i)
  {
    for(int j = 0; j < get_rows(); ++j)
    {
      matrix[j][i] = distribution(generator);
    }
  }
}