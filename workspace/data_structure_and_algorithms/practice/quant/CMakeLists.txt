cmake_minimum_required(VERSION 3.10.2)
project(quant)

## Compile as C++17:
SET(CMAKE_BUILD_TYPE "Release")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
add_compile_options(-std=c++17)
add_definitions(-std=c++17)

################################################
## dependencies ##
################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

## Specify system libs:
find_package(Boost REQUIRED COMPONENTS  
  program_options 
)
find_package(Threads REQUIRED)

###########
## Build ##
###########

add_executable(rq_0001_parse_the_trades
  rq_0001_parse_the_trades.cpp
)

add_executable(rq_0002_parse_the_trades_read_optimized
  rq_0002_parse_the_trades_read_optimized.cpp
)
target_link_libraries(rq_0002_parse_the_trades_read_optimized ${Boost_LIBRARIES} Threads::Threads)