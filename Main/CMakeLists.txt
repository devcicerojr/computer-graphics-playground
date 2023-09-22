cmake_minimum_required (VERSION 3.8)

set (MODULE_NAME "MAIN")

message ("> Module: Main")

set (${MODULE_NAME}_SOURCES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")


include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
link_directories(${GLEW_LIB_DIR} ${GLFW_LIB_DIR})


message ("GLFW LIB: ${GLFW_LIB}")
add_executable(CGMain ${${MODULE_NAME}_SOURCES})
target_link_libraries(CGMain opengl32.lib ${GLEW_LIB} glfw3.lib)