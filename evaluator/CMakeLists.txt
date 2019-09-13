# CMakeLists.txt

# Set the project name
set(PROJECT, "EvalTest")
project(EvalTest)

# Source the OpenGL cmake file
include(${CMAKE_SOURCE_DIR}/cmake/OpenGL.cmake)

# Add a single source file to the executable
add_executable(EvalTest.bin evaltest.c)

# Be sure to link against opengl, glut, and glfw
target_link_libraries(EvalTest.bin ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} glfw)
