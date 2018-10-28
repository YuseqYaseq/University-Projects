cmake_minimum_required(VERSION 3.12)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

find_package(GSL REQUIRED)
include_directories(${GSL_INCLUDE_DIR})

add_executable(zad1 zad1/main.cpp)
add_executable(zad2 zad2/main.cpp)
add_executable(zad3 zad3/main.cpp)
add_executable(zad4 zad4/main.cpp)

target_link_libraries(zad3 ${GSL_LIBRARIES})
target_link_libraries(zad4 ${GSL_LIBRARIES})