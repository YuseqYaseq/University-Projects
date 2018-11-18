cmake_minimum_required(VERSION 3.12)
project(Rozpoznawanie_tekstu_z_obrazu)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rozpoznawanie_tekstu_z_obrazu src/main.cpp src/FullyConnectedLayer.cpp src/FullyConnectedLayer.h src/Layer.cpp src/Layer.h)
add_executable(Run_Tests test/TestSuite.cpp)