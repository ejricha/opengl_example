# OpenGL.cmake
#
# Find packages related to OpenGL

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLFW3
find_package(glfw3 REQUIRED)
