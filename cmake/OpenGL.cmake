# OpenGL.cmake
#
# Find packages related to OpenGL

# OpenGL and GLUT
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

# GLM
#find_package(GLM REQUIRED)
#message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

# GLEW
find_package(GLEW REQUIRED)
#message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")
#include_directories(${GLEW_INCLUDE_DIR})

# GLFW
find_package(glfw3 REQUIRED)
message(STATUS "Found GLFW in ${GLFW_INCLUDE_DIR}")
include_directories(${GLFW_INCLUDE_DIR})

# ASSIMP
#find_package(ASSIMP REQUIRED)
#message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
