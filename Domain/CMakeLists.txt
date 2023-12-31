cmake_minimum_required (VERSION 3.8)

set (MODULE_NAME "DOMAIN")

message ("> Module: Domain")

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Mesh")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Shader")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/WindowHandler")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Camera")
set(DOMAIN_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../" CACHE INTERNAL "")


include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
link_directories(${GLEW_LIB_DIR} ${GLFW_LIB_DIR})

# For each subdirectory, make sure its sources and headers are added to the SOURCES and HEADERS of the module
set(${MODULE_NAME}_SOURCES ${${MODULE_NAME}_MESH_SOURCES}
	${${MODULE_NAME}_SHADER_SOURCES} 
	${${MODULE_NAME}_WINDOWHANDLER_SOURCES}
	${${MODULE_NAME}_CAMERA_SOURCES})

set(${MODULE_NAME}_HEADERS ${${MODULE_NAME}_MESH_HEADERS}
	${${MODULE_NAME}_SHADER_HEADERS}
	${${MODULE_NAME}_WINDOWHANDLER_HEADERS}
	${${MODULE_NAME}_CAMERA_HEADERS})

message ("${${MODULE_NAME}_HEADERS}")

add_library(${MODULE_NAME} ${${MODULE_NAME}_SOURCES} ${${MODULE_NAME}_HEADERS})
target_link_libraries(${MODULE_NAME} opengl32.lib ${GLEW_LIB} ${GLFW_LIB})