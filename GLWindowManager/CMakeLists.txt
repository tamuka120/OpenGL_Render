add_library(GLWindowManager ${CMAKE_CURRENT_SOURCE_DIR}/src/WindowManager.cpp)
 
target_include_directories(GLWindowManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GLFW3 REQUIRED)
target_link_libraries(GLWindowManager PRIVATE GLAD)
target_link_libraries(GLWindowManager PRIVATE GLFW3)
target_link_libraries(GLWindowManager PRIVATE spdlog)
target_link_libraries(GLWindowManager PRIVATE glm)
target_link_libraries(GLWindowManager PRIVATE GLCamera)

target_compile_definitions(GLWindowManager PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
