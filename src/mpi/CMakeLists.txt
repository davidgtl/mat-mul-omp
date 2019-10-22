cmake_minimum_required(VERSION 3.10.2)
project(mpi)

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpic++)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "-Wl,-Bsymbolic-functions -Wl,-z,relro -I/usr/include/mpich -L/usr/lib/x86_64-linux-gnu -lmpich")
#SET(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp")
#SET(GCC_COVERAGE_LINK_FLAGS    "-fopenmp -lpthread")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
include_directories(.)

add_executable(mpi
        main.cpp)