add_library(GLCamera ${CMAKE_CURRENT_SOURCE_DIR}/src/GLCamera.cpp)
 
target_include_directories(GLCamera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GLFW3 REQUIRED)
target_link_libraries(GLCamera PRIVATE GLAD)
target_link_libraries(GLCamera PRIVATE GLFW3)
target_link_libraries(GLCamera PRIVATE spdlog)
target_link_libraries(GLCamera PRIVATE glm)
