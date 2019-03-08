# cmake_minimum_required(VERSION <specify CMake version here>)
project(zad1)

set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required (VERSION 2.6)
find_package (Threads)
add_executable(zad1 main.cpp TokenRingClient.cpp mqueue.cpp Token.h Message.h)
add_compile_options(-Wall)
target_link_libraries (zad1 ${CMAKE_THREAD_LIBS_INIT})
