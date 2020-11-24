cmake_minimum_required(VERSION 3.10.2)
project(depth_first_search)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0425_letter_combinations_of_a_phone_number 
  lc_0425_letter_combinations_of_a_phone_number.cpp
)

add_executable(lc_0010_string_permutation_ii
  lc_0010_string_permutation_ii.cpp
)

add_executable(lc_0135_combination_sum
  lc_0135_combination_sum.cpp
)

add_executable(lc_0090_k_sum_ii
  lc_0090_k_sum_ii.cpp
)