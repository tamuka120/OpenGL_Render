# GLAD
add_library(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)

# UTIL
# add_library(UTIL INTERFACE)
# target_include_directories(UTIL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/utilities)

# SPDLOG
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
