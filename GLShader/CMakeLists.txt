set(RESOURCES_DIR ${CMAKE_SOURCE_DIR}/resources)
set(SHADER_DIR ${RESOURCES_DIR}/shaders)
set(IMAGES_DIR ${RESOURCES_DIR}/images)

# Save paths to resources in generated header file
configure_file (resources.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/resources.h) 

add_library(
    GLShader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLBaseShader.cpp
)

target_include_directories(GLShader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(GLShader PRIVATE GLAD)
target_link_libraries(GLShader PRIVATE spdlog)
