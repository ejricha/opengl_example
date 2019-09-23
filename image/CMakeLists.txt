# CMakeLists.txt

# Set the project name
set(PROJECT, "ImageTest")
project(ImageTest)

# Source the OpenGL cmake file
include(${CMAKE_SOURCE_DIR}/cmake/OpenGL.cmake)

# Add the shader directory path
add_compile_definitions(SHADER_DIR="${CMAKE_SOURCE_DIR}/image")
add_compile_definitions(TEXTURE_DIR="${CMAKE_SOURCE_DIR}/textures")

# Add a single source file to every executable
add_executable_cpp("HelloTriangle")
add_executable_cpp("Shaders")
add_executable_cpp("Textures")
add_executable_cpp("Transformations")
