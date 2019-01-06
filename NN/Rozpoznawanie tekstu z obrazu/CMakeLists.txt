cmake_minimum_required(VERSION 3.12)
project(Rozpoznawanie_tekstu_z_obrazu)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rozpoznawanie_tekstu_z_obrazu
        src/main.cpp
        src/Layer.cpp
        src/SigmoidLayer.cpp
        src/LogisticRegressor.cpp
        src/ConvSigmoidLayer.cpp
        src/MaxPoolLayer.cpp
        src/ActualConvSigmoidLayer.cpp)
add_executable(Run_Tests
        test/TestSuite.cpp
        src/SigmoidLayer.cpp
        src/LogisticRegressor.cpp
        src/Layer.cpp
        src/ConvSigmoidLayer.cpp
        src/MaxPoolLayer.cpp)