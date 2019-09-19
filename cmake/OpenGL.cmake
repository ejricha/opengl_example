# OpenGL.cmake
#
# Find packages related to OpenGL

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

# GLFW3
find_package(glfw3 REQUIRED)

# Macro to add a simple executable
macro(add_executable_cpp NAME)
	set(BIN "${NAME}.bin")
	set(CPP "${NAME}.cpp")
	message("Building ${BIN} from ${CPP}")
	add_executable(${BIN} ${CPP})
	
	# Be sure to link against OpenGL etc.
	target_link_libraries(${BIN} ${OPENGL_LIBRARIES} glad glfw ${CMAKE_DL_LIBS})
endmacro()
