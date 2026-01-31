cmake_minimum_required(VERSION 3.10)

project(cardozo)

add_library(cardozo src/algos.hpp src/matrix.hpp src/dense_cr.cpp src/sparse_cr.cpp src/vector.cpp)
