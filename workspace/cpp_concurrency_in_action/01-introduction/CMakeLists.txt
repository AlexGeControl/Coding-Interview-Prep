cmake_minimum_required(VERSION 3.10.2)
project(introduction)

## Compile as C++11:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++11)
add_definitions(-std=c++11)

##################
## Dependencies ##
##################
find_package (Threads)

##################
## Build        ##
##################

add_executable(01_hello_cpp_concurrency 
  01_hello_cpp_concurrency.cpp
)
target_link_libraries (01_hello_cpp_concurrency Threads::Threads)