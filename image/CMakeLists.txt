# CMakeLists.txt

# Set the project name
set(PROJECT, "ImageTest")
project(ImageTest)

# Source the OpenGL cmake file
include(${CMAKE_SOURCE_DIR}/cmake/OpenGL.cmake)

# Add a single source file to every executable
add_executable_cpp("HelloTriangle")
