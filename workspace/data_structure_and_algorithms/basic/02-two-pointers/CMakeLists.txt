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

add_executable(lc_0382_triangle_count
  lc_0382_triangle_count.cpp
)

add_executable(lc_0443_two_sum_greater_than_target
  lc_0443_two_sum_greater_than_target.cpp
)

add_executable(lc_0608_two_sum_ii_input_array_is_sorted
  lc_0608_two_sum_ii_input_array_is_sorted.cpp
)

add_executable(lc_0609_two_sum_less_than_or_equal_to_target
  lc_0609_two_sum_less_than_or_equal_to_target.cpp
)

add_executable(lc_0539_move_zeros
  lc_0539_move_zeros.cpp
)

add_executable(lc_0228_middle_of_linked_list
  lc_0228_middle_of_linked_list.cpp
)

add_executable(lc_0533_two_sum_closest_to_target
  lc_0533_two_sum_closest_to_target.cpp
)

add_executable(lc_0031_partition_array
  lc_0031_partition_array.cpp
)

add_executable(lc_0148_sort_colors
  lc_0148_sort_colors.cpp
)

add_executable(lc_0461_kth_smallest_numbers_in_unsorted_array
  lc_0461_kth_smallest_numbers_in_unsorted_array.cpp
)

add_executable(lc_0005_kth_largest_element
  lc_0005_kth_largest_element.cpp
)

add_executable(lc_0144_interleaving_positive_and_negative_numbers
  lc_0144_interleaving_positive_and_negative_numbers.cpp
)

add_executable(lc_0976_4sum_ii
  lc_0976_4sum_ii.cpp
)

add_executable(lc_0148_sort_colors_no_counting
  lc_0148_sort_colors_no_counting.cpp
)

add_executable(lc_0143_sort_colors_ii
  lc_0143_sort_colors_ii.cpp
)