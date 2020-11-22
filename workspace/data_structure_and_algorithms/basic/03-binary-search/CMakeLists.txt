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

add_executable(lc_0458_classical_binary_search 
  lc_0458_classical_binary_search.cpp
)

add_executable(lc_0014_first_position_of_target
  lc_0014_first_position_of_target.cpp
)

add_executable(lc_0458_last_position_of_target
  lc_0458_last_position_of_target.cpp
)

add_executable(lc_0460_find_k_closest_elements
  lc_0460_find_k_closest_elements.cpp
)

add_executable(lc_0075_find_peak_element
  lc_0075_find_peak_element.cpp
)

add_executable(lc_0159_find_minimum_in_rotated_sorted_array
  lc_0159_find_minimum_in_rotated_sorted_array.cpp
)

add_executable(lc_0183_wood_cut
  lc_0183_wood_cut.cpp
)

add_executable(lc_0585_maximum_number_in_mountain_sequence
  lc_0585_maximum_number_in_mountain_sequence.cpp
)

add_executable(lc_0447_search_in_a_big_sorted_array
  lc_0447_search_in_a_big_sorted_array.cpp
)

add_executable(lc_0062_search_in_rotated_sorted_array
  lc_0062_search_in_rotated_sorted_array.cpp
)