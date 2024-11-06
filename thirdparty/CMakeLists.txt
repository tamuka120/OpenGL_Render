# GLAD
add_library(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set_target_properties(GLAD PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES $<TARGET_PROPERTY:GLAD,INTERFACE_INCLUDE_DIRECTORIES>)

# SPDLOG
add_library(spdlog INTERFACE)
target_include_directories(spdlog SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
target_compile_definitions(spdlog 
     INTERFACE
     # -w 
     _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)


add_library(stb_image INTERFACE)
target_include_directories(stb_image SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb_image)
target_compile_definitions(stb_image INTERFACE STB_IMAGE_IMPLEMENTATION)


add_library(glm INTERFACE)
target_include_directories(glm SYSTEM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm)
# target_compile_definitions(glm INTERFACE STB_IMAGE_IMPLEMENTATION)