cmake_minimum_required(VERSION 3.31)
project(FFTPrice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_executable(FFTPrice main.cpp)

# Add pybind11 (has its own CMake)
add_subdirectory(extern/pybind11)

# Header-only Eigen: just add include path
set(EIGEN3_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})

# Build the Python module with pybind11
pybind11_add_module(fftprice MODULE py_main.cpp)