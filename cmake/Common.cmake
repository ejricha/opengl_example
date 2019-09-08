# Common.cmake
#
# Variables that should be set in all projects

# Produce YCM tags
include(${CMAKE_SOURCE_DIR}/cmake/YCM.cmake)

# We need at least C++11 to run
set(CMAKE_CXX_STANDARD 11)	

# Use colorful output by default
option(COLOR_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if(${COLOR_OUTPUT})
	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		add_compile_options(-fdiagnostics-color=always)
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		add_compile_options(-fcolor-diagnostics)
	endif()
endif()