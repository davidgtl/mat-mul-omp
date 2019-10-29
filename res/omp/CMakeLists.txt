# Project definition
cmake_minimum_required(VERSION 3.8)
project(cpd_openmp)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES source/loop_ex1.c)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Executable definition and properties
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++ -g3 -Wall -O0")
#set(CMAKE_CXX_STANDARD 17)
#if (MSVC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /openmp")
#endif (MSVC)
#set(CMAKE_REQUIRED_FLAGS "-O2 -std=c++14")
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
#target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/includes")
#set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


