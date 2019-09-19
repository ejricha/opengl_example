# CMakeLists.txt

# Set the project name
set(PROJECT, "ImageTest")
project(ImageTest)

# Source the OpenGL cmake file
include(${CMAKE_SOURCE_DIR}/cmake/OpenGL.cmake)

# Add a single source file to every executable
add_executable(HelloTriangle.bin HelloTriangle.cpp)

# Be sure to link against OpenGL etc.
target_link_libraries(HelloTriangle.bin ${OPENGL_LIBRARIES} glad glfw ${CMAKE_DL_LIBS})
