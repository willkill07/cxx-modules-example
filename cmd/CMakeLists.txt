add_library(cmd)
target_sources(cmd
  PUBLIC
    FILE_SET CXX_MODULES FILES
    root.cpp
    command.cpp
    types.cpp)
target_link_libraries(cmd PUBLIC util)