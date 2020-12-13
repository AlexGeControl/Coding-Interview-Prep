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

add_executable(lc_0265_maximum_non_negative_subarray 
  lc_0265_maximum_non_negative_subarray.cpp
)

add_executable(lc_1507_shortest_subarray_with_sum_at_least_k 
  lc_1507_shortest_subarray_with_sum_at_least_k.cpp
)

add_executable(lc_1844_subarray_sum_equals_to_k_ii 
  lc_1844_subarray_sum_equals_to_k_ii.cpp
)

