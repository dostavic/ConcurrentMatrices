cmake_minimum_required(VERSION 3.27)
project(matrix_multiply)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix_multiply_sequential main.cpp)

add_executable(matrix_multiply_parallel parallel.cpp)