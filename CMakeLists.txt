# CMakeLists.txt
#
# Top-level file

# Need at least cmake 3.10 for OpenGL finder
cmake_minimum_required(VERSION 3.10)

# Source some common files
include(${CMAKE_SOURCE_DIR}/cmake/Common.cmake)

# Add the top-level include directory
#include_directories(include)

# Set the project name
project(OpenGL_Example)

# Build the glad library
add_subdirectory(glad)

# Build the following subdirs
add_subdirectory(evaluator)
add_subdirectory(image)
