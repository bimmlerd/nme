cmake_minimum_required(VERSION 3.3)
project(nm2d_code)

# Tested with g++ and clang
# Use -O3 for strong optimization. We use stdc++11. Compile with Wall to get all warnings.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -O3 -Wextra -Wno-deprecated-declarations -pedantic" )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

# If your compiler already finds and includes Eigen you can safely remove the following two lines
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

set(SOURCE_FILES buildC.cpp)
add_executable(buildC ${SOURCE_FILES})

set(SOURCE_FILES solvelse.cpp)
add_executable(solvelse ${SOURCE_FILES})