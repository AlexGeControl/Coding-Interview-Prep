cmake_minimum_required(VERSION 3.10.2)
project(common_data_structures)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0138_subarray_sum 
  lc_0138_subarray_sum.cpp
)

add_executable(lc_0658_first_unique_number_in_data_stream
  lc_0658_first_unique_number_in_data_stream.cpp
)

add_executable(lc_0657_insert_delete_getrandom_o1
  lc_0657_insert_delete_getrandom_o1.cpp
)

add_executable(lc_0134_lru_cache
  lc_0134_lru_cache.cpp
)

add_executable(lc_0004_ugly_number_ii
  lc_0004_ugly_number_ii.cpp
)