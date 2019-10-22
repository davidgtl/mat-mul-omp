cmake_minimum_required(VERSION 3.10.2)
project(omp)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-fopenmp -lpthread")
#SET(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp")
#SET(GCC_COVERAGE_LINK_FLAGS    "-fopenmp -lpthread")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
include_directories(.)

#set_target_properties(omp PROPERTIES COMPILE_FLAGS "-fopenmp -lpthread")
add_executable(omp
        main.cpp Matrix.cpp Matrix.h)
