cmake_minimum_required(VERSION 3.22)

project(opengl_starter)

# Generate compile_commands.json.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GLFW.
set(GLFW_DIR "${PROJECT_SOURCE_DIR}/external/glfw/")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})

# glad.
set(GLAD_CORE_LIBRARY glad_gl_core_46)
set(GLAD_CORE_VERSION 4.6)
set(GLAD_DIR "${PROJECT_SOURCE_DIR}/external/glad/")
add_subdirectory("${GLAD_DIR}/cmake")
glad_add_library(${GLAD_CORE_LIBRARY} REPRODUCIBLE API gl:core=${GLAD_CORE_VERSION})

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ${GLAD_CORE_LIBRARY} glfw)
