cmake_minimum_required(VERSION 3.10.2)
project(trie)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0442_implement_trie_prefix_tree 
  lc_0442_implement_trie_prefix_tree.cpp
)

add_executable(lc_1624_max_distance
  lc_1624_max_distance.cpp
)

add_executable(lc_0634_word_squares
  lc_0634_word_squares.cpp
)

add_executable(lc_0623_k_edit_distance
  lc_0623_k_edit_distance.cpp
)