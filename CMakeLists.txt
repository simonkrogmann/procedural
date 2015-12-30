cmake_minimum_required (VERSION 3.0)
project(procedural)

find_package(glm REQUIRED)
find_package(glbinding REQUIRED)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(Qt5OpenGL  REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLBINDING_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fsanitize=undefined -Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(source)
