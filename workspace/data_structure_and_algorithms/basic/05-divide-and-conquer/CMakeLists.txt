cmake_minimum_required(VERSION 3.10.2)
project(divide_and_conquer)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0900_closest_binary_search_tree_value 
  lc_0900_closest_binary_search_tree_value.cpp
)

add_executable(lc_0902_kth_smallest_element_in_a_bst
  lc_0902_kth_smallest_element_in_a_bst.cpp
)

add_executable(lc_0596_minimum_subtree
  lc_0596_minimum_subtree.cpp
)

add_executable(lc_0453_flatten_binary_tree_to_linked_list
  lc_0453_flatten_binary_tree_to_linked_list.cpp
)

add_executable(lc_0088_lowest_common_ancestor_of_a_binary_tree
  lc_0088_lowest_common_ancestor_of_a_binary_tree.cpp
)