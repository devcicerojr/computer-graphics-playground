cmake_minimum_required (VERSION 3.8)

set (MODULE_NAME "MAIN")

message ("> Module: Main")

set (${MODULE_NAME}_SOURCES "${CMAKE_CURRENT_LIST_DIR}/main.cpp")


include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${DOMAIN_INCLUDE_DIR})
link_directories(${GLEW_LIB_DIR} ${GLFW_LIB_DIR})


message ("GLFW LIB: ${GLFW_LIB}")
message ("Main binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
message ("Build type: ${CMAKE_BUILD_TYPE}")
add_executable(CGMain ${${MODULE_NAME}_SOURCES})
add_dependencies(CGMain DOMAIN)
target_include_directories(CGMain PRIVATE DOMAIN_INCLUDE_DIR)
target_link_libraries(CGMain opengl32.lib ${GLEW_LIB} ${GLFW_LIB} DOMAIN)

add_custom_command(TARGET CGMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_FILES} $<TARGET_FILE_DIR:CGMain>
    COMMENT "Copying shaders to output directory"
)

add_custom_command(TARGET CGMain POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_DLL} $<TARGET_FILE_DIR:CGMain>
    COMMENT "Copying glew dll to output directory"
)