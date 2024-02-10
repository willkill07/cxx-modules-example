set(CMAKE_CXX_STANDARD_REQUIRED Yes)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    message(FATAL_ERROR "CMake CXX Standard not defined. Must be >= 20")
endif()
if (CMAKE_CXX_STANDARD LESS 20)
    message(FATAL_ERROR "CMake CXX Standard must be >= 20")
endif()

include(FetchContent)

execute_process(COMMAND
  bash "-c" "${CMAKE_CXX_COMPILER} --version | awk '/InstalledDir/{ print \$2 }'"
  OUTPUT_VARIABLE compiler_install_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

cmake_path(
  GET compiler_install_dir
  PARENT_PATH llvm_root_install_dir
)

if(NOT IS_DIRECTORY "${llvm_root_install_dir}/share/libc++/v1")
    message(FATAL_ERROR "\"${llvm_root_install_dir}/share/libc++/v1\" does not exist. Did you enable modules with your LLVM libcxx build?")
endif()

FetchContent_Declare(std_module
  URL "file://${llvm_root_install_dir}/share/libc++/v1"
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SYSTEM
)

if (NOT std_module_POPULATED)
    FetchContent_Populate(std_module)
endif()

add_library(std)
target_sources(std
  PUBLIC FILE_SET cxx_modules
  TYPE CXX_MODULES
  FILES
    ${std_module_SOURCE_DIR}/std.cppm
    ${std_module_SOURCE_DIR}/std.compat.cppm
)

target_include_directories(std
  SYSTEM
  PUBLIC
    ${llvm_root_install_dir}/include/c++/v1
    ${llvm_root_install_dir}/include/x86_64-unknown-linux-gnu/c++/v1
)

target_compile_options(std
  PRIVATE
    -Wno-reserved-module-identifier
    -Wno-reserved-user-defined-literal
  PUBLIC
    -nostdinc++
)

target_link_options(std
  INTERFACE
    -nostdlib++
    -L${llvm_root_install_dir}/lib
    -Wl,-rpath,${llvm_root_install_dir}/lib
)

target_link_libraries(std
  INTERFACE c++
)

link_libraries(std)
