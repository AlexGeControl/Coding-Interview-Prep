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

add_executable(lc_0434_number_of_islands_ii 
  lc_0434_number_of_islands_ii.cpp
)

add_executable(lc_1014_bricks_falling_when_hit
  lc_1014_bricks_falling_when_hit.cpp
)

add_executable(lc_0805_maximum_association_set
  lc_0805_maximum_association_set.cpp
)

add_executable(lc_1463_paper_review
  lc_1463_paper_review.cpp
)

add_executable(lc_1179_friend_circles
  lc_1179_friend_circles.cpp
)