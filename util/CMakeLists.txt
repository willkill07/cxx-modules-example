add_library(util)
target_sources(util
  PUBLIC
    FILE_SET CXX_MODULES FILES
    root.cpp
    result.cpp)
