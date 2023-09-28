cmake_minimum_required (VERSION 3.8)
set (CMAKE_CXX_STANDARD 17)

project ("CGPlayground")

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	message("Build Architecture x86")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	message(FATAL_ERROR "x64 is not supported so far")
endif()

set (GLEW_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/glew/include/" CACHE INTERNAL "")
set (GLEW_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/external/glew/lib/Release/x86/" CACHE INTERNAL "")
set (GLEW_LIB "${CMAKE_CURRENT_LIST_DIR}/external/glew/lib/Release/x86/glew32.lib" CACHE INTERNAL "")
# set (GLEW_LIB_S "${CMAKE_CURRENT_LIST_DIR}/external/glew/lib/Release/x86/glew32s.lib" CACHE INTERNAL "")
set (GLEW_DLL "${CMAKE_CURRENT_LIST_DIR}/external/glew/bin/Release/x86/glew32.dll" CACHE INTERNAL "")

set (GLFW_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/glfw/include/" CACHE INTERNAL "")
set (GLFW_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/external/glfw/lib/x86/" CACHE INTERNAL "")
set (GLFW_LIB "glfw3.lib" CACHE INTERNAL "")

set (GLM_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/external/glm/" CACHE INTERNAL "")

message("Runtime output: ${CMAKE_CURRENT_BINARY_DIR}")

file(COPY ${GLEW_DLL} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

add_compile_definitions(_HAS_STD_BYTE=0)
add_subdirectory ("Main")
add_subdirectory ("Domain")