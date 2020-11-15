cmake_minimum_required(VERSION 3.10.2)
project(introduction)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

###########
## Build ##
###########

add_executable(lc_0627_longest_palindrome_i 
  lc_0627_longest_palindrome_i.cpp
)

add_executable(lc_0200_longest_palindromic_substring 
  lc_0200_longest_palindromic_substring.cpp
)

add_executable(lc_0415_is_palindrome
  lc_0415_is_palindrome.cpp
)

add_executable(lc_0013_find_substring
  lc_0013_find_substring.cpp
)
