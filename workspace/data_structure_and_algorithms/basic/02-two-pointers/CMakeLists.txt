cmake_minimum_required(VERSION 3.10.2)
project(two_pointers)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0607_two_sum_iii_data_structure_design 
  lc_0607_two_sum_iii_data_structure_design.cpp
)

add_executable(lc_0587_two_sum_unique_pairs
  lc_0587_two_sum_unique_pairs.cpp
)

add_executable(lc_0057_3sum
  lc_0057_3sum.cpp
)