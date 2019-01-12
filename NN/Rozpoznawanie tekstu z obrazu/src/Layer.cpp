//
// Created by joseph on 17.11.18.
//
#include <random>
#include <fstream>

#include "Layer.h"

AGH_NN::Layer::Layer(unsigned long currSize, unsigned long prevSize)
{
  weights = Matrix2D<double>(prevSize, currSize, 0.0);
  bias = Matrix2D<double>(currSize, 1, 0.0);
  dw = Matrix2D<double>(prevSize, currSize, 0.0);
  db = Matrix2D<double>(currSize, 1, 0.0);
}

AGH_NN::Layer::Layer(const char* pathName) {
  std::fstream file(pathName, std::fstream::in);
  if (!file.is_open()) {
    std::cerr << "Failed to load from " << pathName << "!" << std::endl;
    return;
  }
  unsigned long currSize, prevSize;
  file >> currSize >> prevSize;

  weights = Matrix2D<double>(prevSize, currSize, 0.0);
  bias = Matrix2D<double>(currSize, 1, 0.0);
  dw = Matrix2D<double>(prevSize, currSize, 0.0);
  db = Matrix2D<double>(currSize, 1, 0.0);

  for(unsigned long c = 0; c < currSize; ++c) {
    for(unsigned long p = 0; p < prevSize; ++p) {
      file >> weights[p][c];
    }
    file >> bias[c][0];
  }
  file.close();
}

void AGH_NN::Layer::save_to_file(const char *pathName) {
  std::fstream file(pathName, std::fstream::out);
  if (!file.is_open()) {
    std::cerr << "Failed to load from " << pathName << "!" << std::endl;
    return;
  }
  unsigned long currSize = weights.get_cols();
  unsigned long prevSize = weights.get_rows();
  file.precision(30);
  file << currSize << " " << prevSize << std::endl;

  for(unsigned long c = 0; c < currSize; ++c) {
    for(unsigned long p = 0; p < prevSize; ++p) {
      file << weights[p][c] << " ";
    }
    file << std::endl;
    file << bias[c][0];
    file << std::endl;
  }
  file.close();
}

void AGH_NN::Layer::initialize_gaussian()
{
  srand(time(NULL));
  initialize_gaussian(0.0, 1.0, static_cast<unsigned long>(rand()));
}

void AGH_NN::Layer::initialize_gaussian(double median, double variance, unsigned long seed)
{
  std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(median, variance);
  for(int i = 0; i < weights.get_cols(); ++i)
  {
    for(int j = 0; j < weights.get_rows(); ++j)
    {
      weights[j][i] = distribution(generator) / 1000;
    }
    //There is no need to randomly initialize bias
    bias[i][0] = 0.0;
  }
}

AGH_NN::Matrix2D<double> AGH_NN::unfold(std::vector<std::vector<AGH_NN::Matrix2D<double>>> X) {
  if(X.empty() || X[0].empty()) {
    return AGH_NN::Matrix2D<double>(0, 0, 0.0);
  }

  unsigned long no_ex = X.size();
  unsigned long depth = X[0].size();
  unsigned long width = X[0][0].get_cols();
  unsigned long height = X[0][0].get_rows();
  AGH_NN::Matrix2D<double> ret(depth * width * height, X.size(), 0.0);
  for(unsigned ex = 0; ex < no_ex; ++ex) {
    for (unsigned long dim = 0; dim < depth; ++dim) {
      for (unsigned long y = 0; y < height; ++y) {
        for (unsigned long x = 0; x < width; ++x) {
          unsigned long index = dim * (height + width) + y * width + x;
          ret[index][ex] = X[ex][dim][y][x];
        }
      }
    }
  }
  return ret;
}

std::vector<std::vector<AGH_NN::Matrix2D<double>>> AGH_NN::fold(AGH_NN::Matrix2D<double> X, unsigned long d,
                                                                unsigned long w, unsigned long h)
{
  std::vector<std::vector<AGH_NN::Matrix2D<double>>> ret(X.get_cols(),
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(h, w, 0.0)));

  for(unsigned ex = 0; ex < X.get_cols(); ++ex) {
    for (unsigned long dim = 0; dim < d; ++dim) {
      for (unsigned long y = 0; y < h; ++y) {
        for (unsigned long x = 0; x < w; ++x) {
          unsigned long index = dim * (h + w) + y * w + x;
          ret[ex][dim][y][x] = X[index][ex];
        }
      }
    }
  }
  return ret;
}