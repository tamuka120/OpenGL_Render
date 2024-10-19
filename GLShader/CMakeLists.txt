add_library(
    GLShader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLShaderProgram.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GLBaseShader.cpp
)

target_include_directories(GLShader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(GLShader PRIVATE GLAD)
# target_link_libraries(GLShader PRIVATE UTIL)
target_link_libraries(GLShader PRIVATE spdlog)

target_compile_definitions(GLShader PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
