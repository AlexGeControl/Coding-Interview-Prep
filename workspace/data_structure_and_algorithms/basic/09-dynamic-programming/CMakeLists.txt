cmake_minimum_required(VERSION 3.10.2)
project(dynamic_programming)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0119_edit_distance 
  lc_0119_edit_distance.cpp
)

add_executable(lc_0366_fibonacci
  lc_0366_fibonacci.cpp
)