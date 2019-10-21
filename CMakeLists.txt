cmake_minimum_required(VERSION 3.10.2)
project(cpd)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-fopenmp -lpthread")
#SET(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp")
#SET(GCC_COVERAGE_LINK_FLAGS    "-fopenmp -lpthread")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
include_directories(.)

add_executable(cpd
        src/main.cpp src/Matrix.cpp src/Matrix.h)
