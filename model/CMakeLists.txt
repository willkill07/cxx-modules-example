add_library(model)
target_sources(model
  PUBLIC
    FILE_SET CXX_MODULES FILES
    root.cpp
    errors.cpp
    attribute.cpp
    class.cpp
    diagram.cpp
    relationship.cpp
    tags.cpp)

target_link_libraries(model PUBLIC util)
