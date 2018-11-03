#include "Matrix2D.h"
#include <exception>
#include <cmath>

using namespace AGH;

// Parameter Constructor                                                                                                                                                      
template<typename T>
Matrix2D<T>::Matrix2D(const std::vector<std::vector<T>>& mat)
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++)
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
Matrix2D<T>::Matrix2D(unsigned long _rows, unsigned long _cols, const T& _initial)
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++)
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
Matrix2D<T>::Matrix2D(const Matrix2D<T>& rhs)
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

template <typename T>
Matrix2D<T>::~Matrix2D()
{

}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned long Matrix2D<T>::get_rows() const
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned long Matrix2D<T>::get_cols() const
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
Matrix2D<T>& Matrix2D<T>::operator=(const Matrix2D<T>& rhs)
{
  if (&rhs == this)
    return *this;

  unsigned long new_rows = rhs.get_rows();
  unsigned long new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++)
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++)
  {
    for (unsigned j=0; j<new_cols; j++)
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& Matrix2D<T>::operator()(const unsigned& row, const unsigned& col)
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& Matrix2D<T>::operator()(const unsigned& row, const unsigned& col) const
{
  return this->matrix[row][col];
}

template <typename T>
std::vector<T>& Matrix2D<T>::operator[](const unsigned &row)
{
  return this->matrix[row];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
Matrix2D<T> Matrix2D<T>::operator+(const Matrix2D<T>& rhs)
{
  Matrix2D<T> returnMatrix = *this;
  if(rhs.cols != this->cols || rhs.rows != this->rows) throw std::exception();
  for(unsigned long i = 0; i < rhs.get_rows(); ++i)
  {
    for(unsigned long j = 0; j < rhs.get_cols(); ++j)
    {
      returnMatrix.matrix[i][j] += rhs.matrix[i][j];
    }
  }
  return returnMatrix;
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& rhs)
{
  Matrix2D<T> returnMatrix = Matrix2D(rhs.get_rows(), this->get_cols(), 0);
  if(rhs.get_cols() != returnMatrix.get_rows()) throw std::exception();
  for(unsigned long i = 0; i < returnMatrix.get_rows(); ++i)
  {
    for(unsigned long j = 0; j < returnMatrix.get_cols(); ++j)
    {
      for(unsigned long k = 0; k < rhs.get_cols(); ++k)
      {
        returnMatrix(i, j) += (*this)(i, k) * rhs(k, j);
      }
    }
  }
  return returnMatrix;
}

template<typename T>
bool Matrix2D<T>::isSymmetrical()
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

template<typename T>
T Matrix2D<T>::determinant()
{
  if(this->get_cols() == 1) return matrix[0][0];
  Matrix2D m = Matrix2D(this->get_rows() - 1, this->get_cols() - 1, static_cast<T>(0));
  std::vector<Matrix2D<T>> minors(this->get_cols(), m);
  T* minorsDeterminants = new T[this->get_cols()];
  T result = static_cast<T>(0);

  for(int n = 0; n < this->get_cols(); ++n)
  {
    for(int i = 0; i < this->get_rows(); ++i)
    {
      for(int j = 0; j < this->get_cols() - 1; ++j)
      {
        if(n > i)
        {
          minors[n][i][j] = matrix[i][j+1];
        } else if(n < i)
        {
          minors[n][i-1][j] = matrix[i][j+1];
        }
      }
    }
    minorsDeterminants[n] = minors[n].determinant();
  }

  for(int i = 0; i < this->get_cols(); ++i)
  {
    if(i % 2 == 0)
      result += matrix[i][0] * minorsDeterminants[i];
    else
      result -= matrix[i][0] * minorsDeterminants[i];
  }
  delete[] minorsDeterminants;
  return result;
}

template<typename T>
Matrix2D<T> Matrix2D<T>::transpose()
{
    Matrix2D<T> ret(this->get_cols(), this->get_rows(), 0);
    for(unsigned long i = 0; i < this->get_rows(); ++i)
    {
        for(unsigned long j = 0; j < this->get_cols(); ++j)
        {
            ret(j, i) = (*this)(i, j);
        }
    }
    return ret;
}

// Printing matrix
template<typename T>
std::ostream& operator<<(std::ostream& stream, const Matrix2D<T>& matrix)
{
  for (int i=0; i<matrix.get_rows(); i++)
  {
    for (int j=0; j<matrix.get_cols(); j++)
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
  stream << std::endl;
  return stream;
}

template <typename T>
std::pair<Matrix2D<T>, Matrix2D<T>> Matrix2D<T>::doolittleDecomposition()
{
  std::pair<Matrix2D<T>, Matrix2D<T>> LU = {Matrix2D(this->get_rows(),
                                            this->get_cols(), 0), Matrix2D(this->get_rows(), this->get_cols(), 0)};

  for(int i = 0; i < this->get_rows(); ++i)
  {
    LU.first[i][i] = 1;
  }

  for(int n = 0; n < this->get_rows(); ++n)
  {
    //U
    for(int i = n; i < this->get_rows(); ++i)
    {
      T sum = matrix[n][i];
      for(int j = 0; j < n; ++j)
      {
        sum -= LU.first[n][j] * LU.second[j][i];
      }
      LU.second[n][i] = sum;
    }

    //L
    for(int i = n+1; i < this->get_cols(); ++i)
    {
      T sum = matrix[i][n];
      for(int j = 0; j < i; ++j)
      {
        sum -= LU.first[i][j] * LU.second[j][n];
      }
      LU.first[i][n] = sum / LU.second[n][n];
    }
  }

  return LU;
}

template <typename T>
Matrix2D<T> Matrix2D<T>::choleskyDecomposition()
{
  Matrix2D<T> L = Matrix2D(this->get_rows(), this->get_cols(), static_cast<T>(0));
  for(int i = 0; i < this->get_rows(); ++i)
  {
    for(int j = 0; j <= i; ++j)
    {
      if(i == j)
      {
        T sum = static_cast<T>(0);
        for(int k = 0; k <= j - 1; ++k)
        {
          sum += L[j][k] * L[j][k];
        }
        L[i][j] = sqrt((*this)[i][j] - sum);
      }
      else
      {
        T sum = static_cast<T>(0);
        for(int k = 0; k <= j - 1; ++k)
        {
          sum += L[i][k] * L[j][k];
        }
        L[i][j] = ((*this)[i][j] - sum) / L[j][j];
      }
    }
  }
  return L;
}

template <typename T>
Matrix2D<T> Matrix2D<T>::gaussianElimination()
{
  //wyniki
  Matrix2D<T> results(this->get_rows(), 1, static_cast<T>(0));
  //kopiujemy macierz, żeby nie modyfikować oryginału
  Matrix2D<T> tmp = (*this);

  for (unsigned long k = 0; k<this->get_rows(); k++)
  {
    unsigned long index = k;
    T maxVal = tmp[index][k];

    //Dla każdego x_k znajdujemy jego maksymalną wartość absolutną.
    //Ten wiersz zostanie wybrany do odejmowania jego wielokrotności od reszty układu
    //po to by zagwarantować stabilność numeryczną.
    for (unsigned long i = k + 1; i < this->get_rows(); ++i)
    {
      if (abs(tmp[i][k]) > maxVal)
      {
        maxVal = tmp[i][k], index = i;
      }
    }

    //Maksymalna absolutna wartość 0 oznacza, że x_k w ogóle nie występuje w układzie, więc
    // nie jest to jednoznaczny układ
    if (tmp[k][index] == static_cast<T>(0))
      throw (-1);

    //Wybrany wiersz wymienia się miejscami z górnym
    if (index != k)
      std::swap(tmp[k], tmp[index]);

    //Od każdego wiersza poniżej wiersza k odejmujemy taką wielokrotność wiersza k, żeby wyzerować x_k
    //w każdym wierszu
    for (unsigned long i = k + 1; i < this->get_rows(); ++i)
    {
      T f = tmp[i][k] / tmp[k][k];

      for (unsigned long j = k + 1; j <= this->get_rows(); ++j)
      {
        tmp[i][j] -= tmp[k][j] * f;
      }

      tmp[i][k] = static_cast<T>(0);
    }
  }

  //W tym momencie macierz jest już górną macierzą trójkątną.
  //Z każdego kolejnego wiersza od końca można wyznaczać poszczególne współczynniki
  for (long i = this->get_rows() - 1; i >= 0; --i)
  {
    results[i][0] = tmp[i][this->get_rows()];

    for (unsigned long j = i + 1; j<this->get_rows(); ++j)
    {
      results[i][0] -= tmp[i][j]*results[j][0];
    }

    results[i][0] = results[i][0]/tmp[i][i];
  }
  return results;
}