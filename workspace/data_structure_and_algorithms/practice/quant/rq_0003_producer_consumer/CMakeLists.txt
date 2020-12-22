cmake_minimum_required(VERSION 3.10.2)
project(producer_consumer)

## Compile as C++17:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++17)
add_definitions(-std=c++17)

################################################
## dependencies ##
################################################
find_package (Threads REQUIRED)

###########
## Build ##
###########
include_directories (
    include
)

add_executable(main 
  main.cpp
)
target_link_libraries (main Threads::Threads)
