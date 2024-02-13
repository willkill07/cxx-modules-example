cmake_minimum_required(VERSION 3.28.0 FATAL_ERROR)
cmake_policy(VERSION 3.28)

project(example LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 26)

# enable c++ modules
include(cmake/std.cmake)

add_subdirectory(util)
add_subdirectory(model)

add_executable(main)
target_sources(main
  PRIVATE
    example.cpp
)
target_link_libraries(main PRIVATE model)
