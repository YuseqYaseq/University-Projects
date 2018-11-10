#include <iostream>
#include <fstream>
#include <complex>
#include <ctime>

#include "FourierTransformator.h"

//Dane pochodzą ze strony http://lampx.tugraz.at/~hadley/num/ch3/3.3a.php
const char* DATA_FILE_NAME = "../data_set.txt";
//Wyniki pomiarów dla rzeczywistych danych o rozmiarze 64
const char* RESULTS_FILE_NAME = "../results/results.txt";
//Wyniki dla pomiarów czasu
const char* TIME_FILE_NAME = "../results/time_elapsed.txt";

int main() {
  /*                     ZAD3                     */
  std::fstream timeFile(TIME_FILE_NAME);
  if(!timeFile.is_open())
  {
    std::cerr << "Failed to open file!" << std::endl;
    return -1;
  }
  std::vector<std::vector<std::complex<double>>> tests;
  tests.emplace_back(std::vector<std::complex<double>>(64));
  tests.emplace_back(std::vector<std::complex<double>>(256));
  tests.emplace_back(std::vector<std::complex<double>>(1024));
  tests.emplace_back(std::vector<std::complex<double>>(4096));
  tests.emplace_back(std::vector<std::complex<double>>(8192));
  for(int i = 0; i < tests.size(); ++i)
  {
    timeFile << "Test " << i << ": file size = " << tests[i].size() << std::endl;

    //DFT
    clock_t begin = clock();
    FourierTransformator<double>::DFT(tests[i]);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    timeFile << "Elapsed CPU time for DFT: " << elapsed_secs << std::endl;

    //FFT
    begin = clock();
    FourierTransformator<double>::FFT(tests[i]);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    timeFile << "Elapsed CPU time for FFT: " << elapsed_secs << std::endl;
    timeFile << std::endl;
  }

  timeFile.close();

  /*                     ZAD4                     */
  std::fstream file(DATA_FILE_NAME);
  std::fstream resultFile(RESULTS_FILE_NAME);
  if(!file.is_open() || !resultFile.is_open())
  {
    std::cerr << "Failed to open file!" << std::endl;
    return -1;
  }
  std::vector<std::complex<double>> x;
  while(!file.eof())
  {
    double re;
    double im = 0.0;
    file >> re;
    x.emplace_back(std::complex<double>(re, im));
  }
  std::vector<std::complex<double>> results = FourierTransformator<double>::FFT(x);
  std::vector<std::complex<double>> resultsDft = FourierTransformator<double>::DFT(x);
  for(int i = 0; i < results.size(); ++i)
  {
    std::cout  << results[i] << " " << resultsDft[i] << std::endl;
    resultFile << results[i] << std::endl;
  }

  file.close();
  resultFile.close();

  return 0;
}