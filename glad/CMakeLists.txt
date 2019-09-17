# CMakeLists.txt

# Set the project name
set(PROJECT, "glad")
project(glad)

# Source the Common cmake file
include(${CMAKE_SOURCE_DIR}/cmake/Common.cmake)

# Create the library
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)
