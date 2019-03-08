# cmake_minimum_required(VERSION <specify CMake version here>)
project(zad1)

set(CMAKE_CXX_STANDARD 17)


add_library(pthread TokenRingClient.cpp)
add_executable(zad1 main.cpp TokenRingClient.cpp TokenRingClient.h)