# CMakeLists.txt

# Set the project name
set(PROJECT, "ImageTest")
project(ImageTest)

# Source the OpenGL cmake file
include(${CMAKE_SOURCE_DIR}/cmake/OpenGL.cmake)

# Add a single source file to the executable
add_executable(ImageTest.bin ImageTest.cpp)
#add_executable(ImageTest.bin ImageFromSource.cpp)

# Be sure to link against OpenGL etc.
#target_link_libraries(ImageTest.bin ${OPENGL_LIBRARIES} glfw GLEW ${GLUT_LIBRARY})
target_link_libraries(ImageTest.bin ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES} glad glfw)
