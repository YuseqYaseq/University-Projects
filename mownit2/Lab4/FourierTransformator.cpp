//
// Created by joseph on 31.10.18.
//

#include <algorithm>
#include <iostream>
#include "FourierTransformator.h"

template <typename T>
std::vector<std::complex<T>> FourierTransformator<T>::DFT(std::vector<std::complex<T>> vals)
{
  unsigned long N = vals.size();
  std::vector<std::complex<T>> results;
  //Dla każdego punktu wynikowego
  for(unsigned long k = 0; k < N; ++k)
  {
    //Dla każdego punktu ze zbioru danych wejściowych
    std::complex<T> sum = std::complex<T>(0, 0);
    for(unsigned long n = 0; n < N; ++n)
    {
      //Sumujemy według wzoru po wszystkich x_n
      std::complex<T> summand = std::complex<T>(cos(2 * M_PI * k * n / N), -sin(2 * M_PI * k * n / N));
      sum += vals[n] * summand;
    }
    results.push_back(sum);
  }
  return results;
}

template <typename T>
std::vector<std::complex<T>> FourierTransformator<T>::FFT(std::vector<std::complex<T>> vals)
{
  std::vector<std::complex<T>> results(vals.size());

  //Nasza implementacja działa jedynie dla rozmiarów wejściowych postaci 2^n
  if(vals.size() % 2 > 0)
  {
    throw -1;
  }

  //Dla odpowiednio małych danych wejściowych możemy wykorzystać powolny algorytm
  //by niepotrzebnie nie tworzyć zbyt wielu zejść rekurencji i tymczasowych vectorów.
  if(vals.size() <= 4)
  {
    return DFT(vals);
  }

  //Dzielimy nasz vector na dwie części - elementy o indeksie parzystym i nieparzystym
  std::vector<std::complex<T>> x_even;
  std::vector<std::complex<T>> x_odd;

  bool toggle = false;
  std::partition_copy(vals.begin(), vals.end(),
          std::back_inserter(x_even), std::back_inserter(x_odd),
          [&toggle](std::complex<T>) {return toggle = !toggle; });

  //Wykonujemy FFT na wydzielonych częściach
  x_even = FFT(x_even);
  x_odd = FFT(x_odd);

  for(int k = 0; k < vals.size()/2; ++k)
  {
    //Wyznaczamy mnożnik
    std::complex<T> factor = std::complex<T>(cos(2 * M_PI * k / vals.size()),
            -sin(2 * M_PI * k / vals.size()));

    //Konkatenujemy x_even i x_odd
    results[k] = x_even[k] + factor * x_odd[k];
    results[k + vals.size() / 2] = x_even[k] - factor * x_odd[k];
  }

  return results;
}