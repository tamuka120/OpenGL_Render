add_library(
    GLBufferObjects 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementBufferObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArrayObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexBufferObject.cpp
)
 
target_include_directories(GLBufferObjects PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(GLBufferObjects PRIVATE GLAD)
target_link_libraries(GLBufferObjects PRIVATE spdlog)

target_compile_definitions(GLBufferObjects PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)


