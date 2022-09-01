cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

set(PROJECT_NAME PrimaryEngine)

project(${PROJECT_NAME})


add_executable(${PROJECT_NAME} 
src/main.cpp
src/Renderer/Shaders/ShaderProgram.h
src/Renderer/Shaders/ShaderProgram.cpp
src/Core/Resources/ResourceManager.h
src/Core/Resources/ResourceManager.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(libs/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORT ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/base $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)

