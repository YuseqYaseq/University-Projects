//
// Created by joseph on 06.12.18.
//

#include <random>
#include <fstream>
#include "ConvSigmoidLayer.h"

AGH_NN::ConvSigmoidLayer::ConvSigmoidLayer(unsigned long _k, unsigned long _d, unsigned long _w, unsigned long _h,
                                           unsigned long _m, unsigned long _wf, unsigned long _hf, unsigned long _s,
                                           unsigned long _p) : k(_k), d(_d), w(_w), h(_h), m(_m), wf(_wf), hf(_hf),
                                                                s(_s), p(_p) {
  if((w + 2 * p - wf) % s != 0 || (h + 2 * p - hf) % s != 0) {
    std::cerr << "Cannot compute convolution with chosen stride!" << std::endl;
    throw -1;
  }
  filters.resize(m);
  dw.resize(m);
  for(unsigned long i = 0; i < m; ++i) {
    filters[i].resize(d, Matrix2D<double>(hf, wf, 0.0));
    dw[i].resize(d, Matrix2D<double>(hf, wf, 0.0));
  }

  A.resize(k);
  for(unsigned long i = 0; i < k; ++i)
    A[i].resize(m, Matrix2D<double>(getSize(h, hf, s, p), getSize(w, wf, s, p), 0.0));
  bias = Matrix2D<double>(m, 1, 0.0);
  db = Matrix2D<double>(m, 1, 0.0);

  dX = nullptr;
}

AGH_NN::ConvSigmoidLayer::~ConvSigmoidLayer() {
  if(dX != nullptr) {
    delete dX;
    dX = nullptr;
  }
}

double AGH_NN::ConvSigmoidLayer::getValue(unsigned long example, unsigned long cornerX,
    unsigned long cornerY, unsigned long filterNo, std::vector<std::vector<AGH_NN::Matrix2D<double>>>& X) {
  double sum = 0;
  long paddedStartingPosX = cornerX - p;
  long paddedStartingPosY = cornerY - p;
  for(long x = paddedStartingPosX; x < paddedStartingPosX + static_cast<long>(wf); ++x) {
    for(long y = paddedStartingPosY; y < paddedStartingPosY + static_cast<long>(hf); ++y) {
      for (unsigned long depth = 0; depth < d; ++depth) {
        long filterPosX = x - paddedStartingPosX;
        long filterPosY = y - paddedStartingPosY;

        double xVal;
        if (x >= 0 && y >= 0 && x < w & y < h) {
          xVal = X[example][depth][y][x];
          sum += filters[filterNo][depth][filterPosY][filterPosX] * xVal;
        }
      }
    }
  }
  return sum;
}


void AGH_NN::ConvSigmoidLayer::forward_propagation(std::vector<std::vector<AGH_NN::Matrix2D<double>>>& X) {
  if(k != X.size()) {
    k = X.size();
    A = std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
        std::vector<AGH_NN::Matrix2D<double>>(m, AGH_NN::Matrix2D<double>(getSize(h, hf, s, p), getSize(w, wf, s, p), 0.0)));
  }
  lastX = &X;
  for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long f_no = 0; f_no < m; ++f_no) {
      unsigned long max_y = getSize(h, hf, s, p);
      for (unsigned long y = 0; y < max_y; y++) {
        unsigned long max_x = getSize(w, wf, s, p);
        for (unsigned long x = 0; x < max_x; x++) {
          A[ex][f_no][y][x] = getValue(ex, x, y, f_no, X) + bias[f_no][0];
        }
      }
      //A[ex][f_no] = sigmoid2D(A[ex][f_no]);
    }
  }
  /*for(unsigned long ex = 0; ex < k; ++ex) {
    for(unsigned long dim = 0; dim < m; ++dim) {
      for(unsigned long y = 0; y < getSize(h, hf, s, p); ++y) {
        for(unsigned long x = 0; x < getSize(w, wf, s, p); ++x) {
          A[ex][dim][y][x] = 0;
        }
      }
    }
  }
  long curY;
  long curX;
  long x = 0;
  long y = 0;
  for(long ex = 0; ex < k; ex++) {
    for (long curFiltersDepth = 0; curFiltersDepth < m; curFiltersDepth++) {
      curY = 0;
      for (long outY = 0; outY < h; outY++) {
        curX = 0;
        for (long outX = 0; outX < w; outX++) {
          for (long i = curY - p; i <= curY + p; i++, y++) {
            for (long j = curX - p; j <= curX + p; j++, x++) {
              for (long dim = 0; dim < d; dim++) {
                if (i >= 0 && i < h && j >= 0 && j < w) {
                  A[ex][curFiltersDepth][i][j] += filters[curFiltersDepth][dim][y][x] * X[ex][dim][outY][outX];
                }
              }
            }
            x = 0;
          }
          y = 0;
          curX += s;
        }
        curY += s;
      }
    }
  }

  for(long ex = 0; ex < k; ex++) {
    for(long dim = 0; dim < d; dim++) {
      for(long x = 0; x < w; ++x) {
        for(long y = 0; y < h; ++y) {
          for(long f = 0; f < m; ++f) {
            A[ex][dim][y][x] += bias[f][0];
          }
        }
      }
    }
  }*/
}

std::vector<std::vector<AGH_NN::Matrix2D<double>>> & AGH_NN::ConvSigmoidLayer::backward_propagation(
    std::vector<std::vector<AGH_NN::Matrix2D<double>>> &prevError) {

  //zero out dw
  for(unsigned long f_no = 0; f_no < m; ++f_no) {
    for (unsigned long dim = 0; dim < d; ++dim) {
      for (unsigned long y = 0; y < hf; y ++) {
        for (unsigned long x = 0; x < wf; x ++) {
          dw[f_no][dim][y][x] = 0.0;
        }
      }
    }
    //zero out db
    db[f_no][0] = 0.0;
  }

  if(dX != nullptr) {
    delete dX;
  }

  dX = new std::vector<std::vector<AGH_NN::Matrix2D<double>>>(k,
      std::vector<AGH_NN::Matrix2D<double>>(d, AGH_NN::Matrix2D<double>(h, w, 0.0)));

  long curY;
  long curX;
  long x = 0;
  long y = 0;
  for(long ex = 0; ex < k; ex++) {
    for (long curFiltersDepth = 0; curFiltersDepth < m; curFiltersDepth++) {
      curY = 0;
      for (long outY = 0; outY < h; outY++) {
        curX = 0;
        for (long outX = 0; outX < w; outX++) {
          for (long i = curY - p; i <= curY + p; i++, y++) {
            for (long j = curX - p; j <= curX + p; j++, x++) {
              for (long dim = 0; dim < d; dim++) {
                if (i >= 0 && i < h && j >= 0 && j < w) {
                  (*dX)[ex][dim][outY][outX] += filters[curFiltersDepth][dim][x][y] * prevError[ex][curFiltersDepth][i][j];
                  dw[curFiltersDepth][dim][y][x] += (*lastX)[ex][dim][j][i] * prevError[ex][curFiltersDepth][i][j];
                }
              }
            }
            x = 0;
          }
          y = 0;
          double tmp = prevError[ex][curFiltersDepth][outY][outX];
          db[curFiltersDepth][0] += tmp;
          curX += s;
        }
        curY += s;
      }
    }
  }
  return *dX;
}

void AGH_NN::ConvSigmoidLayer::update_parameters(double learning_rate) {
  for(unsigned long f_no = 0; f_no < m; ++f_no) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      filters[f_no][dim] -= dw[f_no][dim] * learning_rate;
    }
    bias[f_no][0] -= db[f_no][0];
  }
}

void AGH_NN::ConvSigmoidLayer::initialize_gaussian()
{
  srand(time(NULL));
  initialize_gaussian(0.0, 1.0, static_cast<unsigned long>(rand()));
}

void AGH_NN::ConvSigmoidLayer::initialize_gaussian(double median, double variance, unsigned long seed)
{
  std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(median, variance);
  for(unsigned long ex = 0; ex < m; ++ex) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      for (unsigned long y = 0; y < filters[ex][dim].get_rows(); ++y) {
        for (unsigned long x = 0; x < filters[ex][dim].get_cols(); ++x) {
          filters[ex][dim][y][x] = distribution(generator);
        }
      }
    }
    //There is no need to randomly initialize bias
    bias[ex][0] = 0.0;
  }
}


unsigned long AGH_NN::ConvSigmoidLayer::getSize(unsigned long size, unsigned long filterSize, unsigned long stride,
                                                unsigned long padding) {
  return (size + 2 * padding - filterSize) / stride + 1;
}

void AGH_NN::ConvSigmoidLayer::save_to_file(const char *pathName) {
  std::fstream file(pathName, std::fstream::out);
  if(!file.is_open()) {
    std::cerr << "Failed to save to " << pathName << "!" << std::endl;
    return;
  }
  file.precision(30);
  file << k << " " << d << " " << w << " " << h << " " << m << " " << wf << " " << hf
      << " " << s << " " << p << std::endl;
  
  for(unsigned long f_no = 0; f_no < m; ++f_no) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      for(unsigned long y = 0; y < hf; ++y) {
        for(unsigned long x = 0; x < wf; ++x) {
          file << filters[f_no][dim][y][x] << " ";
        }
      }
    }
    file << bias[f_no][0] << std::endl;
  }
}

AGH_NN::ConvSigmoidLayer::ConvSigmoidLayer(const char *pathName) {
  std::fstream file(pathName, std::fstream::in);
  if(!file.is_open()) {
    std::cerr << "Failed to load from " << pathName << "!" << std::endl;
    return;
  }
  file >> k >> d >> w >> h >> m >> wf >> hf >> s >> p;

  ////////////Standard constructor//////////////
  if((w + 2 * p - wf) % s != 0 || (h + 2 * p - hf) % s != 0) {
    std::cerr << "Cannot compute convolution with chosen stride!" << std::endl;
    throw -1;
  }
  filters.resize(m);
  dw.resize(m);
  for(unsigned long i = 0; i < m; ++i) {
    filters[i].resize(d, Matrix2D<double>(hf, wf, 0.0));
    dw[i].resize(d, Matrix2D<double>(hf, wf, 0.0));
  }

  A.resize(k);
  for(unsigned long i = 0; i < k; ++i)
    A[i].resize(m, Matrix2D<double>(getSize(h, hf, s, p), getSize(w, wf, s, p), 0.0));
  bias = Matrix2D<double>(m, 1, 0.0);
  db = Matrix2D<double>(m, 1, 0.0);

  dX = nullptr;
  //////////////////////////////////////////////

  for(unsigned long f_no = 0; f_no < m; ++f_no) {
    for(unsigned long dim = 0; dim < d; ++dim) {
      for(unsigned long y = 0; y < hf; ++y) {
        for(unsigned long x = 0; x < wf; ++x) {
          file >> filters[f_no][dim][y][x];
        }
      }
    }
    file >> bias[f_no][0];
  }
}