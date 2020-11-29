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

add_executable(01_create_thread_lambda_function 
  01_create_thread_lambda_function.cpp
)
target_link_libraries (01_create_thread_lambda_function Threads::Threads)

add_executable(02_create_thread_functor 
  02_create_thread_functor.cpp
)
target_link_libraries (02_create_thread_functor Threads::Threads)

add_executable(03_thread_guard 
  03_thread_guard.cpp
)
target_link_libraries (03_thread_guard Threads::Threads)

add_executable(04_pass_reference_argument 
  04_pass_reference_argument.cpp
)
target_link_libraries (04_pass_reference_argument Threads::Threads)

add_executable(04_pass_class_method 
  04_pass_class_method.cpp
)
target_link_libraries (04_pass_class_method Threads::Threads)

add_executable(05_movable_thread 
  05_movable_thread.cpp
)
target_link_libraries (05_movable_thread Threads::Threads)

add_executable(06_move_aware_container_for_thread 
  06_move_aware_container_for_thread.cpp
)
target_link_libraries (06_move_aware_container_for_thread Threads::Threads)

add_executable(07_determine_hardware_concurrency 
  07_determine_hardware_concurrency.cpp
)
target_link_libraries (07_determine_hardware_concurrency Threads::Threads)

add_executable(08_parallel_accumulate
  08_parallel_accumulate.cpp
)
target_link_libraries (08_parallel_accumulate Threads::Threads)

add_executable(09_thread_identifier
  09_thread_identifier.cpp
)
target_link_libraries (09_thread_identifier Threads::Threads)