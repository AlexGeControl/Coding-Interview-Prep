cmake_minimum_required(VERSION 3.10.2)
project(breadth_first_search)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0433_number_of_islands__graph_search 
  lc_0433_number_of_islands__graph_search.cpp
)

add_executable(lc_0611_knight_shortest_path
  lc_0611_knight_shortest_path.cpp
)

add_executable(lc_0127_topological_sorting
  lc_0127_topological_sorting.cpp
)

add_executable(lc_0120_word_ladder
  lc_0120_word_ladder.cpp
)

add_executable(lc_0137_clone_graph
  lc_0137_clone_graph.cpp
)