# CMakeLists.txt
#
# Top-level file

# Need at least cmake 3.10 for OpenGL finder
cmake_minimum_required(VERSION 3.10)

# Produce YCM tags
include(cmake/YCM.cmake)

# We need at least C++11 to run
set(CMAKE_CXX_STANDARD 11)	

# Set the project name
project (OpenGL_Example)

# Build the following subdirs
add_subdirectory(evaluator)
