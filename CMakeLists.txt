cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/thirdparty/modules)
set(GLFW3_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/glfw-3.4)

project(OpenGL_Render)

cmake_policy(SET CMP0074 NEW)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
endif(WIN32)

add_subdirectory(GLBufferObjects)
add_subdirectory(GLShader)
add_subdirectory(GLWindowManager)
add_subdirectory(thirdparty)

find_package(GLFW3 REQUIRED)
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")

add_executable(OpenGL_Render main.cpp)

target_link_libraries(OpenGL_Render GLBufferObjects)
target_link_libraries(OpenGL_Render GLShader)
target_link_libraries(OpenGL_Render GLWindowManager) 

target_link_libraries(OpenGL_Render GLAD) 
target_link_libraries(OpenGL_Render GLFW3)
target_link_libraries(OpenGL_Render spdlog)

set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
set_target_properties(OpenGL_Render PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_compile_definitions(OpenGL_Render 
	PRIVATE 
	SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)