#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <algorithm>

#include "SigmoidLayer.h"
#include "ActualConvSigmoidLayer.h"
#include "SoftMaxLayer.h"
#include "LogisticRegressor.h"
#include "MaxPoolLayer.h"
#include "../test/assert.h"

using namespace AGH_NN;
namespace fs = std::experimental::filesystem;
typedef std::vector<std::vector<AGH_NN::Matrix2D<double>>> ConvMatrix;

const char* LAYER1_FILE = "l1.txt";
const char* LAYER2_FILE = "l2.txt";
const char* LAYER3_FILE = "l3.txt";
const char* LAYER4_FILE = "l4.txt";
const char* LAYER5_FILE = "l5.txt";
const char* LAYER6_FILE = "l6.txt";

//set when we want to init weights randomly
//#define FROM_SCRATCH

const int size_x = 256;
const int size_y = 256;
const int num_of_dim = 3;
ConvMatrix load_pics(const char* path, std::vector<std::string>& names) {
  fs::directory_iterator pics(path);
  std::vector<std::string> words;
  ConvMatrix ret;
  for(auto& p : pics) {
    words.emplace_back(p.path());
  }
  std::sort(words.begin(), words.end());
  for(int word = 0; word < words.size(); ++word) {
    fs::directory_iterator w(words[word]);
    for(auto& p : w) {
      std::string s = p.path();
      if(s.substr(s.size() - 4, 4) == ".txt") {
        std::fstream file(s, std::fstream::in);
        if(!file.is_open()) {
          std::cerr << "Failed to open file " << s << "!" << std::endl;
          throw -1;
        }
        std::vector<AGH_NN::Matrix2D<double>> img(3, AGH_NN::Matrix2D<double>(size_y, size_x, 0.0));
        for(unsigned long y = 0; y < size_y; ++y) {
          for(unsigned long x = 0; x < size_x; ++x) {
            for(unsigned long dim = 0; dim < num_of_dim; ++dim) {
              file >> img[dim][y][x];
              img[dim][y][x] /= 255;
          }
        }
        }
        ret.emplace_back(img);
        names.emplace_back(s);
      }
    }
  }
  return ret;
}

int main() {

  double learning_rate = 0.1;
  unsigned long seed = 4324;
  double median = 0.0;
  double variance = 0.0001;

  //conv layer1 hyperparams
  unsigned long k1 = 10*18;
  unsigned long d1 = 3;
  unsigned long w1 = 256;
  unsigned long h1 = 256;
  unsigned long m1 = 5;
  unsigned long wf1 = 1;
  unsigned long hf1 = 1;
  unsigned long s1 = 1;
  unsigned long p1 = 0;

  //maxpool layer2 hyperparams
  unsigned long k2 = k1;
  unsigned long d2 = m1;
  unsigned long w2 = 256;
  unsigned long h2 = 256;
  unsigned long wf2 = 2;
  unsigned long hf2 = 2;
  unsigned long p2 = 0;
  unsigned long s2 = 1;

  //conv layer3 hyperparams
  unsigned long k3 = k1;
  unsigned long d3 = 5;
  unsigned long w3 = 128;
  unsigned long h3 = 128;
  unsigned long m3 = 5;
  unsigned long wf3 = 5;
  unsigned long hf3 = 5;
  unsigned long s3 = 1;
  unsigned long p3 = 2;

  //maxpool layer4 hyperparams
  unsigned long k4 = k1;
  unsigned long d4 = 5;
  unsigned long w4 = 128;
  unsigned long h4 = 128;
  unsigned long wf4 = 16;
  unsigned long hf4 = 16;
  unsigned long p4 = 0;
  unsigned long s4 = 1;

  //f-c sigmoid layer5 hyperparams
  unsigned long k5 = k1;
  unsigned long n5 = 5 * 8 * 8;
  unsigned long m5 = 100;

  //f-c sigmoid layer6 hyperparams
  unsigned long k6 = k1;
  unsigned long n6 = 100;
  unsigned long m6 = 10;

#ifdef FROM_SCRATCH
  //init layers
  ActualConvSigmoidLayer layer1(k1, d1, w1, h1, m1, wf1, hf1, s1, p1);
  MaxPoolLayer layer2(k2, d2, w2, h2, wf2, hf2);
  ActualConvSigmoidLayer layer3(k3, d3, w3, h3, m3, wf3, hf3, s3, p3);
  MaxPoolLayer layer4(k4, d4, w4, h4, wf4, hf4);
  SigmoidLayer layer5(m5, n5);
  SigmoidLayer layer6(m6, n6);
  SoftMaxLayer layer7;

  layer1.layer->initialize_gaussian(median, variance, seed);
  layer3.layer->initialize_gaussian(median, variance, seed);
  layer5.initialize_gaussian(median, variance, seed);
  layer6.initialize_gaussian(median, variance, seed);

  /*layer1.layer->save_to_file(LAYER1_FILE);
  layer2.save_to_file(LAYER2_FILE);
  layer3.layer->save_to_file(LAYER3_FILE);
  layer4.save_to_file(LAYER4_FILE);
  layer5.save_to_file(LAYER5_FILE);
  layer6.save_to_file(LAYER6_FILE);*/
#else
  ActualConvSigmoidLayer  layer1(LAYER1_FILE);
  MaxPoolLayer            layer2(LAYER2_FILE);
  ActualConvSigmoidLayer  layer3(LAYER3_FILE);
  MaxPoolLayer            layer4(LAYER4_FILE);
  SigmoidLayer            layer5(LAYER5_FILE);
  SigmoidLayer            layer6(LAYER6_FILE);
  SoftMaxLayer            layer7;

#endif

  //data
  std::vector<std::string> pic_names;
  std::vector<std::vector<Matrix2D<double>>> X = load_pics("pics", pic_names);
  Matrix2D<double> Y(k1, m6, 0.0);
  for(unsigned long y = 0; y < k1; ++y) {
    for(unsigned long x = 0; x < m6; ++x) {
      if(x == y / 18) {
        Y[y][x] = 1;
      }
    }
  }

  /////
  //for(const std::string& s : pic_names) {
  //  std::cout << s << std::endl;
  //}
  /////


  std::cout.precision(10);
  for(int i = 0; i < 0; ++i)
  {
    //forward propagation
    layer1.forward_propagation(X);

    layer2.forward_propagation(layer1.layer->getA());
    ConvMatrix A2 = layer2.getA();

    layer3.forward_propagation(A2);

    layer4.forward_propagation(layer3.layer->getA());
    Matrix2D<double> A4 = unfold(layer4.getA());

    layer5.forward_propagation(A4);

    Matrix2D<double> A5 = layer5.getA().T();
    layer6.forward_propagation(A5);

    Matrix2D<double> A6 = layer6.getA().T();
    layer7.forward_propagation(A6);


    Matrix2D<double> A7 = layer7.getA().T();
    //compute cost
    double cost = LogisticRegressor::calculateCost(A7, Y);




    //backward propagation
    AGH_NN::Matrix2D<double> dX7 = LogisticRegressor::calculateBackPropDerivatives(A7, Y);

    AGH_NN::Matrix2D<double> dX6 = layer7.backward_propagation(dX7).T();
    AGH_NN::Matrix2D<double> dX5 = layer6.backward_propagation(dX6).T();
    ConvMatrix dX4 = fold(layer5.backward_propagation(dX5), d4, w4/wf4, h4/hf4);
    ConvMatrix dX3 = layer4.backward_propagation(dX4);
    ConvMatrix dX2 = layer3.backward_propagation(dX3);
    ConvMatrix dX1 = layer2.backward_propagation(dX2);
    layer1.backward_propagation(dX1);

    //update parameters
    layer1.update_parameters(10 * learning_rate);
    layer2.update_parameters(10 * learning_rate);
    layer3.update_parameters(10 * learning_rate);
    layer4.update_parameters(learning_rate);
    layer5.update_parameters(learning_rate);
    layer6.update_parameters(learning_rate);

    std::cout << "Cost after " << i << " iterations: " << cost << std::endl;
    layer1.layer->save_to_file(LAYER1_FILE);
    layer2.save_to_file(LAYER2_FILE);
    layer3.layer->save_to_file(LAYER3_FILE);
    layer4.save_to_file(LAYER4_FILE);
    layer5.save_to_file(LAYER5_FILE);
    layer6.save_to_file(LAYER6_FILE);
  }


  //predict
  ConvMatrix d(1, X[0]);
  //d.emplace_back(X[1]);
  //d.emplace_back(X[30]);
  d.emplace_back(X[150]);
  d.emplace_back(X[70]);
  std::vector<std::string> names = {
      pic_names[0],
      //pic_names[1],
      //pic_names[30],
      pic_names[150],
      pic_names[70]};
  layer1.layer->forward_propagation(d);
  save_to(layer1.layer->getA(), "test.txt", names);
  layer2.forward_propagation(layer1.layer->getA());

  ConvMatrix A2 = layer2.getA();
  layer3.forward_propagation(A2);
  layer4.forward_propagation(layer3.layer->getA());
  save_to(layer3.layer->getA(), "test2.txt", names);

  Matrix2D<double> A4 = unfold(layer4.getA());
  layer5.forward_propagation(A4);

  Matrix2D<double> A5 = layer5.getA().T();
  layer6.forward_propagation(A5);

  Matrix2D<double> A6 = layer6.getA().T();
  layer7.forward_propagation(A6);

  std::cout << layer7.getA() << std::endl;
}